#ifndef __LIBSTREAM_H
#define __LIBSTREAM_H

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
