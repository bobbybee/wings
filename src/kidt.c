/**
 * Interrupt descriptor table (C half)
 */

#include <kidt.h>
#include <ktextvga.h>

uint8_t idtTable[8 * 32];

void initIDT() {
    kputs("Initializing idt..\n");
    idtEntry(&idtTable, 0, isr0, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr1, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr2, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr3, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr4, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr5, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr6, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr7, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr8, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr9, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr10, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr11, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr12, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr13, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr14, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr15, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr16, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr17, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr18, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr19, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr20, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr21, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr22, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr23, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr24, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr25, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr26, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr27, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr28, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr29, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr30, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(&idtTable, 0, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    
    struct descriptorPtr ptr;
    ptr.limit = sizeof(idtTable) - 1;
    ptr.offset = &idtTable;
    loadIDT(&ptr);

    kputs("Initialized\n");
}

void idtEntry(
        void* table,
        int number,
        void* offset,
        uint16_t selector,
        uint8_t flags) {
    uint8_t* entry = table + (number * 8);
    uint32_t _offset = (uint32_t) offset;

    entry[0] = _offset & 0x00FF;
    entry[1] = (_offset & 0xFF00) >> 8;
    entry[2] = selector & 0x00FF;
    entry[3] = (selector & 0xFF00) >> 8;
    entry[4] = 0;
    entry[5] = flags;
    entry[6] = (_offset >> 16) & 0x00FF;
    entry[7] = ((_offset >> 16) & 0xFF00) >> 8;
}
