# Bare-metal "Hello, World\!" for RISC-V

### 1\. Giới thiệu

Đây là một dự án lập trình bare-metal đơn giản cho kiến trúc RISC-V, được xây dựng dựa trên nền tảng của repo `wirehack`. Mục tiêu của dự án là chuyển đổi chương trình "Hello, World\!" từ Assembly thuần túy sang C, sau đó biên dịch và chạy nó trên trình giả lập QEMU.

Dự án này là một bài học thực tế về quá trình khởi động (boot sequence), giao tiếp với phần cứng ở cấp độ thấp (Memory-Mapped I/O) và sử dụng các công cụ lập trình hệ thống như trình biên dịch (GCC) và trình liên kết (linker).

### 2\. Cấu trúc thư mục

```
c/
├── Makefile          # Script tự động hóa quá trình biên dịch và chạy
├── boot.S            # Mã khởi động Assembly
├── hello_world.c     # Mã nguồn C
└── linker.ld         # File chỉ định cách sắp xếp bộ nhớ
```

### 3\. Các file chính

#### a) `boot.S` - Mã khởi động

File này chứa mã Assembly đơn giản, đóng vai trò là "cầu nối" giữa CPU và chương trình C.

  - `_start`: Điểm khởi đầu mà CPU nhảy tới khi khởi động.
  - `la sp, __stack_top`: Thiết lập con trỏ stack (`sp`) để chương trình C có thể hoạt động.
  - `call main`: Gọi hàm `main` trong chương trình C của chúng ta.
  - `get_message`: Một hàm Assembly đặc biệt để tải địa chỉ của chuỗi "Hello, World\!" một cách an toàn, tránh lỗi `relocation truncated`.

#### b) `hello_world.c` - Chương trình C

Chương trình này viết bằng C để in ra một chuỗi ký tự bằng cách ghi trực tiếp vào địa chỉ bộ nhớ của cổng UART giả lập.

  - **`#include <stdint.h>`**: Cần thiết để sử dụng kiểu dữ liệu có kích thước cố định như `uint8_t`.
  - **`volatile`**: Đảm bảo trình biên dịch không tối ưu hóa các lệnh ghi vào địa chỉ của phần cứng.
  - **`uart_puts`**: Hàm tùy chỉnh để gửi chuỗi ký tự từng byte một.
  - **`main`**: Lấy địa chỉ chuỗi từ hàm Assembly, in nó ra màn hình và sau đó đi vào vòng lặp vô tận.

#### c) `linker.ld` - Script liên kết

File này hướng dẫn trình liên kết cách sắp xếp các phần của chương trình vào bộ nhớ RAM.

  - **`ENTRY(_start)`**: Chỉ định điểm vào của chương trình.
  - **`0x80000000`**: Đặt địa chỉ cơ sở cho toàn bộ chương trình.
  - **`.text`, `.rodata`, `.data`, `.bss`**: Sắp xếp các khu vực mã lệnh, dữ liệu chỉ đọc, dữ liệu đã khởi tạo và dữ liệu chưa khởi tạo một cách hợp lý.

#### d) `Makefile`

Tự động hóa toàn bộ quá trình:

  - **`all`**: Mục tiêu mặc định để tạo ra file `.bin` cuối cùng.
  - **`hello_world.elf: boot.o hello_world.o`**: Quy tắc liên kết, gộp cả `boot.o` và `hello_world.o` thành một file thực thi duy nhất.
  - **`-T linker.ld`**: Chỉ định sử dụng file `linker.ld` để kiểm soát bộ nhớ.
  - **`run`**: Lệnh chạy chương trình trên QEMU.

### 4\. Hướng dẫn sử dụng

Để biên dịch và chạy chương trình, hãy điều hướng đến thư mục `c/` và sử dụng các lệnh sau:

```bash
# Xóa các file cũ
make clean

# Biên dịch, liên kết và chạy chương trình
make run
```

### 5\. Những bài học quan trọng

1.  **Lập trình bare-metal đòi hỏi sự kiểm soát hoàn toàn:** Không có hệ điều hành, mọi thứ phải được thiết lập thủ công.
2.  **Lỗi `relocation truncated`:** Lỗi này xảy ra khi trình liên kết không thể truy cập dữ liệu vì nó quá xa mã lệnh. Cách giải quyết là sử dụng một `linker script` để sắp xếp lại bộ nhớ.
3.  **Assembly là công cụ mạnh mẽ:** Khi C không thể làm được việc, Assembly có thể được sử dụng để thực hiện các thao tác cấp thấp một cách chính xác.