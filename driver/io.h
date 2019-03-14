#ifndef MURLOC_OS_PORTS_H
#define MURLOC_OS_PORTS_H

/*!
 * Sends a byte to an I/O port.
 *
 * @param port The port address to send the byte to.
 * @param data The byte to send to the port.
 */
void outb(unsigned short port, unsigned char data);

/*!
 * Reads a byte from an I/O port.
 *
 * @param port The port address to read from.
 *
 * @return The byte which was read.
 */
unsigned char inb(unsigned short port);

#endif //MURLOC_OS_PORTS_H
