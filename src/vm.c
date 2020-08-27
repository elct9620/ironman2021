#include "vm.h"
#include "irep.h"
#include "utils.h"
#include "opcode.h"

int mrb_exec(mrb_state* mrb, const uint8_t* data) {
  const uint8_t* p = data;
  uint8_t len;

  mrb_irep* irep = read_irep(p, &len);
  p += len;

  DEBUG_LOG("locals: %d, regs: %d, ireps: %d", irep->nlocals, irep->nregs, irep->nirep);

  // TODO: Move register to mrb_state
  intptr_t reg[irep->nregs - 1];

  // Temp
  int32_t a = 0;
  int32_t b = 0;
  int32_t c = 0;
  int opext = 0;

  // Initialize
  reg[0] = 0;

  for(;;) {
    uint8_t insn = READ_B();
    DEBUG_LOG("OP = %d", insn);

    switch(insn) {
      CASE(OP_NOP, Z) {
        DEBUG_LOG("NOP");
        NEXT;
      }
      CASE(OP_MOVE, BB) {
        reg[a] = reg[b];
        DEBUG_LOG("r[%d] = r[%d] : %ld", a, b, reg[b]);
        NEXT;
      }
      CASE(OP_LOADI, BB) {
        reg[a] = b;
        DEBUG_LOG("r[%d] = %d", a, b);
        NEXT;
      }
      CASE(OP_LOADINEG, BB) {
        reg[a] = -b;
        DEBUG_LOG("r[%d] = %d", a, b);
        NEXT;
      }
      CASE(OP_LOADI__1, B) goto L_LOADI;
      CASE(OP_LOADI_0, B) goto L_LOADI;
      CASE(OP_LOADI_1, B) goto L_LOADI;
      CASE(OP_LOADI_2, B) goto L_LOADI;
      CASE(OP_LOADI_3, B) goto L_LOADI;
      CASE(OP_LOADI_4, B) goto L_LOADI;
      CASE(OP_LOADI_5, B) goto L_LOADI;
      CASE(OP_LOADI_6, B) goto L_LOADI;
      CASE(OP_LOADI_7, B) {
      L_LOADI:
        reg[a] = insn - OP_LOADI_0;
        DEBUG_LOG("Load INT: %ld", reg[a]);
        NEXT;
      }
      CASE(OP_LOADSELF, B) {
        reg[a] = reg[0];
        DEBUG_LOG("r[%d] = self %ld", a, reg[a]);
        NEXT;
      }
      CASE(OP_SEND, BBB) {
        DEBUG_LOG("a = %d, b = %d, c = %d", a, b, c);
        const char* fn = (const char*)irep_get(data, IREP_TYPE_SYMBOL, b);
        DEBUG_LOG("method = \"%s\"", (const char*)(fn));

        // TODO: Always call "puts"
        printf("%d\n", ((int)(reg[a + 1])));
        NEXT;
      }
      CASE(OP_BREAK, B) goto L_RETURN;
      CASE(OP_RETURN_BLK, B) goto L_RETURN;
      CASE(OP_RETURN, B)
      {
      L_RETURN:
        DEBUG_LOG("%s r[%d]", insn == OP_RETURN ? "return" : "break", a);
        NEXT;
      }
      CASE(OP_ADD, B) {
        reg[a] += reg[a + 1];
        DEBUG_LOG("r[%d] = r[%d] + r[%d]", a, a, a + 1);
        NEXT;
      }
      CASE(OP_ADDI, BB) {
        reg[a] += b;
        DEBUG_LOG("r[%d] = r[%d] + %d", a, a, b);
        NEXT;
      }
      CASE(OP_STOP, Z) {
        DEBUG_LOG("STOP");
        return 0;
      }
      default:
        DEBUG_LOG("Unsupport OP Code: %d", insn);
        mrb->exc = 1;
    }

    if (mrb->exc) break;
  }

  return 0;
}
