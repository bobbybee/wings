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

#include <ktextvga.h>
#include <kmemory.h>

uint16_t* VGABaseAddress = (uint16_t*) 0xB8000;
int cursorX = 0, cursorY = 0;

inline void kputchar(char a) {
    if(a == '\n') {
        cursorY++;
        cursorX = 0;
    } else if(a == '\r') {
        cursorY++;
    } else if(a == '\b') {
        cursorX--;
    } else {
        int offset = (cursorY * 80) + cursorX;
        *(VGABaseAddress + offset) = (0x02 << 8) | a;

        cursorX++;

        if(cursorX == 80) {
            cursorY++;
            cursorX = 0;
        }
    }

    if(cursorY == 24) {
        kmemcpy(VGABaseAddress, VGABaseAddress + 80, (80 * 2 * (24 - 1)));
        cursorY--;
        kmemset(VGABaseAddress + (80 * 23), 0, (80 * 2));
    }
}

inline void kputs(char* str) {
    while(*str != 0) kputchar(*(str++));
}

inline char kputnumeral(int numeral, int base) {
    if(base == 16 && numeral > 9) {
        return 'A' + numeral - 10;
    }

    return '0' + numeral;
}

void kputnum(int num, int base) {
    // handle special cases

    if(num == 0) {
        kputchar('0');
        return;
    }

    if(num < 0) {
        kputchar('-');
        num *= -1;
    }

    char buffer[32];
    int index = 0;

    while(num > 0 && index < 32) {
        buffer[index++] = kputnumeral(num % base, base);
        num /= base;
    }

    // print in reverse for the actual numeral
    while(index--) kputchar(buffer[index]);
}
