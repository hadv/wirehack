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
MOD_DIR := src/modules
BUILD   := build

# Find all C and assembly files in src/ and src/modules/
SRCS_C_MAIN := $(wildcard $(SRC_DIR)/*.c)
SRCS_C_MODS := $(wildcard $(MOD_DIR)/*/*.c)
SRCS_S_ASM  := $(wildcard $(ASM_DIR)/*.S)
SRCS_S_MODS := $(wildcard $(MOD_DIR)/*/*.S)

# Generate object file paths
OBJS_C_MAIN := $(patsubst $(SRC_DIR)/%.c,$(BUILD)/%.o,$(SRCS_C_MAIN))
OBJS_C_MODS := $(patsubst $(MOD_DIR)/%.c,$(BUILD)/modules/%.o,$(SRCS_C_MODS))
OBJS_S_ASM  := $(patsubst $(ASM_DIR)/%.S,$(BUILD)/asm/%.o,$(SRCS_S_ASM))
OBJS_S_MODS := $(patsubst $(MOD_DIR)/%.S,$(BUILD)/modules/%.o,$(SRCS_S_MODS))
OBJS        := $(OBJS_C_MAIN) $(OBJS_C_MODS) $(OBJS_S_ASM) $(OBJS_S_MODS)

TARGET_ELF := $(BUILD)/kernel.elf
TARGET_BIN := $(BUILD)/kernel.bin

# Include paths: src/include and src/modules
INCLUDES := -I$(INC_DIR) -I$(MOD_DIR)

.PHONY: all clean run readelf objdump

all: $(TARGET_BIN)

$(BUILD):
	mkdir -p $(BUILD)/asm
	mkdir -p $(BUILD)/modules/clint
	mkdir -p $(BUILD)/modules/plic
	mkdir -p $(BUILD)/modules/uart
	mkdir -p $(BUILD)/modules/sched

$(BUILD)/asm/%.o: $(ASM_DIR)/%.S | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(BUILD)/modules/%.o: $(MOD_DIR)/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(BUILD)/modules/%.o: $(MOD_DIR)/%.S | $(BUILD)
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
