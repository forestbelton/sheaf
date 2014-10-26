#include "terminal.h"

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int access(const char *path, int amode) {
    return 0;
}

int isatty(int fildes) {
    return 0;
}

int open(const char *path, int oflag, ...) {
    return 0;
}

int close(int fildes) {
    return 0;
}

int write(int fildes, const void *buf, size_t nbyte) {
    if(fildes == STDOUT_FILENO) {
        const char *strbuf = buf;
        size_t i = 0;

        for(i = 0; i < nbyte; ++i) {
            terminal_putchar(strbuf[i]);
        }

        return nbyte;
    }
    
    return 0;
}

int read(int fildes, void *buf, size_t nbyte) {
    return 0;
}

int fstat(int fildes, struct stat *buf) {
    return 0;
}

off_t lseek(int fildes, off_t offset, int whence) {
    return 0;
}

void *sbrk(ptrdiff_t bytes) {
    static char *memptr = NULL;
    char *old;

    if(!memptr) {
        extern char kernel_end;
        memptr = (char *)&kernel_end;
    }

    old = memptr;
    memptr += bytes;

    return old;
}
