.section .text
    .globl trap_vector
trap_vector:
    addi sp, sp, -32
    sd   ra, 24(sp)
    sd   a0, 16(sp)
    sd   a1, 8(sp)
    sd   a2, 0(sp)

    csrr a0, mcause
    csrr a1, mepc
    csrr a2, mtval
    call trap_handler

    ld   a2, 0(sp)
    ld   a1, 8(sp)
    ld   a0, 16(sp)
    ld   ra, 24(sp)
    addi sp, sp, 32
    mret
