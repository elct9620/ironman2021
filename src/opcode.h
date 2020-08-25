#ifndef _IRON_OPCODE_H_
#define _IRON_OPCODE_H_

/**
 * Implement mruby 2.1.2
 *
 * Reference: https://github.com/mruby/mruby/blob/2.1.2/include/mruby/ops.h
 *
 * CODE = (Line Number - 14)
 *
 * Example:
 * OP_LOADI__1
 *   Line Number = 19
 *   OP_CODE = (19 - 14) = 5
 */

enum {
  OP_NOP,
  OP_MOVE,
  OP_LOADL,
  OP_LOADI,
  OP_LOADINEG,
  OP_LOADI__1 = 5,
  OP_LOADI_0,
  OP_LOADI_1,
  OP_LOADI_2,
  OP_LOADI_3,
  OP_LOADI_4,
  OP_LOADI_5,
  OP_LOADI_6,
  OP_LOADI_7,
  OP_LOADSYM,
  OP_LOADNIL,
  OP_LOADSELF,
  OP_LOADT,
  OP_LOADF,
  OP_SEND = 46,
  OP_RETURN = 55,
  OP_RETURN_BLK,
  OP_BREAK,
  OP_ADD = 59,
  OP_ADDI,
};

#endif
