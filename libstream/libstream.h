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

    void* latest;
    size_t variableCount;
} ReactiveStream;

ReactiveStream makeStream();

void pushStream(ReactiveStream*, void*);

void registerVariable(ReactiveStream* stream);
void registerStream(ReactiveStream*, DataHandler);

void unregisterStream(ReactiveStream* stream, DataHandler handler);
void unregisterVariable(ReactiveStream* stream);

#endif
