#include "io.h"
#include "../libc/stdio.h"

void serial_configure_baud_rate(uint16_t com, uint16_t divisor)
{
	outb(SERIAL_DATA_PORT(com), SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_DATA_PORT(com), (uint8_t) ((divisor >> 8) & 0x00FF));
	outb(SERIAL_DATA_PORT(com), (uint8_t) (divisor & 0x00FF));
}

void serial_configure_line(uint16_t com)
{
	outb(SERIAL_DATA_PORT(com), 0x03);
}

uint32_t serial_is_transmit_fifo_empty(uint16_t com)
{
	return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void outb(uint16_t port, uint8_t data)
{
	asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint8_t inb(uint16_t port)
{
	unsigned char byte;
	asm("in %%dx, %%al" : "=a" (byte) : "d" (port));
	return byte;
}

void user_in(char* keybuffer)
{
	/* unused */
	(void)keybuffer;
	printf("> ");
}
