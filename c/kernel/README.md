# RISC-V Bare Metal Kernel – Timer Interrupt Demo

Dự án này là một kernel tối giản chạy trên RISC-V `virt` machine của QEMU, mục tiêu là **lập trình timer interrupt** bằng cách sử dụng **CLINT** và các thanh ghi CSRs (Control and Status Registers).

---

## 📂 Cấu trúc dự án

```
.
├── Makefile        # Quy tắc build và chạy trên QEMU
├── linker.ld       # Script định vị bộ nhớ (text, data, stack)
├── _start.S        # Điểm vào (_start), thiết lập stack, mtvec
├── trap.S          # Mã ASM để lưu/khôi phục context và gọi C handler
├── kernel.c        # Kernel chính, bật interrupt và lập trình timer
└── README.md       # Tài liệu
```

---

## 🔧 Build & Run

Yêu cầu:
- `riscv64-unknown-elf-gcc` toolchain
- `qemu-system-riscv64`

Build và chạy:

```bash
make clean
make run
```

Kết quả mong đợi trên QEMU (`-nographic`):

```
kernel: boot
timer armed, waiting for interrupts:
TIMER INTERRUPT FIRED!
TIMER INTERRUPT FIRED!
...
```

---

## ⚙️ Luồng khởi động

1. `_start.S`  
   - Thiết lập stack pointer  
   - Gán `mtvec` trỏ vào `trap_vector`  
   - Bật `mie` (Machine Interrupt Enable) và `mstatus.MIE`  
   - Nhảy vào `kernel_main`  

2. `kernel_main()`  
   - In thông báo boot  
   - Đọc `mtime` từ CLINT  
   - Đặt `mtimecmp = mtime + interval`  
   - Dừng chờ (`wfi`) để CPU ngủ và chỉ thức dậy khi có interrupt  

3. Khi `mtime >= mtimecmp`  
   - CLINT gửi timer interrupt  
   - CPU nhảy vào `trap_vector` (ASM)  
   - `trap.S` lưu context và gọi `handle_trap()` (C)  

4. `handle_trap()`  
   - Kiểm tra cause = timer interrupt  
   - In ra log  
   - Đặt lại `mtimecmp = mtime + interval` để chuẩn bị lần tiếp theo  
   - Quay lại kernel với `mret`  

---

## ⏰ Luồng Interrupt (Sơ đồ ASCII)

```pgsql
     +------------------+
     |    CLINT (SoC)   |
     | mtime  mtimecmp  |
     +---+----------+---+
         |   (mtime >= mtimecmp)?
         v
 +--------------------------+
 |   RISC-V Core (hart)     |
 |   mie.MTIE & mstatus.MIE |
 +------------+-------------+
              |
              v
     +------------------+
     | trap_vector (ASM)|
     | save regs, call C|
     +--------+---------+
              |
              v
     +------------------+
     | handle_trap()    |
     | set next timer   |
     +--------+---------+
              |
              v
     +------------------+
     | return (mret)    |
     +------------------+
```

---

## 📖 Ghi chú

- Cảnh báo `LOAD segment with RWX permissions` là do linker script đơn giản gộp tất cả section vào một segment, không ảnh hưởng đến demo.  
- Để debug, có thể dùng:
  ```bash
  riscv64-unknown-elf-objdump -d kernel.elf | less
  riscv64-unknown-elf-readelf -l kernel.elf
  ```
- Đây chỉ là skeleton để thực hành interrupt, chưa có driver UART/console chính thức.
