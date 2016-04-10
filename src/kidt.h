#ifndef __KIDT_H
#define __KIDT_H

#include <kstandard.h>
#include <kdescriptor.h>

void initIDT();

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#define IDT_GATE_INTERRUPT (0x6)
#define IDT_GATE_TRAP (0xF)
#define IDT_GATE_TASK (0x5)

#define IDT_GATE_PRESENT (1<<7)

#define IDT_MIN_RING0 (0)
#define IDT_MIN_RING1 (1<<5)
#define IDT_MIN_RING2 (1<<6)
#define IDT_MIN_RING3 ((1<<5)|(1<<6))

#endif
