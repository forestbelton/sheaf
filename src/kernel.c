#include "descriptor_tables.h"
#include "terminal.h"
#include "scheme.h"

extern void keyboard_install();

scheme *sc;

void interp_line(const char *in) {
  static char buf[400];
  snprintf(buf, sizeof buf - 1, "(display %s)", in);
  scheme_load_string(sc, buf);
  printf("\n> ");
}

void kernel_main() {
  init_descriptor_tables();
  terminal_initialize();
  keyboard_install();

  printf("sheaf v0.1\n> ");
  __asm__ __volatile__ ("sti");
  
  sc = scheme_init_new();
  scheme_set_input_port_file(sc, stdin);
  scheme_set_output_port_file(sc, stdout);

  for(;;);
}
