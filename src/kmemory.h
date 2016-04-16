#ifndef __KMEMORY_H
#define __KMEMORY_H

#include <kstandard.h>
void kmemcpy(void* dst, void* src, ssize_t length);
void kmemset(void* dst, uint8_t byte, ssize_t length);

#endif
