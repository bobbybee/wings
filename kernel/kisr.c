/*
 * WINGS Operating System
 * Copyright (C) 2016 Alyssa Rosenzweig
 * 
 * This file is part of WINGS.
 * 
 * WINGS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * WINGS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with WINGS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <kstandard.h>
#include <ktextvga.h>
#include <kps2keyboard.h>

// generic interrupt handler

typedef struct {
    uint32_t gs, fs, ds, es;
    uint32_t edi, esi, ebp, ebx, edx, ecx, eax;
    uint32_t number, error;
    uint32_t cs, eflags, esp, ss;
} interrupt_registers;

void exceptionHandler(uint32_t number) {
    kputs("Received exception: ");
    kputnum(number, 16);
    kputchar('\n');
}

void irqHandler(uint32_t number) {
    if(number == 1) {
        ps2KeyboardIRQ();
    } else {
        kputs("Received unhandled IRQ: ");
        kputnum(number, 16);
        kputchar('\n');
    }

    // acknowledge IRQ
    if(number > 0x8) outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void isrHandler(interrupt_registers* context) {
    if(context->number >= 32) irqHandler(context->number - 32);
    else                      exceptionHandler(context->number);
}
