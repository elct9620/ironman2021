#include "vm.h"
#include "irep.h"
#include "utils.h"

int mrb_exec(const uint8_t* data) {
  const uint8_t* src = data;
  uint8_t len;

  mrb_irep* irep = read_irep(src, &len);
  src += len;

  LOG("DEBUG> locals: %d, regs: %d, ireps: %d\n", irep->nlocals, irep->nregs, irep->rlen);

  // TODO
  return 0;
}
