#pragma once
#include <stdint.h>

/**
 * Context structure for RISC-V task switching
 * Contains callee-saved registers according to RISC-V ABI
 */
typedef struct context {
    uint64_t ra;     // x1  - return address
    uint64_t sp;     // x2  - stack pointer
    uint64_t s0;     // x8  - saved register / frame pointer
    uint64_t s1;     // x9  - saved register
    uint64_t s2;     // x18 - saved register
    uint64_t s3;     // x19 - saved register
    uint64_t s4;     // x20 - saved register
    uint64_t s5;     // x21 - saved register
    uint64_t s6;     // x22 - saved register
    uint64_t s7;     // x23 - saved register
    uint64_t s8;     // x24 - saved register
    uint64_t s9;     // x25 - saved register
    uint64_t s10;    // x26 - saved register
    uint64_t s11;    // x27 - saved register
} context_t;

