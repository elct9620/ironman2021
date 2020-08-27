/**
 * iron-ruby-vm
 */

#include "app.h"
#include "iron.h"
#include "vm.h"

int main(int argc, char** argv) {

  mrb_state* mrb = mrb_open();
  mrb_run(mrb, app);
  mrb_close(mrb);

  return 0;
}
