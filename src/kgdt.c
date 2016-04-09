/**
 * Global Descriptor Table implementation
 */

#include <kgdt.h>

uint8_t gdtTable[8 * 3];

void initGDT() {
    gdtEntry(table, 0, 0, GDT_PRESENT | GDT_RING, GDT_SIZE);
    gdtEntry(table, 1, 0xFFFFFFFF, GDT_PRESENT | GDT_RING0 | GDT_EXECUTABLE, GDT_SIZE);
    gdtEntry(table, 2, 0xFFFFFFFF, GDT_PRESENT | GDT_RING0, GDT_SIZE);
    loadGDT(&gdtTable, (3 * 8) - 1);
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

    entry[0] = limit & 0x000000FF;
    entry[1] = (limit & 0x000FF00) >> 8;
    entry[2] = base & 0x000000FF;
    entry[3] = (base & 0x0000FF00) >> 8;
    entry[4] = (base & 0x00FF0000) >> 16;
    entry[5] = access;
    entry[6] = ((limit & 0x00F0000) >> 16) | ((flags & 0x0F) << 4);
    entry[7] = (base & 0xFF000000) >> 24;
}
