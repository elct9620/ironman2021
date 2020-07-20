#include <stdlib.h>

#include "utils.h"
#include "irep.h"

static size_t skip_padding(const uint8_t* buf) {
  const size_t align = sizeof(uint32_t);
  return -(intptr_t)buf & (align - 1);
}

mrb_irep* read_irep(const uint8_t* src, uint8_t* len) {
  const uint8_t* bin = src;

  mrb_irep* irep = (mrb_irep*)malloc(sizeof(mrb_irep));

  // Skip record (+4)
  bin += sizeof(uint32_t);

  irep->nlocals = bin_to_uint16(bin);
  bin += sizeof(uint16_t); // +2

  irep->nregs = bin_to_uint16(bin);
  bin += sizeof(uint16_t); // + 2

  // Child ireps
  irep->rlen = bin_to_uint16(bin);
  bin += sizeof(uint16_t); // +2

  // ISEQ Blocks
  // TODO: Save ISEQ
  bin += sizeof(uint32_t); // +4
  bin += skip_padding(bin);

  *len = (uint8_t)(bin - src);

  return irep;
}
