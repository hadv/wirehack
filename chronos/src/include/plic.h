#pragma once
#include <stdint.h>
void plic_init(void);
uint32_t plic_claim(void);
void plic_complete(uint32_t id);
