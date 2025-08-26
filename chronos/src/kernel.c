#include <stdint.h>
#include "include/defs.h"
#include "include/uart.h"
#include "include/clint.h"
#include "include/plic.h"

/* Forward from trap.S */
void trap_handler(uint64_t cause, uint64_t epc, uint64_t tval);

static inline int cause_is_interrupt(uint64_t cause) {
    return (cause >> 63) != 0;
}
static inline uint64_t cause_code(uint64_t cause) {
    return cause & 0xfff;
}

void trap_handler(uint64_t cause, uint64_t epc, uint64_t tval) {
    if (cause_is_interrupt(cause)) {
        switch (cause_code(cause)) {
            case IRQ_M_TIMER:
                clint_timer_isr();
                break;
            case IRQ_M_EXT: {
                uint32_t id = plic_claim();
                if (id == 10) {
                    uart_puts("[PLIC] UART IRQ\n");
                }
                if (id) plic_complete(id);
                break;
            }
            case IRQ_M_SOFT:
                uart_puts("[SWI]\n");
                break;
            default:
                uart_puts("[INT] Unknown\n");
                break;
        }
    } else {
        uart_puts("[EXC] Synchronous trap\n");
        /* Advance epc by 4 to skip faulting insn if needed */
        csr_write_mepc(epc + 4);
    }
}

void kernel_main(void) {
    uart_init();
    uart_puts("Chronos kernel booting...\n");

    /* Init CLINT timer: 100ms tick at 10 MHz */
    clint_timer_init(10000000UL, 100000);

    /* Init PLIC (optional). Enable UART THRE interrupt in uart_init to see IRQs */
    plic_init();

    uart_puts("Timer armed; entering WFI loop.\n");

    while (1) {
        wfi();
    }
}
