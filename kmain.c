#include "driver/framebuf.h"

int kmain()
{
	fb_clear();
	fb_puts("this is a test\nlol", -1, -1, FB_DEFAULT_ATTRIB);
	return 0;
}
