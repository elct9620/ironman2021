#ifndef _IRON_VM_H_
#define _IRON_VM_H_

// TODO: pass implement mrb_state
#define mrb_run(irep) mrb_exec(irep_load(irep))

int mrb_exec(const uint8_t* irep);

#endif
