# Wirehack

Wirehack is a hacker-style bare-metal playground for learning RISC-V assembly, C, and mini-kernel experiments on QEMU.

## Repository Structure

```text
wirehack/
├── asm/          # ASM demos (Hello UART, string printing, macros)
├── c/            # Bare-metal C demos
├── kernel/       # Mini kernel experiments
├── include/      # Shared headers (UART base addresses, macros)
├── docs/         # Notes, guides, roadmap
├── scripts/      # Helper scripts to build/run demos
└── tools/        # Analysis tools (objdump scripts, memory map inspection)
```

## Quickstart

Run an ASM demo:

```bash
cd asm/hello
make run
```

Clean build files:

```bash
make clean
```

## Notes

- All demos target QEMU virt machine in -nographic mode.
- Each demo has its own Makefile.
- Keep learning iterative: add demo → test → commit.

> Hack, learn, repeat 😎
