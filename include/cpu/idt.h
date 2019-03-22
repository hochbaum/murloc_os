#ifndef MURLOC_OS_IDT_H
#define MURLOC_OS_IDT_H

#include "../stdint.h"
#include "cpu.h"

#define IDT_ENTRIES_MAX 256

/*!
 * Describes an entry (interrupt mapping) for the Interrupt
 * Descriptor Table.
 */
typedef struct __idt_entry
{
	uint16_t    base_low;
	uint16_t    segment_selector;
	uint8_t     always_zero;
	uint8_t     flags;
	uint16_t    base_high;
} __attribute__((packed)) idt_entry_t;

/*!
 * Describes the Interrupt Descriptor Table itself.
 */
typedef struct __idt_gate
{
	uint16_t    size;
	uint32_t    address;
} __attribute__((packed)) idt_t;

/*!
 * Describes a response from our Interrupt Descriptor Table.
 * Index is equal to the ISRs ID called.
 */
typedef struct __idt_response
{
	uint32_t    index;
	uint32_t    errno;
} __attribute__((packed)) idt_response_t;

/*!
 * This function loads the Interrupt Descriptor Table using
 * inlined assembly.
 *
 * @param idt_ptr A pointer to the IDT.
 */
void idt_flush(idt_t* idt_ptr);

/*!
 * Initializes ISRs and IRQs and calls idt_flush.
 */
void idt_initialize();

/*!
 * Adds an entry to the Interrupt Descriptor Table.
 *
 * @param index The index/ISR number for the interrupt.
 * @param base The base of the entry.
 * @param segment_selector The segment to use (0x08 for the kernel code segment).
 * @param flags The flags for the entry.
 */
void idt_entry_set(uint16_t index, uint32_t base, uint16_t segment_selector, uint8_t flags);

/*!
 * This function will be called from interrupt.s everytime an
 * interrupt is issued. It checks whether it's a fault or not
 * and calls the registered handler.
 *
 * @param cpu_state
 * @param idt_response
 * @param stack_state
 */
void interrupt_handler(cpu_state_t cpu_state, idt_response_t idt_response, stack_state_t stack_state);

/*!
 * Describes an interrupt handler.
 */
typedef void(*interrupt_handler_t)(cpu_state_t cpu_state, idt_response_t idt_response, stack_state_t stack_state);

/*!
 * Registers an interrupt handler for a specific interrupt number.
 *
 * @param interrupt The interrupt number to register the handler for.
 * @param handler The handler for the specified interrupt.
 *
 * @return 0 if successful, 1 if not.
 */
uint32_t interrupt_handler_register(uint32_t interrupt, interrupt_handler_t handler);

/*!
 * Globally enables interrupts.
 * Defined in interrupt.s.
 */
extern void interrupts_enable();

/*!
 * Globally disables interrupts.
 * Defined in interrupt.s.
 */
extern void interrupts_disable();

#define INTERRUPT_HANDLER_DECLARE(n)    extern void interrupt_handler_##n();
#define IDT_ENTRY_DECLARE(n)            idt_entry_set(n, (uint32_t) &interrupt_handler_##n, 0x08, 0x8E);

INTERRUPT_HANDLER_DECLARE(0)
INTERRUPT_HANDLER_DECLARE(1)
INTERRUPT_HANDLER_DECLARE(2)
INTERRUPT_HANDLER_DECLARE(3)
INTERRUPT_HANDLER_DECLARE(4)
INTERRUPT_HANDLER_DECLARE(5)
INTERRUPT_HANDLER_DECLARE(6)
INTERRUPT_HANDLER_DECLARE(7)
INTERRUPT_HANDLER_DECLARE(8)
INTERRUPT_HANDLER_DECLARE(9)
INTERRUPT_HANDLER_DECLARE(10)
INTERRUPT_HANDLER_DECLARE(11)
INTERRUPT_HANDLER_DECLARE(12)
INTERRUPT_HANDLER_DECLARE(13)
INTERRUPT_HANDLER_DECLARE(14)
INTERRUPT_HANDLER_DECLARE(15)
INTERRUPT_HANDLER_DECLARE(16)
INTERRUPT_HANDLER_DECLARE(17)
INTERRUPT_HANDLER_DECLARE(18)
INTERRUPT_HANDLER_DECLARE(19)
INTERRUPT_HANDLER_DECLARE(20)
INTERRUPT_HANDLER_DECLARE(21)
INTERRUPT_HANDLER_DECLARE(22)
INTERRUPT_HANDLER_DECLARE(23)
INTERRUPT_HANDLER_DECLARE(24)
INTERRUPT_HANDLER_DECLARE(25)
INTERRUPT_HANDLER_DECLARE(26)
INTERRUPT_HANDLER_DECLARE(27)
INTERRUPT_HANDLER_DECLARE(28)
INTERRUPT_HANDLER_DECLARE(29)
INTERRUPT_HANDLER_DECLARE(30)
INTERRUPT_HANDLER_DECLARE(31)

/* remapped IRQs */
INTERRUPT_HANDLER_DECLARE(32)
INTERRUPT_HANDLER_DECLARE(33)
INTERRUPT_HANDLER_DECLARE(34)
INTERRUPT_HANDLER_DECLARE(35)
INTERRUPT_HANDLER_DECLARE(36)
INTERRUPT_HANDLER_DECLARE(37)
INTERRUPT_HANDLER_DECLARE(38)
INTERRUPT_HANDLER_DECLARE(39)
INTERRUPT_HANDLER_DECLARE(40)
INTERRUPT_HANDLER_DECLARE(41)
INTERRUPT_HANDLER_DECLARE(42)
INTERRUPT_HANDLER_DECLARE(43)
INTERRUPT_HANDLER_DECLARE(44)
INTERRUPT_HANDLER_DECLARE(45)
INTERRUPT_HANDLER_DECLARE(46)
INTERRUPT_HANDLER_DECLARE(47)

#endif //MURLOC_OS_IDT_H
