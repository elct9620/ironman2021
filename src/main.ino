#include <stdio.h>

#include "app.h"
#include "iron.h"
#include "vm.h"

void mrb_puts(mrb_state* mrb, mrb_value self) {
  int argc = mrb_get_argc(mrb);
  mrb_value* argv = mrb_get_argv(mrb);

  for(int i = 0; i < argc; i++) {
    printf("%d\n", argv[i].value.i);
  }
}

int main(int argc, char** argv) {

  mrb_state* mrb = mrb_open();
  // Define Print
  mrb_define_method(mrb, "puts", mrb_puts);

  mrb_run(mrb, app);
  mrb_close(mrb);

  return 0;
}
