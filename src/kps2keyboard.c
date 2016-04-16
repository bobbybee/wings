#include <kstandard.h>
#include <ktextvga.h>

void ps2KeyboardIRQ() {
    char c = inb(0x60);
    kputnum(c, 16);
    kputchar('\n');
}
