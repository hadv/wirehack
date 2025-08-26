/* Chronos Linker Script for RISC-V RV64 on QEMU virt */

OUTPUT_ARCH(riscv)
ENTRY(_start)

PHDRS
{
  text PT_LOAD FLAGS(5); /* R X */
  data PT_LOAD FLAGS(6); /* R W */
}

MEMORY
{
  RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{
  . = ORIGIN(RAM);

  .text : ALIGN(16)
  {
    KEEP(*(.text._start))
    *(.text .text.*)
    *(.rodata .rodata.*)
  } > RAM :text

  . = ALIGN(16);
  .data :
  {
    *(.data .data.*)
  } > RAM :data

  . = ALIGN(16);
  .bss (NOLOAD) :
  {
    *(.sbss .sbss.*)
    *(.bss .bss.*)
    *(COMMON)
  } > RAM :data

  . = ALIGN(16);
  PROVIDE(_stack_top = . + 0x10000); /* 64 KB stack */
}
