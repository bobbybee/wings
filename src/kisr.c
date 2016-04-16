#include <ktextvga.h>

// generic interrupt handler

void isrHandler(uint32_t number) {
    kputs("Received interrupt: ");
    kputnum(number, 16);
    kputchar('\n');
}

void irqHandler(uint32_t number) {
    kputs("Received IRQ: ");
    kputnum(number, 16);
    kputchar('\n');
}

