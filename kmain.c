#include "libc/stdio.h"
#include "driver/framebuf.h"
#include "libc/string.h"
#include "mem/gdt.h"
#include "cpu/idt.h"
#include "driver/timer.h"

int kmain()
{
	gdt_initizalize();
	idt_initialize();

	interrupts_enable();

	timer_initialize();

	fb_clear();

	fb_puts("\n                           < ", -1, -1, FB_COLOR_COMBINE(FB_GREEN, FB_BLACK));
	fb_puts("WELCOME TO MURLOCOS!", -1, -1, FB_COLOR_COMBINE(FB_L_GREEN, FB_BLACK));
	fb_puts(" >\n", -1, -1, FB_COLOR_COMBINE(FB_GREEN, FB_BLACK));

	printf("                   This is a small hobby project by myself,");
	printf("\n             trying to understand how an OS works under the hood!\n");

	for (int i = 0; i < 5; i++)
	{
		printf("\n");
	}

	printf("\n> ");
	return 0;
}
