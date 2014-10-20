#!/bin/bash

set -e
PATH="./tools/toolchain/bin:$PATH"

rm -rf build
mkdir build

CFLAGS="-Iinclude -Imini-printf -Itinyscheme-1.40 -std=gnu99 -ffreestanding
    -O2 -Wall -Wextra -Wno-unused-parameter"
MODULES=("terminal" "crt" "kernel" "scanf" "strtol" "gdt" "idt" "irq"
    "keyboard" "isrs")
OBJS="build/boot.o build/irq.o build/terminal.o build/crt.o build/kernel.o
    build/scanf.o build/mini-printf.o build/malloc.o build/strtol.o
    build/scheme.o build/gdt.o build/idt.o build/keyboard.o build/irqs.o
    build/isrs.o build/isrr.o"

i686-elf-as src/boot.s -o build/boot.o
i686-elf-as src/isrr.s -o build/isrr.o
i686-elf-as src/irqs.s -o build/irqs.o

for MOD in "${MODULES[@]}"
do
    i686-elf-gcc $CFLAGS -c "src/$MOD.c" -o "build/$MOD.o"
done

i686-elf-gcc mini-printf/mini-printf.c -c -o build/mini-printf.o -std=gnu99 \
    -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc $CFLAGS -c src/malloc.c -o build/malloc.o \
    -DNO_MALLOC_STATS -DLACKS_ERRNO_H -DLACKS_TIME_H -DLACKS_STDLIB_H \
    -DLACKS_STRING_H -DLACKS_SYS_MMAN_H -DLACKS_FCNTL_H -DLACKS_UNISTD_H \
    -DLACKS_SYS_PARAM_H -DHAVE_MMAP=0 "-DMALLOC_FAILURE_ACTION=;" \
    -DLACKS_SYS_TYPES_H
i686-elf-gcc $CFLAGS -Itinyscheme-1.40 -c tinyscheme-1.40/scheme.c \
    -o build/scheme.o -DUSE_NO_FEATURES=1 -DUSE_STRCASECMP=0 -Wno-switch \
    -Wno-implicit-function-declaration -Wno-maybe-uninitialized \
    -Wno-unused-function -Wno-sign-compare

i686-elf-gcc -T linker.ld -o build/sheaf.bin -ffreestanding -O2 -nostdlib \
    $OBJS -lgcc
