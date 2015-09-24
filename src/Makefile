CC=i686-elf-gcc
CFLAGS=-Wall -I$(HOME)/CB\ Projects/miniHOS-0.0.6/inc -c
AS=nasm
AFLAGS=-f elf32
OBJ=main.o scrn.o gdt.o idt.o isr.o irq.o timer.o kb.o pg.o start.o string.o io.o math.o algorithm.o hcmd.o syscll.o list.o ram.o
LD=i686-elf-ld
LFLAGS=-N -T link.ld -e _start
ISOPATH=$(HOME)/CB\ Projects/miniHOS-0.0.6/isodir/boot
DEPS=HOS.h limits.h hstd.h string.h sysio.h math.h algorithm.h hcmd.h list.h


%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<
%.o: %.asm
	$(AS) $(AFLAGS) -o $@ $<


make: $(OBJ)
	$(LD) $(LFLAGS) $(OBJ) -o kernel.bin
	mv kernel.bin $(ISOPATH)
	grub-mkrescue -o kernel.iso isodir

.PHONY: clean

clean:
	rm -f *~ *.o
	rm $(ISOPATH)/kernel.bin
