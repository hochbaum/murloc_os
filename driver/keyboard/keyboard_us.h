#ifndef MURLOC_OS_KEYBOARD_US_H
#define MURLOC_OS_KEYBOARD_US_H

#include "../keyboard.h"

char keyboard_us[] =
{
	/* err code and escape? */
	0, 27,

	/* cipher keys */
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',

	'-', '=',

	/* TODO: implement \b */
	'\b', '\t',

	/* lowercase letters 1 */
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',

	'[', ']',

	/* return */
	'\n',

	KEYBOARD_KEY_CTRL,

	/* lowercase letters 2 */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',

	';', '\'', '`', KEYBOARD_KEY_SHIFT, '\\',

	/* lowercase letters 3 */
	'z', 'x', 'c', 'v', 'b', 'n', 'm',

	',', '.', '/', KEYBOARD_KEY_SHIFT,

	'*', KEYBOARD_KEY_ALT, ' ',

	/* caps lock */
	0,

	/* fn keys */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	/* numpad and other useless things */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	/* err code and escape? */
	0, 27,

	/* ciphers but uppercase */
	'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',

	'\b', '\t',

	/* uppercase letters 1 */
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',

	'{', '}',

	/* return */
	'\n',

	KEYBOARD_KEY_CTRL,

	/* uppercase letters 2 */
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',

	':', '"', '~', KEYBOARD_KEY_SHIFT, '|',

	/* uppercase letters 3 */
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',

	'<', '>', '?', KEYBOARD_KEY_SHIFT, '*', KEYBOARD_KEY_ALT, ' ',

	/* caps lock */
	0,

	/* fn keys */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	/* numpad and other useless things */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#endif //MURLOC_OS_KEYBOARD_US_H
