; Kernel main for WINGS
; At the moment, it provides some legacy hardware drivers.

MBALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

; setup multiboot
section .multiboot:
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

; stack
section .bootstack:
align 4

stack_bottom:
resb 16384
stack_top:

; bootstrap
section .text:
global _start

_start:
    mov esp, stack_top

kmain:
    mov al, 'A'
    call vgaPutchar    
    call vgaPutchar    
    call vgaPutchar    
    call vgaPutchar    
    call vgaPutchar    
    call vgaPutchar    
    call vgaPutchar    
    call vgaPutchar    
    call vgaPutchar    
    call vgaPutchar    

    ; wither into oblivion
    cli
.hang:
    hlt
    jmp .hang

; 0xB8000 display driver

vgaPutchar:
    mov bl, al
    mov bh, 0x2A
    
    ; ((cursorY * 80) + (cursorX)) * 2
    mov eax, [cursorY]
    shl eax, 2
    add eax, [cursorY]
    shl eax, 4
    add eax, [cursorX]
    shl eax, 1
    add eax, 0xB8000

    mov word [eax], bx
    ret

section .data:
    cursorX dw 0
    cursorY dw 0
