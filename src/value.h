#ifndef _IRON_VALUE_H_
#define _IRON_VALUE_H_

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

#endif
