nasm -f elf32 -o start.o start.asm
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I$HOME/Desktop/repo/src/include -c -o main.o main.c
gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I$HOME/Desktop/repo/src/include -c -o scrn.o scrn.c
ld -m elf_i386 -N -T link.ld -o kernel.bin -e _start
mv kernel.bin $HOME/Desktop/repo/src/isodir/boot/
grub-mkrescue -o kernel.iso isodir
rm start.o main.o scrn.o start.asm~ main.c~ scrn.c~ $HOME/Desktop/repo/src/isodir/boot/kernel.bin
