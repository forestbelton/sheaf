#!/bin/bash

PATH="./tools/toolchain/bin:$PATH"

rm -rf build
mkdir build

i686-elf-as src/boot.s -o build/boot.o
i686-elf-gcc -Iinclude -c src/terminal.c -o build/terminal.o -std=gnu99 \
    -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc mini-printf/mini-printf.c -c -o build/mini-printf.o -std=gnu99 \
    -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -Iinclude -Imini-printf -c src/crt.c -o build/crt.o -std=gnu99 \
    -ffreestanding -O2 -Wall -Wextra -Wno-unused-parameter
#i686-elf-gcc -Iinclude -c src/malloc.c -o build/malloc.o -std=gnu99 \
#    -ffreestanding -O2 -Wall -Wextra -DLACKS_SYS_TYPES_H -DNO_MALLOC_STATS \
#    -DLACKS_ERRNO_H -DLACKS_TIME_H -DLACKS_STDLIB_H -DLACKS_STRING_H \
#    -DLACKS_SYS_MMAN_H -DLACKS_FCNTL_H -DLACKS_UNISTD_H -DLACKS_SYS_PARAM_H \
#    -DHAVE_MMAP=0 -DMALLOC_FAILURE_ACTION=;
i686-elf-gcc -Iinclude -Imini-printf -c src/kernel.c -o build/kernel.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o build/sheaf.bin -ffreestanding -O2 -nostdlib \
    build/boot.o build/terminal.o build/mini-printf.o build/crt.o \
    build/kernel.o -lgcc
