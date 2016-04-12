/**
 * Interrupt descriptor table (C half)
 */

#include <kidt.h>
#include <ktextvga.h>

typedef uint16_t IDTEntry[8];
IDTEntry idtTable[48];

void idtEntry(int number, void* offset, uint16_t selector, uint8_t flags);

void initIDT() {
    kputs("Initializing idt..\n");
    idtEntry(0, isr0, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(1, isr1, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(2, isr2, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(3, isr3, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(4, isr4, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(5, isr5, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(6, isr6, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(7, isr7, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(8, isr8, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(9, isr9, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(10, isr10, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(11, isr11, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(12, isr12, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(13, isr13, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(14, isr14, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(15, isr15, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(16, isr16, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(17, isr17, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(18, isr18, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(19, isr19, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(20, isr20, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(21, isr21, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(22, isr22, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(23, isr23, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(24, isr24, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(25, isr25, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(26, isr26, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(27, isr27, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(28, isr28, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(29, isr29, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(30, isr30, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);
    idtEntry(31, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_TRAP | IDT_MIN_RING0);

    idtEntry(32, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(33, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(34, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(35, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(36, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(37, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(38, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(39, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);

    idtEntry(40, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(41, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(42, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(43, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(44, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(45, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(46, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);
    idtEntry(47, isr31, 0x8, IDT_GATE_PRESENT | IDT_GATE_INTERRUPT | IDT_MIN_RING0);

    /*struct descriptorPtr ptr;
    ptr.limit = sizeof(idtTable) - 1;
    ptr.offset = &idtTable;
    loadIDT(&ptr);*/

    kputs("Initialized\n");
}

void idtEntry(
        int number,
        void* offset,
        uint16_t selector,
        uint8_t flags) {
    idtTable[number][0] = (uint32_t) offset & 0xFFFF;
    idtTable[number][1] = selector;
    idtTable[number][2] = flags << 8;
    idtTable[number][3] = (uint32_t) offset >> 16;
}
