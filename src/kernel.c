#include "terminal.h"
#include "crt.h"

void kernel_main() {
    terminal_initialize();

    char *x = malloc(20);
    strcpy(x, "Forest");
    
    printf("Hello, %s!\n", x);
}
