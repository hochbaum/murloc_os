extern interrupt_handler

global interrupts_enable
global interrupts_disable

%macro no_errno_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push byte 0
	push byte %1
	jmp interrupt_handler_common
%endmacro

%macro errno_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push byte %1
	jmp interrupt_handler_common
%endmacro

section .text

interrupt_handler_common:
	push esp

	add DWORD [esp], 8

	push eax
	push ebx
	push ecx
	push edx
	push ebp
	push esi
	push edi

	call interrupt_handler

	pop edi
	pop esi
	pop ebp
	pop edx
	pop ecx
	pop ebx
	pop eax
	pop esp

	iret

interrupts_enable:
	sti
	ret

interrupts_disable:
	cli
	ret

no_errno_handler 0
no_errno_handler 1
no_errno_handler 2
no_errno_handler 3
no_errno_handler 4
no_errno_handler 5
no_errno_handler 6
no_errno_handler 7
errno_handler 8
no_errno_handler 9
errno_handler 10
errno_handler 11
errno_handler 12
errno_handler 13
errno_handler 14
no_errno_handler 15
no_errno_handler 16
errno_handler 17
no_errno_handler 18
no_errno_handler 19
no_errno_handler 20
no_errno_handler 21
no_errno_handler 22
no_errno_handler 23
no_errno_handler 24
no_errno_handler 25
no_errno_handler 26
no_errno_handler 27
no_errno_handler 28
no_errno_handler 29
no_errno_handler 30
no_errno_handler 31
no_errno_handler 32
no_errno_handler 33
no_errno_handler 34
no_errno_handler 35
no_errno_handler 36
no_errno_handler 37
no_errno_handler 38
no_errno_handler 39
no_errno_handler 40
no_errno_handler 41
no_errno_handler 42
no_errno_handler 43
no_errno_handler 44
no_errno_handler 45
no_errno_handler 46
no_errno_handler 47
