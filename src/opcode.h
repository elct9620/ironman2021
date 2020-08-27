#ifndef _IRON_OPCODE_H_
#define _IRON_OPCODE_H_

/**
 * B = 8bit
 * S = 16bit
 * W = 24bit
 * L = 32bit
 */

#define PEEK_B(pc) (*(pc))
#define PEEK_S(pc) ((pc)[0]<<8|(pc)[1])
#define PEEK_W(pc) ((pc)[0]<<16|(pc)[1]<<8|(pc)[2])
#define PEEK_L(pc) ((pc)[0]<<24|(pc)[1]<<16|(pc)[2]<<8|(pc)[3])

#define READ_B() PEEK_B(p++)
#define READ_S() (p+=2, PEEK_S(p-2))
#define READ_W() (p+=3, PEEK_W(p-3))
#define READ_L() (p+=4, PEEK_L(p-4))

#define FETCH_Z() /* noop */
#define FETCH_B() do { a = READ_B(); } while(0)
#define FETCH_BB() do { a = READ_B(); b = READ_B(); } while(0)
#define FETCH_BBB() do { a = READ_B(); b = READ_B(); c = READ_B(); } while(0)

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
  OP_STOP = 103,
};

#endif
