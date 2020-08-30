/**
 * iron-ruby-vm
 */

#include <stdio.h>

#include "app.h"
#include "iron.h"
#include "vm.h"

void mrb_puts(mrb_state* mrb, mrb_value self) {
  if (self.tt == MRB_TT_FIXNUM) {
    printf("%d\n", self.value.i);
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
