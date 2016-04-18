#ifndef __KDESCRIPTOR_H
#define __KDESCRIPTOR_H

void loadGDT(void* descriptor);
void loadIDT(void* descriptor);

struct descriptorPtr {
    uint16_t limit;
    void* offset;
} __attribute__((packed));

#endif
