#ifndef _IRON_H_
#define _IRON_H_

#include <klib/khash.h>

#include "value.h"

#define IRON_API extern

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
} mrb_state;

mrb_state* mrb_open(void);
IRON_API void mrb_close(mrb_state* mrb);

typedef void (*mrb_func_t)(mrb_state* mrb, mrb_value value);

KHASH_MAP_INIT_STR(mt, mrb_func_t)
IRON_API void mrb_define_method(mrb_state* mrb, const char* name, mrb_func_t func);

IRON_API int mrb_get_argc(mrb_state* mrb);

#endif
