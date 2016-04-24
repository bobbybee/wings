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

/**
 * Interrupt descriptor table (C half)
 */

#include <kidt.h>
#include <ktextvga.h>

typedef uint16_t IDTEntry[4];
IDTEntry idtTable[48];

void idtEntry(int number, void* offset, uint16_t selector, uint8_t flags);

void* idtOffsets[] = {
    isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7, isr8, isr9, isr10, isr11,
    isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19, isr20, isr21, isr22,
    isr23, isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31,

    irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7,
    irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15
};


void initIDT() {
    kputs("IDT initialization...\n");

    for(uint8_t gate = 0; gate < sizeof(idtOffsets) / sizeof(void*); ++gate) {
        idtEntry(gate, idtOffsets[gate], 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    }

    struct descriptorPtr ptr;
    ptr.limit = sizeof(idtTable) - 1;
    ptr.offset = &idtTable;
    loadIDT(&ptr);

    kputs("IDT Initialized\n");
}

void idtEntry(
        int number,
        void* offset,
        uint16_t selector,
        uint8_t flags) {
    idtTable[number][0] = (uint16_t) ((uint32_t) offset & 0xFFFF);
    idtTable[number][1] = selector;
    idtTable[number][2] = flags << 8;
    idtTable[number][3] = (uint16_t) ((uint32_t) offset >> 16);
}
