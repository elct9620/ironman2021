#include <khash.h>

#include "vm.h"
#include "irep.h"
#include "utils.h"
#include "opcode.h"
#include "iron.h"

int mrb_exec(mrb_state* mrb, const uint8_t* data) {
  static const mrb_value mrb_value_zero = { 0 };
  const uint8_t* p = data;
  uint8_t len;

  mrb_irep* irep = read_irep(p, &len);
  p += len;

  DEBUG_LOG("locals: %d, regs: %d, ireps: %d", irep->nlocals, irep->nregs, irep->nirep);

  mrb->stack = (mrb_value*)malloc(sizeof(mrb_value) * (irep->nregs -  1));

  // Temp
  int32_t a = 0;
  int32_t b = 0;
  int32_t c = 0;
  int opext = 0;
  const uint8_t* porg = p;

  // Initialize
  mrb->stack[0] = mrb_value_zero;

  for(;;) {
    uint8_t insn = READ_B();
    DEBUG_LOG("OP = %d", insn);

    switch(insn) {
      CASE(OP_NOP, Z) {
        DEBUG_LOG("NOP");
        NEXT;
      }
      CASE(OP_MOVE, BB) {
        mrb->stack[a] = mrb->stack[b];
        DEBUG_LOG("r[%d] = r[%d] : %p", a, b, (void*)&mrb->regs[b]);
        NEXT;
      }
      CASE(OP_LOADI, BB) {
        SET_INT_VALUE(mrb->stack[a], b);
        DEBUG_LOG("r[%d] = %d", a, b);
        NEXT;
      }
      CASE(OP_LOADINEG, BB) {
        SET_INT_VALUE(mrb->stack[a], -b);
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
        SET_INT_VALUE(mrb->stack[a], insn - OP_LOADI_0);
        DEBUG_LOG("r[%d] = %p", a, (void*)&mrb->stack[a]);
        NEXT;
      }
      CASE(OP_LOADNIL, B) {
        SET_NIL_VALUE(mrb->stack[a]);
        DEBUG_LOG("r[%d] = nil", a);
        NEXT;
      }
      CASE(OP_LOADSELF, B) {
        mrb->stack[a] = mrb->stack[0];
        DEBUG_LOG("r[%d] = self %p", a, (void *)&mrb->stack[a]);
        NEXT;
      }
      CASE(OP_LOADT, B)
      CASE(OP_LOADF, B) {
      L_LOADF:
        if(insn == OP_LOADT) {
          SET_TRUE_VALUE(mrb->stack[a]);
        } else {
          SET_FALSE_VALUE(mrb->stack[a]);
        }
        DEBUG_LOG("r[%d] = %s", a, insn == OP_LOADT ? "true" : "false");
        NEXT;
      }
      CASE(OP_JMP, S) {
        p = porg + a;
        DEBUG_LOG("jmp %d", b);
        NEXT;
      }
      CASE(OP_JMPIF, BS) goto L_JMPNOT;
      CASE(OP_JMPNOT, BS) {
      L_JMPNOT:
        if (insn == OP_JMPIF) {
          DEBUG_LOG("jmp %d if r[%d] == %p", b, a, (void*)&mrb->stack[a]);
        } else {
          DEBUG_LOG("jmp %d if !r[%d] == %p", b, a, (void*)&mrb->stack[a]);
        }

        if ((insn == OP_JMPIF) == (!(IS_NIL_VALUE(mrb->stack[a])))) {
          p = porg + b;
        }
        NEXT;
      }
      CASE(OP_SEND, BBB) {
        DEBUG_LOG("a = %d, b = %d, c = %d", a, b, c);
        const char* fn = (const char*)irep_get(data, IREP_TYPE_SYMBOL, b);
        DEBUG_LOG("method = \"%s\"", (const char*)(fn));

        // TODO: Always call "puts"
        khiter_t key = kh_get(mt, mrb->mt, fn);
        if (key == kh_end(mrb->mt)) {
          DEBUG_LOG("Undefined Method");
        } else {
          // TODO: Implement mrb_funcall
          mrb_func_t func = kh_value(mrb->mt, key);
          // TODO: Load current object
          mrb_value self = mrb_nil_value();
          mrb_value argv[c];
          for(int i = 1; i <= c; i++) {
            argv[i - 1] = mrb->stack[a + i];
          }
          mrb_callinfo ci = {
            .argc = c,
            .argv = argv
          };
          mrb->ci = &ci;

          func(mrb, self);

          mrb->ci = NULL;
        }
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
        mrb->stack[a].value.i = mrb_fixnum(mrb->stack[a]) + mrb_fixnum(mrb->stack[a + 1]);
        DEBUG_LOG("r[%d] = r[%d] + r[%d]", a, a, a + 1);
        NEXT;
      }
      CASE(OP_ADDI, BB) {
        mrb->stack[a].value.i += b;
        DEBUG_LOG("r[%d] = r[%d] + %d", a, a, b);
        NEXT;
      }
      CASE(OP_EQ, B) {
        // TODO: Implement mrb_value
        if(mrb->stack[a].value.i == mrb->stack[a + 1].value.i) {
          SET_TRUE_VALUE(mrb->stack[a]);
        } else {
          SET_FALSE_VALUE(mrb->stack[a]);
        }
        DEBUG_LOG("r[%d] = r[%d] == r[%d+1]", a, a, a);
        NEXT;
      }
      CASE(OP_LT, B) {
        if(mrb->stack[a].value.i < mrb->stack[a + 1].value.i) {
          SET_TRUE_VALUE(mrb->stack[a]);
        } else {
          SET_FALSE_VALUE(mrb->stack[a]);
        }
        DEBUG_LOG("r[%d] = r[%d] < r[%d+1]", a, a, a);
        NEXT;
      }
      CASE(OP_LE, B) {
        if(mrb->stack[a].value.i <= mrb->stack[a + 1].value.i) {
          SET_TRUE_VALUE(mrb->stack[a]);
        } else {
          SET_FALSE_VALUE(mrb->stack[a]);
        }
        DEBUG_LOG("r[%d] = r[%d] <= r[%d+1]", a, a, a);
        NEXT;
      }
      CASE(OP_GT, B) {
        if(mrb->stack[a].value.i > mrb->stack[a + 1].value.i) {
          SET_TRUE_VALUE(mrb->stack[a]);
        } else {
          SET_FALSE_VALUE(mrb->stack[a]);
        }
        DEBUG_LOG("r[%d] = r[%d] > r[%d+1]", a, a, a);
        NEXT;
      }
      CASE(OP_GE, B) {
        if(mrb->stack[a].value.i >= mrb->stack[a + 1].value.i) {
          SET_TRUE_VALUE(mrb->stack[a]);
        } else {
          SET_FALSE_VALUE(mrb->stack[a]);
        }
        DEBUG_LOG("r[%d] = r[%d] >= r[%d+1]", a, a, a);
        NEXT;
      }
      CASE(OP_STRING, BB) {
        const uint8_t* lit = irep_get(data, IREP_TYPE_LITERAL, b);
        int len = PEEK_B(lit - 1);
        char* buf = malloc(len + 1);
        memcpy(buf, lit, len);
        if(mrb->stack[a].value.p) {
          free(mrb->stack[a].value.p);
        }
        mrb->stack[a].tt = MRB_TT_STRING;
        mrb->stack[a].value.p = (void*)buf;
        DEBUG_LOG("r[%d] = str_dup(lit[%d] %s)", a, b, (const char*)mrb->stack[a].value.p);
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

  for(int i = 0; i < irep->nregs; i++) {
    if(mrb->stack[i].value.p) {
      free(mrb->stack[i].value.p);
    }
  }

  free(mrb->stack);
  free(irep);

  return 0;
}
