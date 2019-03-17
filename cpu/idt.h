#ifndef MURLOC_OS_IDT_H
#define MURLOC_OS_IDT_H

#include "../libc/stdint.h"

#define IDT_ENTRIES_MAX 256

typedef struct __idt_entry
{
	uint16_t    base_low;
	uint16_t    segment_selector;
	uint8_t     always_zero;
	uint8_t     flags;
	uint16_t    base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct __idt_gate
{
	uint16_t    size;
	uint32_t    address;
} __attribute__((packed)) idt_t;

void idt_flush(idt_t* idt_ptr);

void idt_initialize();

void idt_entry_set(uint16_t index, uint32_t base, uint16_t segment_selector, uint8_t flags);

#endif //MURLOC_OS_IDT_H
