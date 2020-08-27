#ifndef _IRON_VM_H_
#define _IRON_VM_H_

#include <stdint.h>

#include "irep.h"
#include "opcode.h"

#define CASE(insn,ops) case insn: FETCH_##ops ();;
#define NEXT break

// TODO: pass implement mrb_state
#define mrb_run(irep) mrb_exec(irep_load(irep))

int mrb_exec(const uint8_t* irep);

#endif
