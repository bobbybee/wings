#ifndef _KSTANDARD_H
#define _KSTANDARD_H

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef signed int     ssize_t;

inline void outb(uint16_t port, uint8_t byte) {
    __asm__("outb %0, %1" : : "a"(byte), "Nd"(port));
}

#endif
