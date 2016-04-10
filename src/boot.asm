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
global loadIDT
loadIDT:
    mov eax, [esp + 4]
    lidt [eax]
    sti
    ret

; ISR stub macros
%macro isr_code 1
    global isr%1
    isr%1:
        ;cli
        ;push dword %1
        ;jmp isrHandlerInterm
        hlt 
%endmacro

%macro isr_stub 1
    global isr%1
    isr%1:
        ;cli
        ;push dword 0xDEADBEEF
        ;push dword %1
        ;jmp isrHandlerInterm
        hlt
%endmacro

; exception stubs
isr_stub 0
isr_stub 1
isr_stub 2
isr_stub 3
isr_stub 4
isr_stub 5
isr_stub 6
isr_stub 7
isr_code 8
isr_stub 9
isr_code 10
isr_code 11
isr_code 12
isr_code 13
isr_code 14
isr_stub 15
isr_stub 16
isr_stub 17
isr_stub 18
isr_stub 19
isr_stub 20
isr_stub 21
isr_stub 22
isr_stub 23
isr_stub 24
isr_stub 25
isr_stub 26
isr_stub 27
isr_stub 28
isr_stub 29
isr_stub 30
isr_stub 31

; general handler
;extern isrHandler
;isrHandlerInterm:
;   pusha
;
;   mov ax, ds
;   push ax
;
;   mov ax, 0x10
;   mov ds, ax
;   mov es, ax
;   mov fs, ax
;   mov gs, ax
;
;   call isrHandler

;   pop ax
;   mov ds, ax
;   mov es, ax
;   mov fs, ax
;   mov gs, ax

;   popa
;   add esp, 8
;   sti
;   iret

;isrHandlerInterm:
;    add esp, 8 ; clean up
;    iret
