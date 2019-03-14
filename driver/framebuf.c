#include "framebuf.h"
#include "io.h"

int fb_putc(const char c, int column, int row, char attrib)
{
	if (!attrib)
	{
		attrib = FB_DEFAULT_ATTRIB;
	}

	unsigned char *framebuf = (unsigned char *) FB_FRAMEBUF_ADDR;

	int offset = (column >= 0 && row >= 0) ? FB_CURSOR_CALC_OFFSET(column, row) : fb_cursor_offset();

	switch (c)
	{
		case '\n': {
			offset = FB_CURSOR_CALC_OFFSET(0, (offset / (2 * FB_MAX_COLUMNS)));
			break;
		}

		case 0x08: {
			framebuf[offset] = ' ';
			framebuf[offset + 1] = attrib;
			break;
		}

		default: {
			framebuf[offset] = c;
			framebuf[offset + 1] = attrib;
			offset += 2;
			break;
		}
	}

	fb_cursor_move(offset);
	return offset;
}

void fb_puts(const char *str, int column, int row, char attrib)
{
	int offset;
	if (column < 0 || row < 0)
	{
		offset = fb_cursor_offset();
		column = FB_CURSOR_CALC_COLUMN_OFFSET(offset);
		row = FB_CURSOR_CALC_ROW_OFFSET(offset);
	}

	for (int i = 0; str[i] != '\0'; i++)
	{
		offset = fb_putc(str[i], column, row, attrib);
		column = FB_CURSOR_CALC_COLUMN_OFFSET(offset);
		row = FB_CURSOR_CALC_ROW_OFFSET(offset);
	}
}

void fb_clear()
{
	unsigned char *framebuf = (unsigned char *) FB_FRAMEBUF_ADDR;
	char black = FB_COLOR_COMBINE(FB_DEFAULT_BG, FB_DEFAULT_BG);

	for (int i = 0; i < FB_SCREEN_SIZE; i++)
	{
		framebuf[i * 2] = ' ';
		framebuf[i * 2 + 1] = black;
	}

	fb_cursor_move(FB_CURSOR_CALC_OFFSET(0, 0));
}

void fb_cursor_move(const unsigned short pos)
{
	outb(FB_PORT_COMMAND, FB_COMMAND_HIGH_BYTE);
	outb(FB_PORT_DATA, FB_CURSOR_CALC_SHIFT(pos));
	outb(FB_PORT_COMMAND, FB_COMMAND_LOW_BYTE);
	outb(FB_PORT_DATA, (pos / 2) & 0xFF);
}

int fb_cursor_offset()
{
	outb(FB_PORT_COMMAND, FB_COMMAND_HIGH_BYTE);
	int offset = inb(FB_PORT_DATA) << 8;
	outb(FB_PORT_COMMAND, FB_COMMAND_LOW_BYTE);
	return (offset + inb(FB_PORT_DATA)) * 2;
}
