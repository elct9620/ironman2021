#ifndef _IRON_H_
#define _IRON_H_

#define IRON_API extern

typedef struct mrb_state {
  int exc; /* exception */
  intptr_t* regs;
} mrb_state;

mrb_state* mrb_open(void);
IRON_API void mrb_close(mrb_state* mrb);


#endif
