#include <stdint.h>
#include "include/defs.h"
#include "modules/uart/uart.h"
#include "modules/clint/clint.h"
#include "modules/plic/plic.h"
#include "modules/sched/sched.h"

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

/* Demo task A */
static volatile int task_a_count = 0;
void taskA(void) {
    while (1) {
        task_a_count++;
        /* Just count, timer will preempt us */
    }
}

/* Demo task B */
static volatile int task_b_count = 0;
void taskB(void) {
    while (1) {
        task_b_count++;
        /* Just count, timer will preempt us */
    }
}

void kernel_main(void) {
    uart_init();
    uart_puts("Chronos kernel booting...\n");

    /* Init scheduler with two tasks */
    uart_puts("Initializing scheduler...\n");
    tasks_init(taskA, taskB);

    /* Init CLINT timer: 10ms tick at 10 MHz for preemptive scheduling */
    uart_puts("Starting preemptive scheduler with timer...\n");
    clint_timer_init(10000000UL, 10000);  // 10ms ticks

    /* Init PLIC (optional) */
    plic_init();

    /* Jump to first task - scheduler will take over via timer */
    uart_puts("Jumping to taskA...\n");
    taskA();

    /* Should never reach here */
    uart_puts("ERROR: Returned from task!\n");
    while (1) {
        wfi();
    }
}
