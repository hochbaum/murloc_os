#include "gdt.h"
#include "../libc/stdio.h"
#include "../libc/string.h"

/* may not be changed, as it's the pointer to our GDT. */
gdt_t gdt;
gdt_entry_t gdt_entries[GDT_ENTRIES_MAX];

void gdt_initizalize()
{
	gdt.address = (uint32_t) &gdt_entries;
	gdt.size = (sizeof(gdt_entry_t) * GDT_ENTRIES_MAX) - 1;

	gdt_entry_set(0, 0, 0, 0, 0);
	gdt_entry_set(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_entry_set(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_entry_set(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_entry_set(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	gdt_flush(&gdt);
}

void gdt_entry_set(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
	gdt_entries[index].base_low = base & 0xFFFF;
	gdt_entries[index].base_middle = (base >> 16) & 0xFF;
	gdt_entries[index].base_high = (base >> 24) & 0xFF;

	gdt_entries[index].limit_low = limit & 0xFFFF;

	gdt_entries[index].granularity = (limit >> 16) & 0x0F;
	gdt_entries[index].granularity |= granularity & 0xF0;

	gdt_entries[index].access = access;
}
