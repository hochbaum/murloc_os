#ifndef MURLOC_OS_PIC_H
#define MURLOC_OS_PIC_H

#include "../stdint.h"

#define PIC1                0x20
#define PIC2                0xA0
#define PIC1_COMMAND        PIC1
#define PIC1_DATA           (PIC1+1)
#define PIC2_COMMAND        PIC2
#define PIC2_DATA           (PIC2+1)

#define ICW1_ICW4           0x01
#define ICW1_SINGLE         0x02
#define ICW1_INTERVAL4      0x04
#define ICW1_LEVEL          0x08
#define ICW1_INIT           0x10

#define ICW4_8086           0x01
#define ICW4_AUTO           0x02
#define ICW4_BUF_SLAVE      0x08
#define ICW4_BUF_MASTER     0x0C
#define ICW4_FULLY_NESTED   0x10

#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT PIC2_START_INTERRUPT + 7
#define PIC_ACK 0x20

/*!
 * This function sends an ack to the interrupt's
 * PIC port as the interrupt will be blocked until
 * we do so.
 *
 * @param interrupt The interrupt ID.
 */
void pic_acknowledge(uint32_t interrupt);

#endif //MURLOC_OS_PIC_H
