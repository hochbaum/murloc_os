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

	fb_puts("<", 27, 2, FB_COLOR_COMBINE(FB_GREEN, FB_BLACK));
	fb_puts("WELCOME TO MURLOCOS!", 29, 2, FB_COLOR_COMBINE(FB_L_GREEN, FB_BLACK));
	fb_puts(" >", -1, 2, FB_COLOR_COMBINE(FB_GREEN, FB_BLACK));
	fb_puts("This is a small hobby project by myself", 20, 3, FB_DEFAULT_ATTRIB);
	fb_puts("trying to understand how an OS works under the hood", 14, 4, FB_DEFAULT_ATTRIB);

	for (int i = 0; i < 5; i++)
	{
		printf("\n");
	}

	printf("\n> ");
	return 0;
}
