#ifndef _IRON_VM_H_
#define _IRON_VM_H_

#include <stdint.h>

#include "iron.h"
#include "irep.h"
#include "opcode.h"

#define CASE(insn,ops) case insn: FETCH_##ops ();;
#define NEXT break

// TODO: pass implement mrb_state
#define mrb_run(mrb, irep) mrb_exec(mrb, irep_load(irep))

#ifdef __cplusplus
extern "C" {
#endif

IRON_API
int mrb_exec(mrb_state* mrb, const uint8_t* irep);

#ifdef __cplusplus
}
#endif

#endif
