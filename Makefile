export PATH := ./tools/toolchain/bin:$(PATH)

CC := i686-elf-gcc
AS := i686-elf-as

DEFINES := \
    -DUSE_NO_FEATURES=1 -DUSE_STRCASECMP=0 \
    -DNO_MALLOC_STATS -DLACKS_ERRNO_H -DLACKS_TIME_H -DLACKS_STDLIB_H \
    -DLACKS_STRING_H -DLACKS_SYS_MMAN_H -DLACKS_FCNTL_H -DLACKS_UNISTD_H \
    -DLACKS_SYS_PARAM_H -DHAVE_MMAP=0 "-DMALLOC_FAILURE_ACTION=;" \
    -DLACKS_SYS_TYPES_H

CFLAGS := -Iinclude -Imini-printf -Itinyscheme-1.40 -std=gnu99 -O2 $(DEFINES) \
	-nostdlib -Itools/toolchain -ffreestanding \
	-Wno-implicit-function-declaration

CFILES := $(wildcard src/*.c) tinyscheme-1.40/scheme.c mini-printf/mini-printf.c
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

.PHONY: clean

clean:
	rm -rf build/* src/*.o tinyscheme-1.40/*.o mini-printf/*.o
