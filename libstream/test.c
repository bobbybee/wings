/**
 * test program for working with streams
 * for clarification, this is meant to run under GNU/Linux, not WINGS
 */

#include <stdio.h>
#include "libstream.h"

void screenOut(void* node) {
    putchar( (char) node);
}

int main(int argc, char** argv) {
    ReactiveStream out = makeStream();
    registerStream(&out, screenOut);


    pushStream(&out, (void*) 'A');
}
