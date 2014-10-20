#include "terminal.h"
#include "scheme.h"

void gdt_install(void);

void kernel_main() {
  scheme *sc;

  gdt_install();
  terminal_initialize();
  
  printf("Initializing Scheme...\n");
  sc = scheme_init_new();
  
  scheme_set_input_port_file(sc, stdin);
  scheme_set_output_port_file(sc, stdout);

  scheme_load_string(sc, "(display \"Hello from Scheme\")");
}
