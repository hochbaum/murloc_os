#ifndef MURLOC_OS_KEYBOARD_H
#define MURLOC_OS_KEYBOARD_H

#define KEYBOARD_DATA_PORT      0x60

#define KEYBOARD_KEY_SHIFT      0x11
#define KEYBOARD_KEY_ALT        0x12
#define KEYBOARD_KEY_CTRL       0x13

void keyboard_initialize();

#endif //MURLOC_OS_KEYBOARD_H
