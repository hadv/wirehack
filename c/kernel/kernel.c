#include <stdint.h>

#define CLINT_BASE  0x2000000
#define MTIMECMP    ((volatile uint64_t*)(CLINT_BASE + 0x4000))
#define MTIME       ((volatile uint64_t*)(CLINT_BASE + 0xBFF8))
#define UART0       ((volatile uint8_t*)0x10000000)

static inline void putchar(char c) {
    *UART0 = c;
}

static inline void print(const char *s) {
    while (*s) putchar(*s++);
}

void kernel_main() {
    print("kernel: boot\n");

    uint64_t now = *MTIME;
    *MTIMECMP = now + 100000;   // fire timer after ~0.1s

    print("timer armed, waiting for interrupts:\n");

    while (1) {
        asm volatile("wfi");
    }
}

void handle_trap() {
    print("[INTERRUPT] timer fired!\n");

    uint64_t now = *MTIME;
    *MTIMECMP = now + 100000;   // re-arm timer
}
