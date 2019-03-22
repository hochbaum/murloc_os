#ifndef MURLOC_OS_CPU_H
#define MURLOC_OS_CPU_H

#include "../stdint.h"

/*!
 * Holds the current state of the registers.
 */
typedef struct __cpu_state
{
	uint32_t    edi;
	uint32_t    esi;
	uint32_t    ebp;
	uint32_t    edx;
	uint32_t    ecx;
	uint32_t    ebx;
	uint32_t    eax;
	uint32_t    esp;
} __attribute__((packed)) cpu_state_t;

/*!
 * Holds the current state of the stack.
 */
typedef struct __stack_state
{
	uint32_t    eip;
	uint32_t    cs;
	uint32_t    eflags;
	uint32_t    user_esp;
	uint32_t    user_ss;
} __attribute__((packed)) stack_state_t;

#endif //MURLOC_OS_CPU_H
