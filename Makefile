ASM_SOURCES = $(wildcard *.s mem/*.s cpu/*.s)
C_SOURCES = $(wildcard *.c driver/*.c libc/*.c mem/*.c cpu/*.c)
C_HEADERS = $(wildcard *.h driver/*.h libc/*.h mem/*.h cpu/*.h)
OBJECTS = ${C_SOURCES:.c=.o} ${ASM_SOURCES:.s=.o}

CC = i386-elf-gcc
AS = nasm
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	mkisofs -R                              \
	        -b boot/grub/stage2_eltorito    \
	        -no-emul-boot                   \
	        -boot-load-size 4               \
	        -A os                           \
	        -input-charset utf8             \
	        -quiet                          \
	        -boot-info-table                \
	        -o murloc.iso                   \
	        iso

run: os.iso
	qemu-system-i386 -boot d -cdrom murloc.iso -m 4096

debug: os.iso
	qemu-system-i386 -boot d -cdrom murloc.iso -m 4096 -s &
	$(GDB) -ex "target remote :1234" -ex "symbol-file kernel.elf"

%.o: %.c $(C_HEADERS)
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	find . -name '*.o' -type f -delete
	find . -name '*.elf' -type f -delete
	find . -name '*.iso' -type f -delete
