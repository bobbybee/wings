/**
 * WINGS
 * welcome to kernel space!
 */

#include <kstandard.h>
#include <ktextvga.h>
#include <kgdt.h>
#include <kidt.h>

void kmain() {
    kputs("Hello, World!\n");
    initGDT();
    initIDT();
    //__asm__("int $6");
    for(;;);
}
