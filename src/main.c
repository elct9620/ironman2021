/**
 * iron-ruby-vm
 */

#include "app.h"
#include "vm.h"

int main(int argc, char** argv) {

  mrb_run(app);

  return 0;
}
