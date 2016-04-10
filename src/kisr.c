#include <ktextvga.h>

// generic interrupt handler

void isrHandler(uint32_t offset, uint32_t number) {
    kputs("Received interrupt: ");
    kputnum(number, 16);
    kputs(" @ ");
    kputnum(offset, 16);
    kputchar('\n');
}
