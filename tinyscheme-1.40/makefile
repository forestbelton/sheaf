# Makefile for TinyScheme
# Time-stamp: <2002-06-24 14:13:27 gildea>

# Windows/2000
#CC = cl -nologo
#DEBUG= -W3 -Z7 -MD
#DL_FLAGS=
#SYS_LIBS=
#Osuf=obj
#SOsuf=dll
#LIBsuf=.lib
#EXE_EXT=.exe
#LD = link -nologo
#LDFLAGS = -debug -map -dll -incremental:no
#LIBPREFIX =
#OUT = -out:$@
#RM= -del
#AR= echo

# Unix, generally
CC = ../tools/toolchain/bin/i686-elf-gcc -fpic -ffreestanding -nostdlib -I../mini-printf
DEBUG=-Wall -Wno-char-subscripts -O
Osuf=o
SOsuf=so
LIBsuf=a
EXE_EXT=
LIBPREFIX=lib
OUT = -o $@
RM= -rm -f
AR= ar crs

# Linux
LD = ../tools/toolchain/bin/i686-elf-ld
LDFLAGS = -shared
DEBUG=-g -Wno-char-subscripts -O

# Cygwin
#PLATFORM_FEATURES = -DUSE_STRLWR=0


# Solaris
#SYS_LIBS= -ldl -lc
#Osuf=o
#SOsuf=so
#EXE_EXT=
#LD = ld
#LDFLAGS = -G -Bsymbolic -z text
#LIBPREFIX = lib
#OUT = -o $@

FEATURES = $(PLATFORM_FEATURES) -DUSE_NO_FEATURES=1 -DUSE_STRCASECMP=0

OBJS = scheme.$(Osuf) crt.$(Osuf) mini-printf.$(Osuf)

LIBTARGET = $(LIBPREFIX)tinyscheme.$(SOsuf)
STATICLIBTARGET = $(LIBPREFIX)tinyscheme.$(LIBsuf)

all: $(LIBTARGET) $(STATICLIBTARGET) scheme$(EXE_EXT)

%.$(Osuf): %.c
	$(CC) -I. -c $(DEBUG) $(FEATURES) $(DL_FLAGS) $<

$(LIBTARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OUT) $(OBJS) $(SYS_LIBS)

scheme$(EXE_EXT): $(OBJS)
	$(CC) -o $@ $(DEBUG) $(OBJS) $(SYS_LIBS)

$(STATICLIBTARGET): $(OBJS)
	$(AR) $@ $(OBJS)

$(OBJS): scheme.h scheme-private.h opdefines.h crt.h ../mini-printf/mini-printf.h

clean:
	$(RM) $(OBJS) $(LIBTARGET) $(STATICLIBTARGET) scheme$(EXE_EXT)
	$(RM) tinyscheme.ilk tinyscheme.map tinyscheme.pdb tinyscheme.exp
	$(RM) scheme.ilk scheme.map scheme.pdb scheme.lib scheme.exp
	$(RM) *~

TAGS_SRCS = scheme.h scheme.c crt.h crt.c

tags: TAGS
TAGS: $(TAGS_SRCS)
	etags $(TAGS_SRCS)
