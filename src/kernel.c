#include "terminal.h"
#include "scheme.h"

void gdt_install(void);
void idt_install(void);

void kernel_main() {
  scheme *sc;

  gdt_install();
  idt_install();
  terminal_initialize();
  
  printf("Initializing Scheme...\n");
  sc = scheme_init_new();
  
  scheme_set_input_port_file(sc, stdin);
  scheme_set_output_port_file(sc, stdout);

  scheme_load_string(sc, "(let ((x (+ 1 1))) (display x))");
}
