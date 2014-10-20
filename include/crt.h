#ifndef CRT_H_
#define CRT_H_

#include <stddef.h>
#include <stdarg.h>
#include "mini-printf.h"

#define BASE_HEAP 0x100000

// stdio.h
#define EOF -1
typedef struct FILE FILE;

int printf(char *, ...);
int fwrite();
FILE *fopen();
int sscanf(const char *, const char *, ...);
int fputs(const char *, FILE *);

FILE *stdout, *stderr, *stdin;

// string.h
char *strcpy();
size_t strlen();
void *memcpy();
void *memset();

// stdlib.h
void *malloc(size_t);
void free(void *);
char *getenv();
void abort();

int tolower(int);

#endif
