CFLAGS=-Wall -Werror -Wextra -nostdlib -ffreestanding -O2 -c -std=gnu99 -Ikernel/
COBJECTS=kernel/boot.o kernel/ktextvga.o kernel/kmemory.o kernel/kgdt.o kernel/kidt.o kernel/kisr.o kernel/kps2keyboard.o

kernel/kernel.elf: kernel/boot.o $(COBJECTS)
	i386-elf-gcc -T kernel/linker.ld -o kernel/kernel.elf -ffreestanding -O2 -nostdlib -lgcc $(COBJECTS)

kernel/boot.o: kernel/boot.asm
	nasm -felf32 kernel/boot.asm -o kernel/boot.o

kernel/%.o: kernel/%.c
	i386-elf-gcc -o kernel/$*.o kernel/$*.c $(CFLAGS)

clean:
	rm kernel/*.o kernel/*.elf
