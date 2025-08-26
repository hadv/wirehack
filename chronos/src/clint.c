#include "include/defs.h"
#include "include/clint.h"
#include "include/uart.h"

/* QEMU virt mtimer: 10 MHz by default (seen in OpenSBI log) */
#define DEFAULT_MTIMER_HZ 10000000UL

static uint64_t tick_interval_cycles = 0;

static void clint_set_mtimecmp(uint64_t hart, uint64_t value) {
    REG64(CLINT_MTIMECMP(hart)) = value;
}

static uint64_t clint_get_mtime(void) {
    return REG64(CLINT_MTIME);
}

void clint_timer_init(uint64_t hz, uint64_t interval_us) {
    if (hz == 0) hz = DEFAULT_MTIMER_HZ;
    uint64_t hart = csr_read_mhartid();
    tick_interval_cycles = (hz / 1000000ULL) * interval_us;

    uint64_t now = clint_get_mtime();
    clint_set_mtimecmp(hart, now + tick_interval_cycles);

    /* Ensure MTIE enabled (done in _start as well) */
    csr_set_mie(1ULL << IRQ_M_TIMER);
}

void clint_timer_isr(void) {
    /* re-arm next tick */
    uint64_t hart = csr_read_mhartid();
    uint64_t now  = REG64(CLINT_MTIME);
    REG64(CLINT_MTIMECMP(hart)) = now + tick_interval_cycles;

    uart_puts("[CLINT] timer tick\n");
}
