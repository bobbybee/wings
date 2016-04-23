/*
 * WINGS Operating System
 * Copyright (C) 2016 Alyssa Rosenzweig
 * 
 * This file is part of WINGS.
 * 
 * WINGS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * WINGS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with WINGS.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * reactive stream library,
 * designed to be used a supporting library for the WINGS userspace,
 * in addition to providing a common ABI for the kernel to use.
 */

#include <libstream.h>

ReactiveStream makeStream() {
    ReactiveStream out;
    out.handlers = malloc(1);
    out.handlerCount = 0;
    out.allocatedCount = 1;
    return out;
}

void pushStream(ReactiveStream* stream, void* node) {
    if(stream->variableCount) stream->latetst = node;

    for(int i = 0; i < stream->handlerCount; ++i) {
        stream->handlers[i](node);
    }
}

void registerStream(ReactiveStream* stream, DataHandler handler) {
    // ensure this is not a duplicate handler
    // this simplifies unregistering logic immensely
    // also, it's the correct behavior
    // TODO: should this trigger a warning?
    
    for(int i = 0; i < stream->handlerCount; ++i) {
        if(stream->handlers[i] == handler) return;
    }

    if(stream->handlerCount + 1 > stream->allocatedCount) {
        stream->handlers = realloc(stream->handlers, stream->allocatedCount * 2);
        stream->allocatedCount *= 2;
    }

    stream->handlers[stream->handlerCount++] = handler;
}

void registerVariable(ReactiveStream* stream) {
    stream->variableCount++;
}

void unregisterStream(ReactiveStream* stream, DataHandler handler) {
    // registerStream gaurentees there is only one handle
    for(int i = 0; i < stream->handlerCount; ++i) {
        if(stream->handlers[i] == handler) {
            if(stream->handlerCount > i + 1) {
                memmove(stream->handlers[i], stream->handlers[i + 1], stream->handlerCount - i);
            }

            stream->handlerCount--;
        }
    }
}

void unregisterVariable(ReactiveStream* stream) {
    stream->variableCount--;
}
