#include "crt.h"
#include "terminal.h"
#include "mini-printf.h"

/* stubs */
FILE *fopen(const char *name, const char *mode) {
  return NULL;
}

void fclose(FILE *f) {
}

int access(const char *p, int mode) {
  return 0;
}

int fwrite(const void *ptr, size_t sz, size_t count, FILE *f) {
  return 0;
}

int fgetc(FILE *f) {
  return EOF;
}

int fputc(int c, FILE *f) {
  return 0;
}

int ungetc(int c, FILE *f) {
  return 0;
}

char *getenv(const char *key) {
  return "";
}

/* non-stubs */
int printf(char *fmt, ...) {
  static char buf[100];
  
  va_list args;
  va_start(args, fmt);
  
  vsnprintf(buf, sizeof buf - 1, fmt, args);
  va_end(args);

  terminal_writestring(buf);
  
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

int labs(int i) {
  return i > 0 ? i : -i;
}

#define ISCLASS(cs) do {         \
  size_t i;                      \
                                 \
  for(i = 0; i < sizeof cs; ++i) \
    if(cs[i] == c)               \
      return 1;                  \
  return 0;                      \
} while(0)

int isdigit(int c) {
  ISCLASS("0123456789");
}

int isxdigit(int c) {
  ISCLASS("0123456789abcdefABCDEF");
}

int isspace(int c) {
  ISCLASS(" \r\n\v\t\f");
}

int isalpha(int c) {
  ISCLASS("abcdefghijklmnopqrstuvwxyzABCDEFGHJIJKLMNOPQRSTUVWXYZ");
}

int isupper(int c) {
  ISCLASS("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

int tolower(int c) {
  if(c >= 'A' && c <= 'Z')
    return (c - 'A') + 'a';
  else
    return c;
}

int toupper(int c) {
  if(c >= 'a' && c <= 'z')
    return (c - 'a') + 'A';
  else
    return c;
}

float atof(const char *in) {
  return 0;
}

long atol(const char *in) {
  long sgn = 1, val = 0;
  
  if(*in == '-') {
    sgn = -1;
    in++;
  }

  while(*in) {
    val *= 10;
    val += *in++ - '0';
  }
  
  return val * sgn;
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
  terminal_writestring("ABORTING...\n");
  for(;;);
}
