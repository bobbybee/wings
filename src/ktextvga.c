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

void kputnum(int num, int base) {
    kputs("[num]");
    num++;
    base++;

}
