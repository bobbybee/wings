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
