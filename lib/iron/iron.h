#ifndef _IRON_H_
#define _IRON_H_

#include <khash.h>

#include "value.h"

#define IRON_API extern

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mrb_callinfo {
  int argc;
  mrb_value* argv;
} mrb_callinfo;

typedef struct mrb_state {
  int exc; /* exception */
  intptr_t* regs;

  // TODO: Move to RClass
  struct kh_mt_s *mt;
  // TODO: Move to mrb_context
  mrb_callinfo* ci;
  mrb_value* stack;
} mrb_state;


IRON_API mrb_state* mrb_open(void);
IRON_API void mrb_close(mrb_state* mrb);

typedef mrb_value (*mrb_func_t)(mrb_state* mrb, mrb_value value);

KHASH_MAP_INIT_STR(mt, mrb_func_t)
IRON_API void mrb_define_method(mrb_state* mrb, const char* name, mrb_func_t func);

IRON_API int mrb_get_argc(mrb_state* mrb);
IRON_API mrb_value* mrb_get_argv(mrb_state* mrb);

#ifdef __cplusplus
}
#endif

#endif
