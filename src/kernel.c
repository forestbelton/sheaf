#include "descriptor_tables.h"
#include "terminal.h"
#include "scheme.h"

extern void keyboard_install();

scheme *sc;

void interp_line(const char *in) {
  scheme_load_string(sc, in);
  printf("\n> ");
}

void kernel_main() {
  init_descriptor_tables();
  terminal_initialize();
  keyboard_install();

  printf("sheaf v0.1\n> ");
  __asm__ __volatile__ ("sti");
  
  sc = scheme_init_new();
  for(;;);
  
  //  scheme_set_input_port_file(sc, stdin);
  //  scheme_set_output_port_file(sc, stdout);

  //  scheme_load_string(sc, "(let ((x (+ 1 1))) (display x))");
}
