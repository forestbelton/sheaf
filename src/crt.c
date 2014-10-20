#include "crt.h"
#include "terminal.h"
#include "mini-printf.h"

FILE *fopen(const char *name, const char *mode) {
  return NULL;
}

void fclose(FILE *f) {
}

int printf(char *fmt, ...) {
  static char buf[100];
  
  va_list args;
  va_start(args, fmt);
  
  vsnprintf(buf, sizeof buf - 1, fmt, args);
  va_end(args);

  terminal_writestring(buf);
  
  return 0;
}

int sscanf(const char *s, const char *fmt, ...) {
  return 0;
}

int fputs(const char *s, FILE *f) {
  return 0;
}

int access(const char *p, int mode) {
  return 0;
}

int fwrite(const void *ptr, size_t sz, size_t count, FILE *f) {
  return 0;
}

char *strlwr(char *s) {
  char *t = s;

  while(*t)
    tolower(*t++);

  return s;
}

int strcmp(const char *s1, const char *s2) {
  int diff = 0;

  while(*s1 && diff == 0)
    diff = *s1++ - *s2++;

  return diff;
}

int stricmp(const char *s1, const char *s2) {
  int diff = 0;

  while(*s1 && diff == 0)
    diff = tolower(*s1++) - tolower(*s2++);

  return diff;
}

char *strcpy(char *dst, const char *src) {
  char *t = dst;

  while(*src)
    *t++ = *src++;
  
  return dst;
}

void *memcpy(void *dst, void *src, size_t sz) {
  size_t i = 0;
  char *a = dst, *b = src;

  while(i < sz)
    a[i] = b[i];

  return dst;
}

int fgetc(FILE *f) {
  return EOF;
}

int fputc(int c, FILE *f) {
  return 0;
}

int labs(int i) {
  return i > 0 ? i : -i;
}

int isdigit(int c) {
  return 0;
}

int isspace(int c) {
  return 0;
}

int ungetc(int c, FILE *f) {
  return 0;
}

char *getenv(const char *key) {
  return "";
}

int tolower(int c) {
  return c;
}

int toupper(int c) {
  return c;
}

float atof(const char *in) {
  return 0;
}

int atol(const char *in) {
  return 0;
}

size_t strlen(const char *s) {
  size_t i = 0;

  while(*s++)
    i++;

  return i;
}

void *memset(void *p, int val, size_t cnt) {
  char *pp = p;

  while(cnt--)
    *pp++ = val;
  
  return p;
}

void *sbrk(int inc) {
  static char *memptr = (char *)BASE_HEAP;
  char *old = memptr;

  memptr += inc;
  return old;
}  

void abort() {
}
