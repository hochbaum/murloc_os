#ifndef MURLOC_OS_PORTS_H
#define MURLOC_OS_PORTS_H

#include "../libc/stdint.h"

#define SERIAL_COM1_BASE 0x3F8
#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#define SERIAL_LINE_ENABLE_DLAB 0x80

void serial_configure_baud_rate(uint16_t com, uint16_t divisor);

void serial_configure_line(uint16_t com);

uint32_t serial_is_transmit_fifo_empty(uint16_t com);

/*!
 * Sends a byte to an I/O port.
 *
 * @param port The port address to send the byte to.
 * @param data The byte to send to the port.
 */
void outb(uint16_t port, uint8_t data);

/*!
 * Reads a byte from an I/O port.
 *
 * @param port The port address to read from.
 *
 * @return The byte which was read.
 */
uint8_t inb(uint16_t port);

/*!
 * This function is called whenever we press return to
 * input commands.
 *
 * Might be moved to another location later.
 *
 * @param keybuffer The pressed letters.
 */
void user_in(char* keybuffer);

#endif //MURLOC_OS_PORTS_H
