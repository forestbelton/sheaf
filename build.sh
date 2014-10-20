#!/bin/bash

PATH="./tools/toolchain/bin:$PATH"

rm -rf build
mkdir build

i686-elf-as src/boot.s -o build/boot.o
i686-elf-gcc -Iinclude -c src/terminal.c -o build/terminal.o -std=gnu99 \
    -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -Iinclude -c src/kernel.c -o build/kernel.o -std=gnu99 \
    -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o build/sheaf.bin -ffreestanding -O2 -nostdlib \
    build/boot.o build/terminal.o build/kernel.o -lgcc
