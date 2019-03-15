#include "framebuf.h"
#include "io.h"
#include "../libc/string.h"

uint32_t fb_putc(const unsigned char c, int32_t column, int32_t row, uint8_t attrib)
{
	if (!attrib)
	{
		attrib = FB_DEFAULT_ATTRIB;
	}

	uint8_t *framebuf = (uint8_t *) FB_FRAMEBUF_ADDR;
	uint32_t offset = (column >= 0 && row >= 0) ? FB_CURSOR_CALC_OFFSET(column, row) : fb_cursor_offset();

	switch (c)
	{
		case '\n': {
			uint32_t rows = offset / (2 * FB_MAX_COLUMNS);
			offset = FB_CURSOR_CALC_OFFSET(0, rows + 1);
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

	if (offset >= FB_MAX_ROWS * FB_MAX_COLUMNS * 2)
	{
		for (int i = 1; i < FB_MAX_ROWS; i++)
		{
			memcpy((uint32_t *) FB_CURSOR_CALC_OFFSET(0, i) + FB_FRAMEBUF_ADDR, (uint32_t *) FB_CURSOR_CALC_OFFSET(0, i - 1) + FB_FRAMEBUF_ADDR, FB_MAX_COLUMNS * 2);
		}

		uint8_t *last_row = (uint8_t *) FB_CURSOR_CALC_OFFSET(0, FB_MAX_ROWS - 1) + FB_FRAMEBUF_ADDR;

		for (int i = 0; i < FB_MAX_COLUMNS * 2; i++)
		{
			last_row[i] = 0;
		}

		offset -= 2 * FB_MAX_COLUMNS;
	}

	fb_cursor_move(offset);
	return offset;
}

void fb_puts(const char *str, int32_t column, int32_t row, uint8_t attrib)
{
	uint32_t offset;
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
	uint8_t *framebuf = (uint8_t *) FB_FRAMEBUF_ADDR;
	uint8_t black = FB_COLOR_COMBINE(FB_DEFAULT_BG, FB_DEFAULT_BG);

	for (int i = 0; i < FB_SCREEN_SIZE; i++)
	{
		framebuf[i * 2] = ' ';
		framebuf[i * 2 + 1] = black;
	}

	fb_cursor_move(FB_CURSOR_CALC_OFFSET(0, 0));
}

void fb_cursor_move(const uint16_t pos)
{
	outb(FB_PORT_COMMAND, FB_COMMAND_HIGH_BYTE);
	outb(FB_PORT_DATA, FB_CURSOR_CALC_SHIFT(pos));
	outb(FB_PORT_COMMAND, FB_COMMAND_LOW_BYTE);
	outb(FB_PORT_DATA, (uint8_t) ((pos / 2) & 0xFF));
}

uint32_t fb_cursor_offset()
{
	outb(FB_PORT_COMMAND, FB_COMMAND_HIGH_BYTE);
	uint32_t offset = inb(FB_PORT_DATA) << 8;
	outb(FB_PORT_COMMAND, FB_COMMAND_LOW_BYTE);
	return (offset + inb(FB_PORT_DATA)) * 2;
}
