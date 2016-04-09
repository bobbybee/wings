/**
 * WINGS
 * welcome to kernel space!
 */

#include <kstandard.h>
#include <ktextvga.h>
#include <kgdt.h>

void kmain() {
    kputs("Hello, World!\n");
    initGDT();
    for(;;);
}
