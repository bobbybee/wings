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
extern kmain

_start:
    mov esp, stack_top

    call kmain

; wither into oblivion
    cli
.hang:
    hlt
    jmp .hang


; void loadGDT(void* descriptor)
global loadGDT
loadGDT:
    cli

    ; load GDT structure
    mov eax, [esp + 4]
    lgdt [eax]
    
    jmp 0x08:codesegment
codesegment:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret

; void loadIDT(void* descriptor)
loadIDT:
    mov eax, [esp + 4]
    lidt [eax]
    return
