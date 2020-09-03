#ifdef UNIT_TEST
    #include "ArduinoFake.h"
#else
    #include "Arduino.h"
#endif

#include "app.h"
#include "iron.h"
#include "vm.h"

mrb_state* mrb;

void mrb_puts(mrb_state* mrb, mrb_value self) {
  int argc = mrb_get_argc(mrb);
  mrb_value* argv = mrb_get_argv(mrb);

  for(int i = 0; i < argc; i++) {
    Serial.print(argv[i].value.i);
    Serial.println();
  }
}

void setup() {
  Serial.begin(9600);

  mrb = mrb_open();
  // Define Print
  mrb_define_method(mrb, "puts", mrb_puts);

  // mrb_close(mrb);
}

void loop() {
  mrb_run(mrb, app);
}