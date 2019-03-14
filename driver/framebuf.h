#ifndef MURLOC_OS_FRAMEBUF_H
#define MURLOC_OS_FRAMEBUF_H

#define FB_FRAMEBUF_ADDR 0x00B8000

#define FB_BLACK        0x0
#define FB_BLUE         0x1
#define FB_GREEN        0x2
#define FB_CYAN         0x3
#define FB_RED          0x4
#define FB_MAGENTA      0x5
#define FB_BROWN        0x6
#define FB_L_GRAY       0x7
#define FB_D_GRAY       0x8
#define FB_L_BLUE       0x9
#define FB_L_GREEN      0xA
#define FB_L_CYAN       0xB
#define FB_L_RED        0xC
#define FB_L_MAGENTA    0xD
#define FB_L_BROWN      0xE
#define FB_WHITE        0xF

#define FB_PORT_COMMAND     0x3D4
#define FB_PORT_DATA        0x3D5

#define FB_COMMAND_HIGH_BYTE    14
#define FB_COMMAND_LOW_BYTE     15

#define FB_COLOR_COMBINE(fg, bg)    (((bg & 0x0F) << 4) | (fg & 0x0F))

#define FB_MAX_COLUMNS 100
#define FB_MAX_ROWS     16
#define FB_SCREEN_SIZE (FB_MAX_COLUMNS * FB_MAX_ROWS)

#define FB_CURSOR_CALC_SHIFT(offset)            ((offset / 2) >> 8)
#define FB_CURSOR_CALC_OFFSET(col, row)         (2 * (row * FB_MAX_COLUMNS + col))
#define FB_CURSOR_CALC_ROW_OFFSET(offset)       ((offset / 2) * FB_MAX_COLUMNS)
#define FB_CURSOR_CALC_COLUMN_OFFSET(offset)    ((offset - (FB_CURSOR_CALC_ROW_OFFSET(offset) * 2 * FB_MAX_COLUMNS)) / 2)

#define FB_DEFAULT_FG       FB_L_GRAY
#define FB_DEFAULT_BG       FB_BLACK
#define FB_DEFAULT_ATTRIB   (FB_COLOR_COMBINE(FB_DEFAULT_FG, FB_DEFAULT_BG))

/*!
 * Prints the specified character at the given location using the
 * attribute.
 *
 * You can use -1 for both column and row to let it calculate
 * automatically.
 *
 * See FB_COLOR_COMBINE for creating your attribute.
 *
 * @param c The character to print.
 * @param column The X coordinate of the character.
 * @param row The Y coordinate of the character.
 * @param attrib Foreground and background color.
 *
 * @return The new offset.
 */
int fb_putc(const char c, int column, int row, char attrib);

/*!
 * Prints the specified string at the given location using the
 * attribute.
 *
 * You can use -1 for both column and row to let it calculate
 * automatically.
 *
 * See FB_COLOR_COMBINE for creating your attribute.
 *
 * @param str The string to print.
 * @param column The X coordinate of the first character of the string.
 * @param row The Y coordinate of the first character of the string.
 * @param attrib Foreground and background color.
 */
void fb_puts(const char *str, int column, int row, char attrib);

/*!
 * Clears the screen.
 */
void fb_clear();

/*!
 * Moves the cursor to the specified position.
 *
 * See FB_CURSOR_CALC_OFFSET for calculating the position.
 *
 * @param pos The new position for the cursor.
 */
void fb_cursor_move(const unsigned short pos);

/**
 * Returns the cursor's current offset.
 *
 * @return The cursor offset.
 */
int fb_cursor_offset();

#endif //MURLOC_OS_FRAMEBUF_H
