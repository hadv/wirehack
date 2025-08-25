    .section .text.boot
    .globl _start
_start:
    la sp, _stack_top        # set stack pointer

    la t0, trap_vector
    csrw mtvec, t0           # set trap vector

    li t0, 0x80              # enable timer interrupt (MTIE)
    csrs mie, t0

    li t0, 0x8               # enable global interrupt (MIE in mstatus)
    csrs mstatus, t0

    call kernel_main

1:  j 1b                     # hang if kernel_main returns
