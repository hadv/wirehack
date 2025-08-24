    .global _start
_start:
    la   sp, __stack_top
    call main
loop:
    j loop

# ----- Hàm để lấy địa chỉ của chuỗi -----
# Hàm này sẽ được gọi từ C
    .global get_message
get_message:
    la a0, message # Tải địa chỉ của chuỗi 'message' vào thanh ghi a0
    ret            # Trả về giá trị trong a0

# ----- Định nghĩa dữ liệu -----
    .section .rodata
message:
    .string "Hello from bare-metal C!\n"

# ----- Định nghĩa vùng nhớ cho Stack -----
    .section .bss
    .align 4
__stack_bottom:
    .space 4096
__stack_top: