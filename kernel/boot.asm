; WINGS Operating System
; Copyright (C) 2016 Alyssa Rosenzweig
; 
; This file is part of WINGS.
; 
; WINGS is free software: you can redistribute it and/or modify
; it under the terms of the GNU Affero General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; WINGS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with WINGS.  If not, see <http://www.gnu.org/licenses/>.

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

section .stack:
stackBottom:
times 16384 db 0
stackTop:

; bootstrap
section .text:
global _start

extern initGDT
extern initIDT

_start:
    mov esp, stackTop

    cli
    call initGDT
    call initIDT
    call initPIC
    
    push 0xFF
    push 0xFD
    call maskPIC

    sti

.loop:
    hlt ; hlt for power efficiency
    jmp .loop

; wither into oblivion
    cli
.hang:
    hlt
    jmp .hang


; void loadGDT(void* descriptor)
global loadGDT
loadGDT:
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
    ret

; ISR stub macros
%macro isr_code 1
    global isr%1
    isr%1:
        push %1
        jmp isrHandlerInterm
%endmacro

%macro isr_stub 1
    global isr%1
    isr%1:
        push 42
        push %1
        jmp isrHandlerInterm
%endmacro

%macro irq 1
    global irq%1
    irq%1:
        push 0xDEADBEEF
        push (32+%1)
        jmp isrHandlerInterm
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
isr_code 17
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
isr_code 30
isr_stub 31

; IRQ handlers

irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15

extern isrHandler
isrHandlerInterm:
    push eax
    push ecx
    push edx
    push ebx
    push ebp
    push esi
    push edi
    push ds
    push es
    push fs
    push gs

    mov ebp, 0x10
    mov ds, ebp
    mov es, ebp
    mov fs, ebp
    mov gs, ebp

    mov ebx, esp
    sub esp, 4
    and esp, 0xFFFFFF00

    push ebx
    call isrHandler

    mov esp, ebx

    pop gs
    pop fs
    pop es
    pop ds
    pop edi
    pop esi
    pop ebp
    pop ebx
    pop edx
    pop ecx
    pop eax

    add esp, 8
    iret

; PIC remapping code
global initPIC

initPIC:
    push bx

    ; save state
    ; bh contains master pic state
    ; bl contains slave pic state
    in al, 0x21
    mov bh, al
    in al, 0xA1
    mov bl, al

    ; meta-initialize
    mov al, 0x11
    out 0x20, al
    mov al, 0
    out 0x80, al
    mov al, 0x11
    out 0xA0, al
    mov al, 0x00
    out 0x80, al

    ; new offsets
    mov al, 0x20
    out 0x21, al
    mov al, 0x00
    out 0x80, al
    mov al, 0x28
    out 0xA1, al
    mov al, 0x00
    out 0x80, al

    ; black magic from the osdev wiki
    mov al, 0x04
    out 0x21, al
    mov al, 0x00
    out 0x80, al
    mov al, 0x02
    out 0xA1, al
    mov al, 0x00
    out 0x80, al
    mov al, 0x01
    out 0x21, al
    mov al, 0x00
    out 0x80, al
    mov al, 0x01
    out 0xA1, al
    mov al, 0x00
    out 0x80, al

    ; restore state
    out 0xA1, al
    mov al, ah
    out 0x21, al
    
    pop bx
    ret

global maskPIC
; void maskPIC(int maskMaster, int maskSlave)
; passes full words for my sanity -- besides, this should only be called once

maskPIC:
    mov eax, [esp + 4]
    out 0x21, eax
    mov eax, [esp + 8]
    out 0xA1, eax
    ret
