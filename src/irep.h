#ifndef _IRON_IREP_H_
#define _IRON_IREP_H_

#include <stdint.h>
#include <stdlib.h>

#include "opcode.h"

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

#define IREP_PADDING() p += skip_padding(p)
#define IREP_READ_SIZE() READ_L()
#define IREP_READ_B(name) uint8_t name = READ_B()
#define IREP_READ_S(name) uint16_t name = READ_S()
#define IREP_READ_L(name) uint32_t name = READ_L()

#define IREP_SKIP_HEADER() READ_L(); READ_S(); READ_S(); READ_S()
#define IREP_SKIP_ISEQ() READ_L(); IREP_PADDING()

typedef struct mrb_irep {
  uint16_t nlocals;
  uint16_t nregs;
  uint16_t nirep;
} mrb_irep;

static size_t skip_padding(const uint8_t* buf) {
  const size_t align = sizeof(uint32_t);
  return -(intptr_t)buf & (align - 1);
}

mrb_irep* read_irep(const uint8_t* src, uint8_t* len);
const uint8_t* irep_get(const uint8_t* p, int type, int n);

#endif
