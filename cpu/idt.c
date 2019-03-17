#include "idt.h"
#include "../libc/string.h"

idt_t idt;
idt_entry_t idt_entries[IDT_ENTRIES_MAX];

void idt_flush(idt_t* idt_ptr)
{
	asm("lidt (%0)" : : "r" (idt_ptr));
}

void idt_initialize()
{
	idt.size = (sizeof(idt_entry_t) * IDT_ENTRIES_MAX) - 1;
	idt.address = (uint32_t) &idt;

	/* empty for now */
	memset(&idt, 0, sizeof(idt_entry_t) * IDT_ENTRIES_MAX);
	idt_flush(&idt);
}

void idt_entry_set(uint16_t index, uint32_t base, uint16_t segment_selector, uint8_t flags)
{
	idt_entries[index].base_low = base & 0xFFFF;
	idt_entries[index].base_high = (base >> 16) & 0xFFFF;
	idt_entries[index].segment_selector = segment_selector;
	idt_entries[index].always_zero = 0;
	idt_entries[index].flags = flags;
}
