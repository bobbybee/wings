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

#include <kstandard.h>
#include <ktextvga.h>

bool isShift = false;

char qwerty_US_lower[] = {
    0, 0, // 0, 1
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 2-E
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', // F -1C
    0, // 1D
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', // 1E-28
    0, 0, // 29, 2A
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', // 2B-35
    0, 0, 0, // 36-38
    ' ', // 39
};

char qwerty_US_upper[] = {
    0, 0, // 0, 1
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', // 2-E
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', // F-1C
    0, // 1D
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', // 1E-28
    0, 0, // 29, 2A
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', // 2B-35
    0, 0, 0, // 36-38
    ' ', // 39
};


void ps2KeyboardIRQ() {
    uint8_t c = inb(0x60);

    if(c < 128) {
        if(c < sizeof(qwerty_US_lower)) {
            if(qwerty_US_lower[c] == 0) {
                if(c == 0x2A) {
                    isShift = true;
                }
            } else {
                if(isShift) {
                    kputchar(qwerty_US_upper[c]);
                    isShift = false;
                } else {
                    kputchar(qwerty_US_lower[c]);
                }
            }
        }
    }
}
