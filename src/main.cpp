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
    if (argv[i].tt == MRB_TT_STRING) {
      tft.drawString((const char*)argv[i].value.p, 8, i * 16 + 8, 1);
    } else {
      sprintf(num, "%d", argv[i].value.i);
      tft.drawString(num, 8, i * 16 + 8, 1);
    }
  }
}

void mrb_sleep(mrb_state* mrb, mrb_value self) {
  mrb_value* argv = mrb_get_argv(mrb);
  delay(argv[0].value.i);
}

void mrb_clear(mrb_state* mrb, mrb_value self) {
  tft.fillScreen(TFT_BLACK);
}

void mrb_draw_text(mrb_state* mrb, mrb_value self) {
  mrb_value* argv = mrb_get_argv(mrb);

  int x = mrb_fixnum(argv[1]);
  int y = mrb_fixnum(argv[2]);
  const char* text = (const char*)argv[0].value.p;

  tft.drawString(text, x, y, 1);
}

void setup() {
  Serial.begin(9600);

  tft.init();
  tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  mrb = mrb_open();
  // Define Print
  mrb_define_method(mrb, "puts", mrb_puts);
  mrb_define_method(mrb, "sleep", mrb_sleep);
  mrb_define_method(mrb, "clear", mrb_clear);
  mrb_define_method(mrb, "draw_text", mrb_draw_text);

  mrb_run(mrb, app);
  mrb_close(mrb);
}

void loop() {
  Serial.println("Looping...");
  delay(5000);
}
