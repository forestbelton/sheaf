#include "kernel.h"
#include "terminal.h"
#include <stddef.h>
#include <stdint.h>

#define TEXT_COL 0xf

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static size_t x = 0, y = 0;
static volatile uint16_t *buf = (uint16_t *)0xb8000;
static char bufcpy[VGA_HEIGHT][VGA_WIDTH];

static inline void bufset(size_t x, size_t y, char c) {
    bufcpy[y][x] = c;
    buf[y * VGA_WIDTH + x] = (TEXT_COL << 8) | c;
}

static void terminal_flush() {
    for(size_t yi = 0; yi < VGA_HEIGHT; yi++) {
        for(size_t xi = 0; xi < VGA_WIDTH; xi++) {
            bufset(xi, yi, bufcpy[yi][xi]);
        }
    }
}

static void update_cursor() {
    uint16_t loc = y * VGA_WIDTH + x;

    outb(0x3d4, 14);
    outb(0x3d5, loc >> 8);
    outb(0x3d4, 15);
    outb(0x3d5, loc & 0xff);
}

void terminal_initialize()
{
    memset(&bufcpy[0][0], ' ', sizeof bufcpy);
    terminal_flush();
    update_cursor();
}

static void next_line() {
    size_t yi;

    if(++y == VGA_HEIGHT - 1) {
        size_t yi;

        for(yi = 1; yi < VGA_HEIGHT; yi++) {
            memcpy(&bufcpy[yi - 1][0], &bufcpy[yi][0], sizeof bufcpy[yi]);
        }

        --y;
        terminal_flush();
    }
}

void terminal_putchar(char c)
{
    switch(c) {
    case '\b':
        if(x != 0) {
            bufset(--x, y, ' ');
        }
        break;
        
    case '\n':
        x = 0;
        next_line();
        break;

    case '\r':
        x = 0;
        break;

    default:
        if(!isprint(c)) {
            return;
        }

        bufset(x, y, c);
        if(++x == VGA_WIDTH) {
            next_line();
        }
    }

    update_cursor();
}

