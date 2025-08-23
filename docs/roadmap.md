# Wirehack Learning Roadmap

This roadmap guides you step-by-step through learning bare-metal RISC-V programming, from simple assembly to a mini kernel.

---

## 1. Basics

- Learn RISC-V ISA (RV64IMAC)
- Understand registers, immediate values, load/store
- Learn difference between `.S` and `.s` files
- UART basics: memory-mapped I/O
- Practice simple assembly: printing single characters via UART

---

## 2. ASM Demos

- Hello UART program
- Print strings via loop and null-terminated strings
- Using `.rodata` and `.asciz` for static strings
- Labels and loops in ASM
- Optional: macros for repeated code

---

## 3. Bare-Metal C

- Port simple UART programs from ASM to C
- Understand `_start` entry point
- Use `-nostdlib` and custom linker script
- Mix C + ASM routines
- Learn about volatile pointers for memory-mapped I/O

---

## 4. Mini Kernel

- Write `_start.S` as boot entry
- Linker scripts to place code in memory
- Implement basic I/O and infinite loops
- Explore timers, interrupts (optional)
- Expand kernel gradually: tasks, memory map, UART driver

---

## 5. Advanced Experiments

- Mix ASM + C for optimized routines
- Implement a simple printf over UART
- Bare-metal “Hello World OS”
- Explore RISC-V privileged instructions (S-mode, M-mode)
- Experiment with QEMU devices: CLINT, PLIC

---

## 6. Notes

- Each step has its own folder/demo in `asm/`, `c/`, `kernel/`.
- Use QEMU `-nographic` mode for all tests.
- Iterative learning: build → run → commit → improve.
- Keep the repo organized and document all experiments.
