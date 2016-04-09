#ifndef __KGDT_H
#define __KGDT_H

#include <kstandard.h>

extern void loadGDT(void* base, uint16_t limit);  
extern void loadIDT(void* base, uint16_t limit);  

void initGDT();
void initIDT();

void gdtEntry(void* table, int number, void* base, uint32_t limit, uint8_t access, uint8_t flags);

#define GDT_PRESENT (1<<7) | (1 << 4)

#define GDT_RING0 (0)
#define GDT_RING1 (1<<5)
#define GDT_RING2 (1<<6)
#define GDT_RING3 (1<<5 | 1<<6)

#define GDT_EXECUTABLE (1<<3)
#define GDT_DC (1<<2)
#define GDT_RW (1<<1)

#define GDT_GRANULARITY_PAGE (1<<3)
#define GDT_SIZE (1<<2)

#endif
