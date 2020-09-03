#include <stdlib.h>
#include <string.h>

#include "iron.h"

IRON_API
mrb_state* mrb_open(void) {
  mrb_state* mrb = (mrb_state*)malloc(sizeof(mrb_state));

  mrb->mt = kh_init(mt);

  return mrb;
}

IRON_API
void mrb_close(mrb_state* mrb) {
  if(!mrb) return;

  free(mrb->regs);
  free(mrb);
}

// TODO: Register method under object
IRON_API
void mrb_define_method(mrb_state* mrb, const char* name, mrb_func_t func) {
  int ret;
  khiter_t key = kh_put(mt, mrb->mt, name, &ret);
  kh_value(mrb->mt, key) = func;
}
