#ifndef CRT_H_
#define CRT_H_

#include "mini-printf.h"

// stdio.h
#define NULL 0
#define EOF -1
typedef struct FILE FILE;
typedef unsigned int size_t;

int printf(const char *, ...);
int fprintf(FILE *, const char *, ...);
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
void *malloc();
void free();
char *getenv();

#endif
