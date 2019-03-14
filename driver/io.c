#include "io.h"

void outb(unsigned short port, unsigned char data)
{
	asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned char inb(unsigned short port)
{
	unsigned char byte;
	asm("in %%dx, %%al" : "=a" (byte) : "d" (port));
	return byte;
}
