.section .text._start
    .globl _start
_start:
    /* set up stack */
    la   sp, _stack_top

    /* set mtvec to trap_vector (direct mode) */
    la   t0, trap_vector
    csrw mtvec, t0

    /* enable machine timer interrupt (MTIE) and external interrupt (MEIE) */
    li   t0, (1 << 7) | (1 << 11)   /* MTIE=7, MEIE=11 */
    csrs mie, t0

    /* set MSTATUS.MIE = 1 (global enable) */
    li   t0, (1 << 3)               /* MIE bit */
    csrs mstatus, t0

    /* jump to C kernel main */
    la   t0, kernel_main
    jr   t0

    .size _start, . - _start
