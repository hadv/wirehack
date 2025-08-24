// File: c/hello_world.c

#include <stdint.h>

// Khai báo hàm Assembly sẽ trả về con trỏ chuỗi
extern const char* get_message();

#define UART_BASE 0x10000000

void uart_putc(char c) {
    volatile uint8_t *uart = (volatile uint8_t *)UART_BASE;
    *uart = c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

int main() {
    // Lấy con trỏ đến chuỗi từ hàm Assembly
    const char* my_message = get_message();

    uart_puts(my_message);

    while (1);

    return 0;
}