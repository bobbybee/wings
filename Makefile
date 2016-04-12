CFLAGS=-Wall -Werror -Wextra -nostdlib -ffreestanding -O3 -c -std=gnu99 -march=i386 -m32 -Isrc/
COBJECTS=bin/kmain.o bin/ktextvga.o bin/kmemory.o bin/kgdt.o bin/kidt.o bin/kisr.o

bin/kernel.elf: bin/boot.o $(OBJECTS)
#	ld -Ttext=0x100000 -melf_i386 -o bin/kernel.elf $(OBJECTS)
	ld -T src/linker.ld -melf_i386 $(COBJECTS)

bin/boot.o: src/boot.asm
	nasm -felf32 src/boot.asm -o bin/boot.o

bin/%.o: src/%.c
	gcc -o bin/$*.o src/$*.c $(CFLAGS)

clean:
	rm bin/*
