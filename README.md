# Wirehack

Wirehack is a hacker-style bare-metal playground for learning RISC-V assembly, C, and mini-kernel experiments on QEMU.

## Repository Structure

- asm/      ASM demos (Hello UART, strings, etc.)
- c/        Bare-metal C demos
- kernel/   Mini kernel experiments
- include/  Shared headers
- docs/     Notes and guides
- scripts/  Build/run helpers
- tools/    Analysis scripts

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
