#include <stdlib.h>

#include "utils.h"
#include "irep.h"

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

const uint8_t* irep_get(const uint8_t* p, int type, int n) {
  // irep_header
  p += sizeof(uint32_t); // Record Size
  p += sizeof(uint16_t); // nlocals
  p += sizeof(uint16_t); // nregs

  int nirep = bin_to_uint16(p);
  p += sizeof(uint16_t);

  // Skip ISEQ
  int codelen = bin_to_uint32(p);
  p += sizeof(uint32_t);
  p += skip_padding(p);
  p += codelen;

  // Find in POOL
  {
    int pool_len = bin_to_uint32(p);
    p += sizeof(uint32_t);

    if (type == IREP_TYPE_LITERAL) {
      pool_len = n;

      for(int i = 0; i < pool_len; i++) {
        uint8_t type = *p;
        p += sizeof(uint8_t);
        uint16_t len = bin_to_uint16(p);
        p += sizeof(uint16_t);
        p += len + 1; // End with null byte
      }

      return p + 3; // Skip type and length
    }
  }

  // Find in SYM
  {
    int sym_len = bin_to_uint32(p);
    p += sizeof(uint32_t);
    if (type == IREP_TYPE_SYMBOL) {
      sym_len = n;
      for (int i = 0; i < sym_len; i++) {
        uint16_t len = bin_to_uint16(p);
        p += sizeof(uint16_t);
        p += len + 1; // End with null byte
      }

      return p + 2; // Skip length
    }
  }

  // Find in IREP
  {
    if (type == IREP_TYPE_IREP) {
      nirep = n;
      for (int i = 0; i < nirep; i++) {
        p = irep_get(p, IREP_TYPE_SKIP, 0);
      }
      return p;
    }
  }

  return p;
}
