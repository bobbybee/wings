/**
 * Global Descriptor Table implementation
 */

#include <kgdt.h>
#include <ktextvga.h>

uint8_t gdtTable[8 * 3];

void initGDT() {
    gdtEntry(gdtTable, 0, 0, 0, 0, GDT_SIZE);
    gdtEntry(gdtTable, 1, 0, 0xFFFFFFFF, GDT_PRESENT | GDT_RING0 | GDT_RW | GDT_EXECUTABLE, GDT_SIZE);
    gdtEntry(gdtTable, 2, 0, 0xFFFFFFFF, GDT_PRESENT | GDT_RING0 | GDT_RW, GDT_SIZE);
    
    loadGDT(&gdtTable, sizeof(gdtTable));
}

void initIDT() {

}


void gdtEntry(
        void* table,
        int number,
        void* base,
        uint32_t limit,
        uint8_t access,
        uint8_t flags) {

    if(limit > 0xFFFF) {
        limit = limit >> 12;
        flags |= GDT_GRANULARITY_PAGE;
    }
    
    uint8_t* entry = table + (number * 8);
    uint32_t _base = (uint32_t) base;

    entry[0] = limit & 0x000000FF;
    entry[1] = (limit & 0x000FF00) >> 8;
    entry[2] = _base & 0x000000FF;
    entry[3] = (_base & 0x0000FF00) >> 8;
    entry[4] = (_base & 0x00FF0000) >> 16;
    entry[5] = access;
    entry[6] = ((limit & 0x00F0000) >> 16) | ((flags & 0x0F) << 4);
    entry[7] = (_base & 0xFF000000) >> 24;

    kputs("GDT Entry: ");
    kputnum(number, 10);
    kputs(", base: ");
    kputnum((uint32_t)base, 16);
    kputs(", limit: ");
    kputnum(limit, 16);
    kputs(", access: ");
    kputnum(access, 16);
    kputs(", flags: ");
    kputnum(flags, 16);
    kputchar('\n');
}
