#include <stdlib.h>

#include "iron.h"

IRON_API mrb_state*
mrb_open(void) {
  mrb_state* mrb = (mrb_state*)malloc(sizeof(mrb_state));

  return mrb;
}

IRON_API void
mrb_close(mrb_state* mrb) {
  if(!mrb) return;

  free(mrb);
}
