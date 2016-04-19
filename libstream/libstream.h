#ifndef __LIBSTREAM_H
#define __LIBSTREAM_H

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <stddef.h>

typedef void (*DataHandler)(void*);

typedef struct {
    DataHandler* handlers;
    size_t handlerCount;
    size_t allocatedCount;
} ReactiveStream;

ReactiveStream makeStream();
void pushStream(ReactiveStream*, void*);
void registerStream(ReactiveStream*, DataHandler);

#endif
