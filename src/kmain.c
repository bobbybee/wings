/**
 * WINGS
 * welcome to kernel space!
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef signed int     ssize_t;

inline void kputchar(char);
inline void kmemcpy(void* dst, void* src, ssize_t length);

void kmain() {
    for(int i = 0; i < 2000; ++i) {
        kputchar('A' + (i % 26));
    }

    for(;;);
}

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
        *(VGABaseAddress + offset) = (0x2A << 8) | a;

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

inline void kmemcpy(void* dst, void* src, ssize_t length) {
    while(length--) {
        *((uint8_t*) dst) = *((uint8_t*) src);
        ++dst;
        ++src;
    }
}
