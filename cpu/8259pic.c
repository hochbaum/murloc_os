#include "8259pic.h"
#include "../driver/io.h"

void pic_acknowledge(uint32_t interrupt)
{
	if (interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT)
	{
		return;
	}

	if (interrupt < PIC2_START_INTERRUPT)
	{
		outb(PIC1_COMMAND, PIC_ACK);
	}
	else {
		outb(PIC2_COMMAND, PIC_ACK);
	}
}
