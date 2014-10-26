export PATH := ./tools/toolchain/bin:$(PATH)

CC := i686-elf-gcc
AS := i686-elf-as

CFLAGS := -Iinclude -Itinyscheme-1.40 -std=gnu99 -O2 -nostdlib \
	-Itools/toolchain -ffreestanding -Wno-implicit-function-declaration \
	-DUSE_NO_FEATURES=1

CFILES := $(wildcard src/*.c) tinyscheme-1.40/scheme.c
SFILES := $(wildcard src/*.s)

COBJS := $(patsubst %.c, %.o, $(CFILES))
SOBJS := $(patsubst %.s, %.o, $(SFILES))

OBJS := $(COBJS) $(SOBJS)

build/sheaf.bin: $(OBJS)
	$(CC) $(CFLAGS) -T linker.ld -o $@ $(OBJS) -lgcc -lc

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.s
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean run

clean:
	rm -rf build/* src/*.o tinyscheme-1.40/*.o

run: build/sheaf.bin
	qemu-system-i386 -kernel build/sheaf.bin
