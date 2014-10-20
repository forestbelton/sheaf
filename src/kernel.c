#include "terminal.h"
#include "crt.h"

void kernel_main() {
    terminal_initialize();
    printf("Hello, %s!\n", "Forest");
}
