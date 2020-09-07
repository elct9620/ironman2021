#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "app.h"
#include "iron.h"
#include "vm.h"

TFT_eSPI tft = TFT_eSPI();
mrb_state* mrb;

void mrb_puts(mrb_state* mrb, mrb_value self) {
  int argc = mrb_get_argc(mrb);
  mrb_value* argv = mrb_get_argv(mrb);

  char num[4];

  tft.fillScreen(TFT_BLACK);
  for(int i = 0; i < argc; i++) {
    sprintf(num, "%d", argv[i].value.i);
    tft.drawString(num, 8, i * 16 + 8, 2);
    Serial.println(argv[i].value.i);
  }
}

void setup() {
  Serial.begin(9600);

  tft.init();
  tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  mrb = mrb_open();
  // Define Print
  mrb_define_method(mrb, "puts", mrb_puts);

  // mrb_close(mrb);
}

void loop() {
  mrb_run(mrb, app);
  delay(5000);
}
