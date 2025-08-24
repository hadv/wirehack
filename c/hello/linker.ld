ENTRY(_start)

OUTPUT_ARCH(riscv)

SECTIONS
{
    . = 0x80000000;

    .text : {
        *(.text)
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }

    . = ALIGN(4);
    _end = .;
}