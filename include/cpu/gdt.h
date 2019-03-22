#ifndef MURLOC_OS_GDT_H
#define MURLOC_OS_GDT_H

#include "../stdint.h"

#define GDT_ENTRIES_MAX 5

/*!
 * Describes an entry (segment) for the Global Descriptor Table.
 */
typedef struct __gdt_entry
{
	uint16_t    limit_low;
	uint16_t    base_low;
	uint8_t     base_middle;
	uint8_t     access;
	uint8_t     granularity;
	uint8_t     base_high;
} __attribute__((packed)) gdt_entry_t;

/*!
 * Describes the Global Descriptor Table itself.
 *
 * Address determines where the GDT is located whilst size is used,
 * to calculate the offset. It is equal to GDT_ENTRIES_MAX * sizeof(struct __gdt_gate) -1.
 */
typedef struct __gdt_gate
{
	uint16_t    size;
	uint32_t    address;
} __attribute__((packed)) gdt_t;

/*!
 * This function is defined in gdt.s. It loads the Global Descriptor Table
 * and updates the data segment offsets.
 *
 * Should be called whenever an entry was updated.
 */
extern void gdt_flush(gdt_t *gdt_ptr);

/*!
 * Initializes the Global Descriptor Table, used for segmentation of the memory.
 */
void gdt_initialize();

/*!
 * Adds an entry to the Global Descriptor table.
 * See GDT_ENTRIES_MAX for the maximum amount of entries.
 *
 * @param index The index of the entry.
 * @param base The base of the entry.
 * @param limit The limit of the entry.
 * @param access The access flag.
 * @param granularity The granularity to use.
 */
void gdt_entry_set(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

#endif //MURLOC_OS_GDT_H
