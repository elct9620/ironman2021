#include "iron.h"

IRON_API
int mrb_get_argc(mrb_state* mrb) {
  return mrb->ci->argc;
}

IRON_API
mrb_value* mrb_get_argv(mrb_state* mrb) {
  return mrb->ci->argv;
}
