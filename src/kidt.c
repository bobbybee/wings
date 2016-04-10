/**
 * Interrupt descriptor table (C half)
 */

#include <kidt.h>
#include <ktextvga.h>

uint16_t idtTable[4 * 33];

void idtEntry(uint16_t* table, int number, void* offset, uint16_t selector, uint8_t flags);

void initIDT() {
    kputs("Initializing idt..\n");
    idtEntry(idtTable, 0, isr0, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 1, isr1, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 2, isr2, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 3, isr3, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 4, isr4, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 5, isr5, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 6, isr6, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 7, isr7, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 8, isr8, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 9, isr9, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 10, isr10, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 11, isr11, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 12, isr12, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 13, isr13, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 14, isr14, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 15, isr15, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 16, isr16, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 17, isr17, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 18, isr18, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 19, isr19, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 20, isr20, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 21, isr21, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 22, isr22, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 23, isr23, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 24, isr24, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 25, isr25, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 26, isr26, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 27, isr27, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 28, isr28, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 29, isr29, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 30, isr30, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(idtTable, 31, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);

    idtEntry(idtTable, 32, irq0, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
   
    struct descriptorPtr ptr;
    ptr.limit = sizeof(idtTable) - 1;
    ptr.offset = &idtTable;
    loadIDT(&ptr);

    kputs("Initialized\n");
}

void idtEntry(
        uint16_t* table,
        int number,
        void* offset,
        uint16_t selector,
        uint8_t flags) {
    table[ (number * 4) + 0] = (uint32_t) offset & 0xFFFF;
    table[ (number * 4) + 1] = selector;
    table[ (number * 4) + 2] = flags << 8;
    table[ (number * 4) + 3] = (uint32_t) offset >> 16;

}
