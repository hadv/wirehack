# Chronos Makefile
CROSS   ?= riscv64-unknown-elf-
CC      := $(CROSS)gcc
OBJCOPY := $(CROSS)objcopy
READELF := $(CROSS)readelf

ARCH    := -march=rv64imac_zicsr -mabi=lp64 -mcmodel=medany
CFLAGS  := -Wall -Wextra -O2 -ffreestanding -fno-common -nostdlib -nostartfiles $(ARCH)
ASFLAGS := $(ARCH)
LDFLAGS := -T linker.ld -nostdlib -nostartfiles $(ARCH)

SRC_DIR := src
ASM_DIR := src/asm
INC_DIR := src/include
BUILD   := build

SRCS_C  := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
SRCS_S  := $(wildcard $(ASM_DIR)/*.S)
OBJS    := $(patsubst $(SRC_DIR)/%.c,$(BUILD)/%.o,$(SRCS_C)) \
           $(patsubst $(ASM_DIR)/%.S,$(BUILD)/asm/%.o,$(SRCS_S))

TARGET_ELF := $(BUILD)/kernel.elf
TARGET_BIN := $(BUILD)/kernel.bin

INCLUDES := -I$(INC_DIR)

.PHONY: all clean run readelf objdump

all: $(TARGET_BIN)

$(BUILD):
	mkdir -p $(BUILD)/asm
	mkdir -p $(BUILD)

$(BUILD)/asm/%.o: $(ASM_DIR)/%.S | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(TARGET_ELF): $(OBJS) linker.ld | $(BUILD)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(TARGET_BIN): $(TARGET_ELF) | $(BUILD)
	$(OBJCOPY) -O binary $< $@

run: $(TARGET_BIN)
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel $(TARGET_BIN)

readelf: $(TARGET_ELF)
	$(READELF) -h -l $(TARGET_ELF)

clean:
	rm -rf $(BUILD)
