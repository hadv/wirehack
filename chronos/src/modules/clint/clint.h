#pragma once
#include <stdint.h>
void clint_timer_init(uint64_t hz, uint64_t interval_us);
void clint_timer_isr(void);
