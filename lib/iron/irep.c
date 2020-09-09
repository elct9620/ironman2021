#include <stdlib.h>

#include "utils.h"
#include "irep.h"

mrb_irep* read_irep(const uint8_t* src, uint8_t* len) {
  const uint8_t* p = src;

  mrb_irep* irep = (mrb_irep*)malloc(sizeof(mrb_irep));

  IREP_READ_SIZE();
  IREP_READ_S(nlocals);
  IREP_READ_S(nregs);
  IREP_READ_S(nirep);

  irep->nlocals = nlocals;
  irep->nregs = nregs;
  irep->nirep = nirep;

  IREP_SKIP_ISEQ();

  *len = (uint8_t)(p - src);

  return irep;
}

const uint8_t* irep_get(const uint8_t* p, int type, int n) {
  IREP_READ_SIZE();
  IREP_READ_S(nlocals);
  IREP_READ_S(nregs);
  IREP_READ_S(nirep);

  // Skip ISEQ
  IREP_READ_L(codelen);
  IREP_PADDING();
  p += codelen;

  // Find in POOL
  {
    IREP_READ_L(npool);

    if (type == IREP_TYPE_LITERAL) {
      npool = n;
    }

    for(int i = 0; i < npool; i++) {
      IREP_READ_B(type);
      IREP_READ_S(len);
      p += len;
    }

    if (type == IREP_TYPE_LITERAL) {
      return p + 3; // Skip type and length
    }
  }

  // Find in SYM
  {
    IREP_READ_L(nsym);

    if (type == IREP_TYPE_SYMBOL) {
      nsym = n;
    }

    for (int i = 0; i < nsym; i++) {
      IREP_READ_S(len);
      p += len + 1; // End with null byte
    }

    if (type == IREP_TYPE_SYMBOL) {
      return p + 2; // Skip length
    }
  }

  // Find in IREP
  {
    if (type == IREP_TYPE_IREP) {
      nirep = n;
    }

    for (int i = 0; i < nirep; i++) {
      p = irep_get(p, IREP_TYPE_SKIP, 0);
    }

    if (type == IREP_TYPE_IREP) {
      return p;
    }
  }

  return p;
}
