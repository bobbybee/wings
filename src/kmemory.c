#include <kmemory.h>

inline void kmemcpy(void* dst, void* src, ssize_t length) {
    while(length--) {
        *((uint8_t*) dst) = *((uint8_t*) src);
        ++dst;
        ++src;
    }
}
