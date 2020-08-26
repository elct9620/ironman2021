#include "vm.h"
#include "irep.h"
#include "utils.h"
#include "opcode.h"

int mrb_exec(const uint8_t* data) {
  const uint8_t* src = data;
  uint8_t len;

  mrb_irep* irep = read_irep(src, &len);
  src += len;

  LOG("DEBUG> locals: %d, regs: %d, ireps: %d\n", irep->nlocals, irep->nregs, irep->nirep);

  int error = 0;

  // TODO: Move register to mrb_state
  intptr_t reg[irep->nregs - 1];

  // Temp
  int32_t a = 0;
  int32_t b = 0;
  int32_t c = 0;
  int opext = 0;

  // Initialize
  reg[0] = 0;

  while(!error) {
    uint8_t op = *src++;
    LOG("DEBUG> OP = %d\n", op);

    switch(op) {
      case OP_NOP:
        LOG("DEBUG> Nop\n");
        break;
      case OP_MOVE:
        a = *src++;
        b = *src++;
        reg[a] = reg[b];
        LOG("DEBUG> r[%d] = r[%d] : %ld\n", a, b, reg[b]);
        break;
      case OP_LOADI:
      case OP_LOADINEG:
        a = *src++; b = *src++;
        // if (opext == 2) {
        //   b = (b << 8) + *src++;
        // }
        if (op == OP_LOADINEG) {
          b = -b;
        }
        reg[a] = b;
        LOG("DEBUG> r[%d] = %d\n", a, b);
        break;
      case OP_LOADI__1:
      case OP_LOADI_0:
      case OP_LOADI_1:
      case OP_LOADI_2:
      case OP_LOADI_3:
      case OP_LOADI_4:
      case OP_LOADI_5:
      case OP_LOADI_6:
      case OP_LOADI_7:
        a = *src++;
        reg[a] = op - OP_LOADI_0;
        LOG("DEBUG> Load INT: %ld\n", reg[a]);
        break;
      case OP_LOADSELF:
        a = *src++;
        reg[a] = reg[0];
        LOG("DEBUG> r[%d] = self %ld\n", a, reg[a]);
        break;
      case OP_SEND:
        a = *src++; b = *src++; c = *src++;
        LOG("DEBUG> a = %d, b = %d, c = %d\n", a, b, c);

        const uint8_t* fn = irep_get(data, IREP_TYPE_SYMBOL, b);
        // TODO: Check for magic number 2
        LOG("DEBUG> method = \"%s\"\n", (const char*)(fn));

        // TODO: Always call "puts"
        printf("%d\n", ((int)(reg[a + 1])));
        break;
      case OP_RETURN:
      case OP_RETURN_BLK:
      case OP_BREAK:
        a = *src++;
        LOG("DEBUG> %s r[%d]\n", op == OP_RETURN ? "return" : "break", a);
        return reg[a];
      case OP_ADD:
        a = *src++;
        reg[a] += reg[a + 1];
        LOG("DEBUG> r[%d] = r[%d] + r[%d]\n", a, a, a + 1);
        break;
      case OP_ADDI:
        a = *src++; b = *src++;
        reg[a] += b;
        LOG("DEBUG> r[%d] = r[%d] + %d\n", a, a, b);
        break;
      default:
        LOG("DEBUG> Unsupport OP Code: %d\n", op);
        error = 1;
    }
  }

  return 0;
}
