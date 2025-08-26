    .section .text
    .globl trap_vector
trap_vector:
    addi sp, sp, -128        # save registers (simple stack frame)
    sd ra, 120(sp)
    sd t0, 112(sp)
    sd t1, 104(sp)
    sd t2, 96(sp)

    call handle_trap          # call C handler

    ld ra, 120(sp)
    ld t0, 112(sp)
    ld t1, 104(sp)
    ld t2, 96(sp)
    addi sp, sp, 128
    mret
