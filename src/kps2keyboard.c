#include <kstandard.h>
#include <ktextvga.h>

typedef uint8_t bool;
#define false 0
#define true 1
#define NULL 0

bool isShift = false;

char qwerty_US_lower[] = {
    NULL, NULL, // 0, 1
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 2-E
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', // F -1C
    NULL, // 1D
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', // 1E-28
    NULL, NULL, // 29, 2A
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', // 2B-35
    NULL, NULL, NULL, // 36-38
    ' ', // 39
};

void ps2KeyboardIRQ() {
    uint8_t c = inb(0x60);

    if(c < 128) {
        if(c < sizeof(qwerty_US_lower)) {
            if(qwerty_US_lower[c] == NULL) {
                if(c == 0x2A) {
                    isShift = true;
                }
            } else {
                if(isShift) {
                    kputchar(qwerty_US_lower[c]);
                    isShift = false;
                } else {
                    kputchar(qwerty_US_lower[c]);
                }
            }
        }
    }
}
