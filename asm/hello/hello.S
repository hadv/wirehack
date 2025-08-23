    .section .text
    .globl _start
_start:
    # UART0 base address
    li t0, 0x10000000      

    # Địa chỉ chuỗi trong bộ nhớ
    la t1, message         

print_loop:
    lbu t2, 0(t1)          # load 1 byte từ chuỗi
    beqz t2, done          # nếu = 0 (null terminator) thì xong
    sb t2, 0(t0)           # ghi ra UART
    addi t1, t1, 1         # tăng con trỏ chuỗi
    j print_loop

done:
    j done                 # loop vô tận

    .section .rodata
message:
    .asciz "Hello RISC-V!\n"
