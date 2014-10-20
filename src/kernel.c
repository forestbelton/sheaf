#include "terminal.h"
#include "scheme.h"

void kernel_main() {
  scheme *sc;
  
  terminal_initialize();
  
  printf("Initializing Scheme...\n");
  sc = scheme_init_new();
  
  printf("Setting I/O ports...\n");
  scheme_set_input_port_file(sc, stdin);
  scheme_set_output_port_file(sc, stdout);

  printf("Evaluating 1+1...\n");
  scheme_load_string(sc, "(+ 1 1)");
}
