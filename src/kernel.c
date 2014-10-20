#include "terminal.h"

void kernel_main() {
    terminal_initialize();
    terminal_writestring("Hello, world!\n");
}
