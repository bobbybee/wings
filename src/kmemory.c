#include <kmemory.h>

inline void kmemcpy(void* dst, void* src, ssize_t length) {
    while(length--) {
        *((uint8_t*) dst) = *((uint8_t*) src);
        ++dst;
        ++src;
    }
}

void kmemset(void* dst, uint8_t d, ssize_t length) {
    while(length--) {
        *((uint8_t*) dst) = d;
        ++dst;
    }
}
