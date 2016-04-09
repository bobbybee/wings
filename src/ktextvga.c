#include <ktextvga.h>
#include <kmemory.h>

uint16_t* VGABaseAddress = (uint16_t*) 0xB8000;
int cursorX = 0, cursorY = 0;

inline void kputchar(char a) {
    if(a == '\n') {
        cursorY++;
        cursorX = 0;
    } else if(a == '\r') {
        cursorY++;
    } else if(a == '\b') {
        cursorX--;
    } else {
        int offset = (cursorY * 80) + cursorX;
        *(VGABaseAddress + offset) = (0x02 << 8) | a;

        cursorX++;

        if(cursorX == 80) {
            cursorY++;
            cursorX = 0;
        }
    }

    if(cursorY == 24) {
        kmemcpy(VGABaseAddress, VGABaseAddress + 80, (80 * 2 * (24 - 1)));
        cursorY--;
    }
}

inline void kputs(char* str) {
    while(*str != 0) kputchar(*(str++));
}

inline char kputnumeral(int numeral, int base) {
    if(base == 16 && numeral > 9) {
        return 'A' + numeral - 10;
    }

    return '0' + numeral;
}

void kputnum(int num, int base) {
    // handle special cases

    if(num == 0) {
        kputchar('0');
        return;
    }

    if(num < 0) {
        kputchar('-');
        num *= -1;
    }

    char buffer[32];
    int index = 0;

    while(num > 0 && index < 32) {
        buffer[index++] = kputnumeral(num % base, base);
        num /= base;
    }

    // print in reverse for the actual numeral
    while(index--) kputchar(buffer[index]);
}
