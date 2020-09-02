#include "iron.h"

IRON_API
int mrb_get_argc(mrb_state* mrb) {
  return mrb->ci->argc;
}
