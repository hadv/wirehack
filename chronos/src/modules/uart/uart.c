#include "../../include/defs.h"
#include "uart.h"

static inline void mmio_write8(uintptr_t addr, uint8_t v) {
    *(volatile uint8_t*)addr = v;
}
static inline uint8_t mmio_read8(uintptr_t addr) {
    return *(volatile uint8_t*)addr;
}

void uart_init(void) {
    /* Enable FIFO, 8N1 config is default in QEMU */
    mmio_write8(UART0_BASE + UART_FCR, 0x07); /* enable & clear FIFOs */
    /* Optionally enable THRE interrupt to demo PLIC (not required): */
    // mmio_write8(UART0_BASE + UART_IER, 0x02);
}

void uart_putc(char c) {
    /* Poll for THR empty */
    while ((mmio_read8(UART0_BASE + UART_LSR) & LSR_THRE) == 0) { }
    mmio_write8(UART0_BASE + UART_THR, (uint8_t)c);
}

void uart_puts(const char* s) {
    while (*s) {
        if (*s == '\n') uart_putc('\r');
        uart_putc(*s++);
    }
}
