#include "timer.h"
#include "../libc/stdint.h"
#include "../cpu/cpu.h"
#include "../cpu/idt.h"
#include "io.h"
#include "../cpu/8259pic.h"

uint32_t tick;

static void handler_timer(cpu_state_t cpu_state, idt_response_t idt_response, stack_state_t stack_state)
{
	pic_acknowledge(32);

	/* unused */
	(void)cpu_state;
	(void)idt_response;
	(void)stack_state;

	tick++;
}

void timer_initialize()
{
	interrupt_handler_register(32, &handler_timer);

	uint32_t div = TIMER / TIMER_FREQUENCY;
	uint8_t low = div & 0xFF;
	uint8_t high = (div >> 8) & 0xFF;

	outb(0x43, 0x36);
	outb(0x40, low);
	outb(0x40, high);
}
