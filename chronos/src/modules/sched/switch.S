# switch.S - RISC-V context switch implementation
# void swtch(context_t **old_ctx, context_t *new_ctx)
# a0 = &old_ctx (pointer to pointer where we store current context)
# a1 = new_ctx  (pointer to new context to restore)

    .section .text
    .globl swtch
    .align 2
swtch:
    # --- Save current context ---
    # Load the address where we should save the current context
    ld   t0, 0(a0)            # t0 = *old_ctx (address of current context struct)
    
    # Save callee-saved registers to current context
    sd   ra,   0(t0)          # offset 0:   save ra
    sd   sp,   8(t0)          # offset 8:   save sp
    sd   s0,  16(t0)          # offset 16:  save s0/fp
    sd   s1,  24(t0)          # offset 24:  save s1
    sd   s2,  32(t0)          # offset 32:  save s2
    sd   s3,  40(t0)          # offset 40:  save s3
    sd   s4,  48(t0)          # offset 48:  save s4
    sd   s5,  56(t0)          # offset 56:  save s5
    sd   s6,  64(t0)          # offset 64:  save s6
    sd   s7,  72(t0)          # offset 72:  save s7
    sd   s8,  80(t0)          # offset 80:  save s8
    sd   s9,  88(t0)          # offset 88:  save s9
    sd   s10, 96(t0)          # offset 96:  save s10
    sd   s11, 104(t0)         # offset 104: save s11

    # --- Load new context ---
    # a1 already points to new_ctx
    ld   ra,   0(a1)          # offset 0:   restore ra
    ld   sp,   8(a1)          # offset 8:   restore sp
    ld   s0,  16(a1)          # offset 16:  restore s0/fp
    ld   s1,  24(a1)          # offset 24:  restore s1
    ld   s2,  32(a1)          # offset 32:  restore s2
    ld   s3,  40(a1)          # offset 40:  restore s3
    ld   s4,  48(a1)          # offset 48:  restore s4
    ld   s5,  56(a1)          # offset 56:  restore s5
    ld   s6,  64(a1)          # offset 64:  restore s6
    ld   s7,  72(a1)          # offset 72:  restore s7
    ld   s8,  80(a1)          # offset 80:  restore s8
    ld   s9,  88(a1)          # offset 88:  restore s9
    ld   s10, 96(a1)          # offset 96:  restore s10
    ld   s11, 104(a1)         # offset 104: restore s11

    # Return to the new context (ra now points to new task's return address)
    ret

