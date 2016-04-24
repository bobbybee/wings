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

#ifndef _KSTANDARD_H
#define _KSTANDARD_H

// (freestanding) integer types
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

inline void outb(uint16_t port, uint8_t byte) {
    __asm__("outb %0, %1" : : "a"(byte), "Nd"(port));
}

inline uint8_t inb(uint16_t port) {
    uint8_t out;
    __asm__("inb %1, %0" : "=a"(out) : "Nd"(port));
    return out;
}

#endif
