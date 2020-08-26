#ifndef _IRON_IREP_H_
#define _IRON_IREP_H_

#include <stdint.h>
#include <stdlib.h>

/**
 * mruby binary header
 *
 * uint8_t rite_binary_header[22]
 * uint8_t rite_section_irep_header[12]
 *
 */
#define irep_load(irep) ((irep) + 34)

#define IREP_TYPE_SKIP    0
#define IREP_TYPE_LITERAL 1
#define IREP_TYPE_SYMBOL  2
#define IREP_TYPE_IREP    3

typedef struct mrb_irep {
  uint16_t nlocals;
  uint16_t nregs;

  uint16_t rlen;
} mrb_irep;

static size_t skip_padding(const uint8_t* buf) {
  const size_t align = sizeof(uint32_t);
  return -(intptr_t)buf & (align - 1);
}

mrb_irep* read_irep(const uint8_t* src, uint8_t* len);
const uint8_t* irep_get(const uint8_t* p, int type, int n);

#endif
