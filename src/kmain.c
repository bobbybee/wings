/**
 * WINGS
 * welcome to kernel space!
 */

#include <kstandard.h>
#include <ktextvga.h>
#include <kgdt.h>
#include <kidt.h>

void initPIC();
void maskPIC(int master, int slave);

void kmain() {
    kputs("Hello, World!\n");

    __asm__("cli");
    initGDT();
    initIDT();
//    initPIC();
    maskPIC(0xFF, 0xFF);
    __asm__("int $0x1");
    __asm__("sti");

    for(;;);
}
