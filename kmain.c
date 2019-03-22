#include <stdio.h>
#include <string.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <driver/timer.h>
#include <driver/keyboard.h>
#include <driver/framebuf.h>

int kmain()
{
	gdt_initialize();
	idt_initialize();

	interrupts_enable();

	timer_initialize();
	keyboard_initialize();

	fb_clear();

	fb_puts("\n\t\t\t\t\t\t\t< ", -1, -1, FB_COLOR_COMBINE(FB_GREEN, FB_BLACK));
	fb_puts("WELCOME TO MURLOCOS!", -1, -1, FB_COLOR_COMBINE(FB_L_GREEN, FB_BLACK));
	fb_puts(" >\n", -1, -1, FB_COLOR_COMBINE(FB_GREEN, FB_BLACK));

	printf("\t\t\t\t\t This is a small hobby project by myself,");
	printf("\n\t\t\t  trying to understand how an OS works under the hood!\n");

	for (int i = 0; i < 5; i++)
	{
		printf("\n");
	}

	printf("\n> ");
	return 0;
}
