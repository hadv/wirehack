# Toolchain
CC      = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy
QEMU    = qemu-system-riscv64

# Flags
CFLAGS  = -nostdlib -march=rv64imac -mabi=lp64 -Ttext=0x80000000

# Targets
all: hello.bin

hello.elf: hello.S
	$(CC) $(CFLAGS) -o $@ $<

hello.bin: hello.elf
	$(OBJCOPY) -O binary $< $@

run: hello.bin
	$(QEMU) -machine virt -nographic -bios none -kernel $<

clean:
	rm -f hello.elf hello.bin
