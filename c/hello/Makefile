# Toolchain
CC      = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy
QEMU    = qemu-system-riscv64

# Flags
# Thêm cờ -Wall để bật cảnh báo và -g để debug
CFLAGS  = -nostdlib -march=rv64imac -mabi=lp64 -Wall -g -mcmodel=medlow

# Source files
# Liệt kê tất cả các file .o cần thiết
OBJS    = boot.o hello_world.o

# Targets
TARGET  = hello_world

all: $(TARGET).bin

# --- Quy tắc liên kết (Linking Rule) ---
# Để tạo file .elf, chúng ta cần tất cả các file .o
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -T linker.ld

# --- Quy tắc biên dịch (Compilation Rules) ---
# Quy tắc chung để tạo file .o từ file .c
boot.o: boot.S
	$(CC) $(CFLAGS) -c $< -o $@

# Quy tắc chung để tạo file .o từ file .S
hello_world.o: hello_world.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Quy tắc tiện ích (Utility Rules) ---
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

run: $(TARGET).bin
	$(QEMU) -machine virt -nographic -bios none -kernel $<

clean:
	rm -f *.o *.elf *.bin