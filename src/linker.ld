ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
STARTUP(bin/boot.o)
OUTPUT(bin/kernel.elf)

SECTIONS {
    . = 1M;

    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K) {
        *(.COMMON)
        *(.bss)
    }

    .bootstrap_stack BLOCK(4K) : ALIGN(4K) {
        *(.bootstrap_stack)
    }
}
