#include <cpu/idt.h>
#include <cpu/io.h>
#include <cpu/8259pic.h>
#include <string.h>
#include <stdio.h>
#include <driver/framebuf.h>

idt_t idt;
idt_entry_t idt_entries[IDT_ENTRIES_MAX];

interrupt_handler_t handlers[IDT_ENTRIES_MAX];

const char *fault_messages[] =
{
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void idt_flush(idt_t* idt_ptr)
{
	asm("lidt (%0)" : : "r" (idt_ptr));
}

void idt_initialize()
{
	idt.size = (sizeof(idt_entry_t) * IDT_ENTRIES_MAX) - 1;
	idt.address = (uint32_t) &idt_entries;

	IDT_ENTRY_DECLARE(0)
	IDT_ENTRY_DECLARE(1)
	IDT_ENTRY_DECLARE(2)
	IDT_ENTRY_DECLARE(3)
	IDT_ENTRY_DECLARE(4)
	IDT_ENTRY_DECLARE(5)
	IDT_ENTRY_DECLARE(6)
	IDT_ENTRY_DECLARE(7)
	IDT_ENTRY_DECLARE(8)
	IDT_ENTRY_DECLARE(9)
	IDT_ENTRY_DECLARE(10)
	IDT_ENTRY_DECLARE(11)
	IDT_ENTRY_DECLARE(12)
	IDT_ENTRY_DECLARE(13)
	IDT_ENTRY_DECLARE(14)
	IDT_ENTRY_DECLARE(15)
	IDT_ENTRY_DECLARE(16)
	IDT_ENTRY_DECLARE(17)
	IDT_ENTRY_DECLARE(18)
	IDT_ENTRY_DECLARE(19)
	IDT_ENTRY_DECLARE(20)
	IDT_ENTRY_DECLARE(21)
	IDT_ENTRY_DECLARE(22)
	IDT_ENTRY_DECLARE(23)
	IDT_ENTRY_DECLARE(24)
	IDT_ENTRY_DECLARE(25)
	IDT_ENTRY_DECLARE(26)
	IDT_ENTRY_DECLARE(27)
	IDT_ENTRY_DECLARE(28)
	IDT_ENTRY_DECLARE(29)
	IDT_ENTRY_DECLARE(30)
	IDT_ENTRY_DECLARE(31)

	/* remap IRQs */
	outb(PIC1_COMMAND, 0x11);
	outb(PIC2_COMMAND, 0x11);
	outb(PIC1_DATA, 0x20);
	outb(PIC2_DATA, 0x28);
	outb(PIC1_DATA, 0x04);
	outb(PIC2_DATA, 0x02);
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01);
	outb(PIC1_DATA, 0x0);
	outb(PIC2_DATA, 0x0);

	IDT_ENTRY_DECLARE(32)
	IDT_ENTRY_DECLARE(33)
	IDT_ENTRY_DECLARE(34)
	IDT_ENTRY_DECLARE(35)
	IDT_ENTRY_DECLARE(36)
	IDT_ENTRY_DECLARE(37)
	IDT_ENTRY_DECLARE(38)
	IDT_ENTRY_DECLARE(39)
	IDT_ENTRY_DECLARE(40)
	IDT_ENTRY_DECLARE(41)
	IDT_ENTRY_DECLARE(42)
	IDT_ENTRY_DECLARE(43)
	IDT_ENTRY_DECLARE(44)
	IDT_ENTRY_DECLARE(45)
	IDT_ENTRY_DECLARE(46)
	IDT_ENTRY_DECLARE(47)

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

uint32_t interrupt_handler_register(uint32_t interrupt, interrupt_handler_t handler)
{
	if (interrupt > IDT_ENTRIES_MAX || handlers[interrupt] != NULL)
	{
		return 1;
	}

	handlers[interrupt] = handler;
	return 0;
}

void interrupt_handler(cpu_state_t cpu_state, idt_response_t idt_response, stack_state_t stack_state)
{
	uint32_t index = idt_response.index;

	/* interrupt is not an IRQ but an ISR fault */
	if (index < 32)
	{
		char red_on_black = FB_COLOR_COMBINE(FB_RED, FB_BLACK);

		printf("\n\n");
		fb_puts("FAULT: ", -1, -1, red_on_black);
		fb_puts(fault_messages[index], -1, -1, red_on_black);
		printf("\nHalting the system!");

		asm("hlt");
		return;
	}

	if (handlers[idt_response.index] != NULL)
	{
		handlers[idt_response.index](cpu_state, idt_response, stack_state);
	}
}
