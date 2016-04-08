bin/kernel.elf: bin/boot.o bin/kmain.o
	ld -Ttext=0x100000 -melf_i386 -o bin/kernel.elf bin/kernel.bin

bin/boot.o: src/boot.asm
	nasm -felf32 src/boot.asm -o bin/boot.o

bin/kmain.o: src/kmain.c
	gcc -o bin/kmain.o src/kmain.c -Wall -Werror -Wextra -nostdlib -O3

clean:
	rm bin/*
