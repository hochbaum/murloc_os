C_SOURCES = $(wildcard *.c driver/*.c libc/*.c)
C_HEADERS = $(wildcard *.h driver/*.h libc/*.h)
OBJECTS = ${C_SOURCES:.c=.o loader.o}

CC = i386-elf-gcc
AS = nasm
LD = /usr/local/i386elfgcc/bin/i386-elf-ld

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
	qemu-system-i386 -boot d -cdrom murloc.iso -m 512

debug: os.iso
	qemu-system-i386 -boot d -cdrom murloc.iso -m 512 -s
	gdb -ex "target remote :1234"

%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	find . -name '*.o' -type f -delete
	find . -name '*.elf' -type f -delete
	find . -name '*.iso' -type f -delete
