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

#ifndef __KGDT_H
#define __KGDT_H

#include <kstandard.h>
#include <kdescriptor.h>

void initGDT();

void gdtEntry(void* table, int number, void* base, uint32_t limit, uint8_t access, uint8_t flags);

#define GDT_PRESENT (1<<7) | (1 << 4)

#define GDT_RING0 (0)
#define GDT_RING1 (1<<5)
#define GDT_RING2 (1<<6)
#define GDT_RING3 (1<<5 | 1<<6)

#define GDT_EXECUTABLE (1<<3)
#define GDT_DC (1<<2)
#define GDT_RW (1<<1)

#define GDT_GRANULARITY_PAGE (1<<3)
#define GDT_SIZE (1<<2)

#endif
