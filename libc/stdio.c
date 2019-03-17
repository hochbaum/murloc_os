#include "stdio.h"
#include "stdint.h"
#include "../driver/framebuf.h"
#include "string.h"

void printf(char *fmt, ...)
{
	va_list ap;
	char *sval;
	uint32_t uival;

	va_start(ap, fmt);

	for (char *p = fmt; *p != '\0'; ++p)
	{
		if (*p != '%')
		{
			fb_putc(*p, -1, -1, FB_DEFAULT_ATTRIB);
			continue;
		}

		switch (*++p)
		{
			case 's': {
				sval = va_arg(ap, char*); /* in case you are using CLion, it might complain here? */
				fb_puts(sval, -1, -1, FB_DEFAULT_ATTRIB);
				break;
			}

			case '%': {
				fb_putc('%', -1, -1, FB_DEFAULT_ATTRIB);
				break;
			}

			case 'd': {
				uival = va_arg(ap, uint32_t);
				char buf[16];
				itoa(buf, uival);
				fb_puts(buf, -1, -1, FB_DEFAULT_ATTRIB);
				break;
			}
		}
	}

	va_end(ap);
}
