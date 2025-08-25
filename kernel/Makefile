CROSS = riscv64-unknown-elf-
CC    = $(CROSS)gcc
AS    = $(CROSS)as
LD    = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy
QEMU  = qemu-system-riscv64

CFLAGS = -Wall -O2 -nostdlib -ffreestanding -march=rv64imac_zicsr -mabi=lp64 -mcmodel=medany
LDFLAGS = -T linker.ld

all: kernel.elf kernel.bin

kernel.elf: _start.o trap.o kernel.o linker.ld
	$(CC) $(CFLAGS) -o $@ _start.o trap.o kernel.o $(LDFLAGS)

kernel.bin: kernel.elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

run: kernel.bin
	$(QEMU) -machine virt -nographic -bios none -kernel kernel.bin

clean:
	rm -f *.o *.elf *.bin
