#ifndef MURLOC_OS_PORTS_H
#define MURLOC_OS_PORTS_H

#include "../libc/stdint.h"

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

#endif //MURLOC_OS_PORTS_H
