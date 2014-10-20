#ifndef CRT_H_
#define CRT_H_

#include <limits.h>
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

int isalpha(int);
int isupper(int);
int isspace(int);
int isdigit(int);
int tolower(int);
int isxdigit(int);

long strtol(const char *str, char **endptr, int base);

#endif
