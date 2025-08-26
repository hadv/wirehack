#pragma once
#include <stdint.h>

/* CSR helpers */
static inline uint64_t read_csr(const char* csr_name) {
    uint64_t x = 0;
    /* This function can't take string CSR in inline asm portably; provide dedicated ones instead. */
    return x;
}

static inline uint64_t csr_read_mhartid(void) {
    uint64_t x; __asm__ volatile("csrr %0, mhartid" : "=r"(x)); return x;
}
static inline uint64_t csr_read_mcycle(void) {
    uint64_t x; __asm__ volatile("csrr %0, mcycle" : "=r"(x)); return x;
}
static inline uint64_t csr_read_mcause(void) {
    uint64_t x; __asm__ volatile("csrr %0, mcause" : "=r"(x)); return x;
}
static inline void csr_write_mepc(uint64_t x) {
    __asm__ volatile("csrw mepc, %0" :: "r"(x));
}
static inline void csr_set_mie(uint64_t x) {
    __asm__ volatile("csrs mie, %0" :: "r"(x));
}
static inline void csr_set_mstatus(uint64_t x) {
    __asm__ volatile("csrs mstatus, %0" :: "r"(x));
}
static inline void wfi(void) { __asm__ volatile("wfi"); }

/* Memory-mapped base addresses on QEMU virt */
#define UART0_BASE   0x10000000UL

/* ACLINT MTIMER on QEMU virt @ 10 MHz */
#define CLINT_BASE        0x02000000UL
#define CLINT_MTIMECMP(h) (CLINT_BASE + 0x4000 + 8*(h))
#define CLINT_MTIME       (CLINT_BASE + 0xBFF8)

/* PLIC base */
#define PLIC_BASE        0x0c000000UL
#define PLIC_PRIORITY(id)   (PLIC_BASE + 4*(id))
#define PLIC_PENDING        (PLIC_BASE + 0x001000)
#define PLIC_MENABLE(h)     (PLIC_BASE + 0x002000 + 0x80*(h))
#define PLIC_MTHRESHOLD(h)  (PLIC_BASE + 0x200000 + 0x2000*(h))
#define PLIC_MCLAIM(h)      (PLIC_BASE + 0x200004 + 0x2000*(h))

/* Helpers */
#define REG32(addr) (*(volatile uint32_t*)(uintptr_t)(addr))
#define REG64(addr) (*(volatile uint64_t*)(uintptr_t)(addr))

enum {
    IRQ_M_SOFT   = 3,
    IRQ_M_TIMER  = 7,
    IRQ_M_EXT    = 11,
};

/* UART 16550 registers (byte offsets) */
#define UART_RBR   0x00 /* receive buffer (read) */
#define UART_THR   0x00 /* transmit holding (write) */
#define UART_IER   0x01 /* interrupt enable */
#define UART_IIR   0x02 /* interrupt ident (read) */
#define UART_FCR   0x02 /* FIFO control (write) */
#define UART_LCR   0x03 /* line control */
#define UART_MCR   0x04 /* modem control */
#define UART_LSR   0x05 /* line status */
#define UART_MSR   0x06 /* modem status */
#define UART_SCR   0x07 /* scratch */

#define LSR_THRE   0x20
