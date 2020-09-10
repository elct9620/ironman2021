#ifndef _IRON_VALUE_H_
#define _IRON_VALUE_H_

#include "utils.h"

enum mrb_vtype {
  MRB_TT_FALSE = 0,
  MRB_TT_TRUE,
  MRB_TT_FIXNUM,
  MRB_TT_STRING,
  MRB_TT_ARRAY
};

typedef struct mrb_value {
  union {
    void *p;
    int i;
  } value;
  enum mrb_vtype tt;
} mrb_value;

#define SET_VALUE(o, ttt, attr, v) do {\
  (o).tt = ttt;\
  (o).attr = v;\
} while(0)

#define SET_NIL_VALUE(r) SET_VALUE(r, MRB_TT_FALSE, value.i, 0)
#define SET_INT_VALUE(r, n) SET_VALUE(r, MRB_TT_FIXNUM, value.i, (n))
#define SET_FALSE_VALUE(r) SET_VALUE(r, MRB_TT_FALSE, value.i, 1)
#define SET_TRUE_VALUE(r) SET_VALUE(r, MRB_TT_TRUE, value.i, 1)

#define IS_NIL_VALUE(r) (r.tt == MRB_TT_FALSE && r.value.i == 0)

#define mrb_fixnum(o) (o).value.i
#define mrb_int(o) mrb_fixnum(o)

#define MRB_NIL 0x80000000 // nil for ruby
#define MRB_TRUE 1
#define MRB_FALSE MRB_NIL

IRON_INLINE mrb_value mrb_nil_value(void) {
  mrb_value v;
  SET_NIL_VALUE(v);
  return v;
}

IRON_INLINE mrb_value mrb_fixnum_value(int i) {
  mrb_value v;
  SET_INT_VALUE(v, i);
  return v;
}

#endif
