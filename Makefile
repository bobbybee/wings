CFLAGS=-Wall -Werror -Wextra -nostdlib -ffreestanding -O2 -c -std=gnu99 -march=i386 -m32 -Ikernel/
COBJECTS=kernel/boot.o kernel/ktextvga.o kernel/kmemory.o kernel/kgdt.o kernel/kidt.o kernel/kisr.o kernel/kps2keyboard.o

kernel/kernel.elf: kernel/boot.o $(COBJECTS)
	ld -T kernel/linker.ld -melf_i386 -o kernel/kernel.elf $(COBJECTS)

kernel/boot.o: kernel/boot.asm
	nasm -felf32 kernel/boot.asm -o kernel/boot.o

kernel/%.o: kernel/%.c
	gcc -o kernel/$*.o kernel/$*.c $(CFLAGS)

clean:
	rm kernel/*.o kernel/*.elf
