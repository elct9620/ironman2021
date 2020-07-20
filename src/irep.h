#ifndef _IRON_IREP_H_
#define _IRON_IREP_H_

#include <stdint.h>

/**
 * mruby binary header
 *
 * uint8_t rite_binary_header[22]
 * uint8_t rite_section_irep_header[12]
 *
 */
#define irep_load(irep) ((irep) + 34)

typedef struct mrb_irep {
  uint16_t nlocals;
  uint16_t nregs;

  uint16_t rlen;
} mrb_irep;

mrb_irep* read_irep(const uint8_t* src, uint8_t* len);

#endif
