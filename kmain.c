#include "libc/stdio.h"
#include "driver/framebuf.h"
#include "libc/string.h"
#include "mem/gdt.h"

int kmain()
{


	fb_clear();

	/* really need \t here :/ */
	fb_puts("                           < WELCOME TO MURLOCOS! >\n", -1, -1, FB_COLOR_COMBINE(FB_L_GREEN, FB_BLACK));
	printf("                   This is a small hobby project by myself,\n             trying to understand how an OS works under the hood!\n");
	printf("\n> ");

	gdt_initizalize();
	return 0;
}
