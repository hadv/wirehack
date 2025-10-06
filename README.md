# Wirehack 🔧

A hacker-style bare-metal playground for learning **RISC-V assembly, C, and OS development** on QEMU. From simple "Hello World" to a preemptive multitasking kernel!

## 🎯 What's Inside

This repository contains a progressive learning path from basic assembly to a functional mini-kernel with interrupts and scheduling:

### 📚 Learning Modules

1. **Assembly Basics** (`asm/`) - Pure RISC-V assembly programs
2. **Bare-Metal C** (`c/`) - C programs without standard library
3. **Chronos Kernel** (`chronos/`) - Full-featured mini-kernel with:
   - ✅ Modular architecture
   - ✅ Timer interrupts (CLINT)
   - ✅ External interrupts (PLIC)
   - ✅ UART driver
   - ✅ **Preemptive multitasking scheduler**
   - ✅ Context switching

## 📂 Repository Structure

```text
wirehack/
├── asm/                    # Assembly demos
│   └── hello/              # Hello UART in pure assembly
├── c/                      # Bare-metal C demos
│   ├── hello/              # Hello World in C
│   └── kernel/             # Early kernel experiments
├── chronos/                # 🌟 Full-featured mini-kernel
│   ├── src/
│   │   ├── asm/            # Boot code and trap handlers
│   │   ├── kernel.c        # Main kernel logic
│   │   └── modules/        # Modular kernel subsystems
│   │       ├── clint/      # Timer interrupt driver
│   │       ├── plic/       # Interrupt controller
│   │       ├── uart/       # Serial port driver
│   │       └── sched/      # 🆕 Preemptive scheduler
│   ├── docs/               # Detailed documentation
│   └── Makefile            # Modular build system
├── docs/                   # Learning guides
│   ├── roadmap.md          # Learning roadmap
│   └── clint_vs_plic.md    # Interrupt controllers guide
├── include/                # Shared headers
├── scripts/                # Build helpers
└── tools/                  # Analysis tools

```

## 🚀 Quick Start

### Run Assembly Demo
```bash
cd asm/hello
make run
```

### Run C Demo
```bash
cd c/hello
make run
```

### Run Chronos Kernel (Recommended!)
```bash
cd chronos
make run
```

Expected output:
```
[CLINT] timer tick, task=0
[CLINT] timer tick, task=1
[CLINT] timer tick, task=0
...
```

The alternating task IDs show **preemptive multitasking** in action! 🎉

## 🌟 Chronos Kernel Highlights

The **Chronos** mini-kernel is the crown jewel of this repository, featuring:

### Modular Architecture
- Clean separation of kernel subsystems
- Each module is self-contained with its own directory
- Easy to understand, modify, and extend

### Interrupt Support
- **CLINT** (Core-Local Interruptor) for timer interrupts
- **PLIC** (Platform-Level Interrupt Controller) for external interrupts
- Proper trap handling with interrupt routing

### Preemptive Scheduler
- **Context switching** using RISC-V callee-saved registers
- **Cooperative scheduling** - tasks can yield voluntarily
- **Preemptive scheduling** - timer-driven task switches (10ms)
- Round-robin between tasks
- xv6-style implementation

### Documentation
- [`chronos/README.md`](chronos/README.md) - Kernel overview
- [`chronos/docs/scheduler.md`](chronos/docs/scheduler.md) - Scheduler deep dive
- [`chronos/docs/IMPLEMENTATION_SUMMARY.md`](chronos/docs/IMPLEMENTATION_SUMMARY.md) - Implementation details

## 📖 Learning Path

Follow the [roadmap](docs/roadmap.md) for a structured learning journey:

1. **Basics** - RISC-V ISA, registers, UART I/O
2. **Assembly** - Hello World, loops, string printing
3. **Bare-Metal C** - C without stdlib, linker scripts
4. **Mini Kernel** - Boot code, interrupts, drivers
5. **Advanced** - Multitasking, scheduling, OS concepts

## 🛠️ Prerequisites

- **RISC-V Toolchain**: `riscv64-unknown-elf-gcc`
- **QEMU**: `qemu-system-riscv64`
- **Make**: Build automation

### macOS Installation
```bash
brew install riscv-gnu-toolchain qemu
```

### Linux Installation
```bash
# Ubuntu/Debian
sudo apt-get install gcc-riscv64-unknown-elf qemu-system-misc

# Arch Linux
sudo pacman -S riscv64-elf-gcc qemu-arch-extra
```

## 🎓 Key Concepts Covered

- ✅ RISC-V assembly programming (RV64IMAC)
- ✅ Memory-mapped I/O (UART, CLINT, PLIC)
- ✅ Bare-metal C programming
- ✅ Linker scripts and memory layout
- ✅ Interrupt handling (M-mode)
- ✅ Context switching and task management
- ✅ Preemptive multitasking
- ✅ Modular kernel architecture

## 📚 Resources

- [RISC-V Specifications](https://riscv.org/technical/specifications/)
- [QEMU RISC-V Documentation](https://www.qemu.org/docs/master/system/target-riscv.html)
- [xv6-riscv](https://github.com/mit-pdos/xv6-riscv) - Educational OS
- [RISC-V Assembly Programmer's Manual](https://github.com/riscv-non-isa/riscv-asm-manual)

## 🤝 Contributing

This is a personal learning repository, but feel free to:
- Open issues for questions or suggestions
- Submit PRs for improvements or fixes
- Use this as a template for your own RISC-V learning journey

## 📝 License

This project is open source and available for educational purposes.

## 🎯 Project Status

- ✅ Assembly demos working
- ✅ Bare-metal C demos working
- ✅ Chronos kernel with interrupts
- ✅ Modular architecture implemented
- ✅ Preemptive scheduler working
- 🚧 Future: More tasks, priorities, synchronization primitives

---

> **Hack, learn, repeat** 😎
>
> *From "Hello World" to a multitasking kernel - one instruction at a time!*
