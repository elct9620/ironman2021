#include <stdio.h>
#include <unity.h>

#include "app.h"
#include "iron.h"
#include "vm.h"

void mrb_puts(mrb_state* mrb, mrb_value self) {
  int argc = mrb_get_argc(mrb);
  mrb_value* argv = mrb_get_argv(mrb);

  for(int i = 0; i < argc; i++) {
    if (argv[i].tt == MRB_TT_STRING) {
      printf("%s\n", (const char*)argv[i].value.p);
    } else {
      printf("%d\n", (int)argv[i].value.i);
    }
  }
}

void test_mrb_run(void) {
  mrb_state* mrb = mrb_open();
  mrb_define_method(mrb, "puts", mrb_puts);
  mrb_run(mrb, app);
  mrb_close(mrb);
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_mrb_run);
  UNITY_END();
  return 0;
}
