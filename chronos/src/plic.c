#include "include/defs.h"
#include "include/plic.h"
#include "include/uart.h"

#define UART_IRQ_ID 10

void plic_init(void) {
    uint32_t hart = (uint32_t)csr_read_mhartid();

    /* Set priority for UART > 0 */
    REG32(PLIC_PRIORITY(UART_IRQ_ID)) = 1;

    /* Enable UART IRQ for this hart's M-mode context */
    REG32(PLIC_MENABLE(hart)) = (1u << UART_IRQ_ID);

    /* Set threshold to 0 (accept all >0) */
    REG32(PLIC_MTHRESHOLD(hart)) = 0;

    /* Also enable machine external interrupt */
    csr_set_mie(1ULL << IRQ_M_EXT);
}

uint32_t plic_claim(void) {
    uint32_t hart = (uint32_t)csr_read_mhartid();
    return REG32(PLIC_MCLAIM(hart));
}

void plic_complete(uint32_t id) {
    uint32_t hart = (uint32_t)csr_read_mhartid();
    REG32(PLIC_MCLAIM(hart)) = id;
}
