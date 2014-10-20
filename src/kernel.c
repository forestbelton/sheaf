#include "terminal.h"
#include "scheme.h"

void gdt_install(void);
void idt_install(void);
void irq_install(void);
void isrs_install(void);
void keyboard_install(void);
void idt_load(void);

void kernel_main() {
  scheme *sc;

  terminal_initialize();
  
  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  keyboard_install();
  idt_load();
  __asm__ __volatile__ ("sti");


  int i = 0;
  i = 10 / 0;
  printf("Initializing Scheme...\n");
  //  sc = scheme_init_new();
  
  //  scheme_set_input_port_file(sc, stdin);
  //  scheme_set_output_port_file(sc, stdout);

  //  scheme_load_string(sc, "(let ((x (+ 1 1))) (display x))");

  for(;;);
}
