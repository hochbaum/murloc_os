#include "keyboard.h"
#include "../cpu/idt.h"
#include "io.h"
#include "framebuf.h"
#include "../cpu/8259pic.h"
#include "../libc/string.h"

#include "keyboard/keyboard_us.h"
#define LAYOUT keyboard_us

static char keybuffer[256];
static uint32_t shift_pressed;

static void handler_keyboard(cpu_state_t cpu_state, idt_response_t idt_response, stack_state_t stack_state)
{
	/* unused */
	(void)cpu_state;
	(void)idt_response;
	(void)stack_state;

	uint8_t scancode = inb(KEYBOARD_DATA_PORT);
	pic_acknowledge(33);

	if (scancode > 57)
	{
		uint8_t released = scancode - 0x80;

		if (LAYOUT[released] == KEYBOARD_KEY_SHIFT)
		{
			shift_pressed = 0;
		}

		return;
	}

	switch (LAYOUT[scancode])
	{
		case '\b': {
			uint32_t len = strlen(keybuffer);

			if (len > 0)
			{
				keybuffer[len - 1] = '\0';
				fb_putbs();
			}
			break;
		}

		case KEYBOARD_KEY_SHIFT: {
			shift_pressed = 1;
			break;
		}

		case '\n': {
			fb_puts("\n", -1, -1, FB_DEFAULT_ATTRIB);
			memset(keybuffer, 0, 256);

			user_in(keybuffer);
			break;
		}

		default: {
			char letter;
			if (shift_pressed)
			{
				letter = LAYOUT[scancode + 128];
			}
			else {
				letter = LAYOUT[scancode];
			}

			uint32_t len = strlen(keybuffer);

			keybuffer[len] = letter;
			keybuffer[len + 1] = '\0';

			fb_putc(letter, -1, -1, FB_DEFAULT_ATTRIB);
			break;
		}
	}
}

#undef LAYOUT

void keyboard_initialize()
{
	interrupt_handler_register(33, &handler_keyboard);
}
