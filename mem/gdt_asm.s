[bits 32]

global gdt_flush

gdt_flush:
	mov eax, DWORD [esp + 4]
	lgdt [eax]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:cs_flush

cs_flush:
	ret
