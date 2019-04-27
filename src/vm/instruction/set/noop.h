#ifndef NOOP_H
#define NOOP_H

#include "instruction/instruction.h"

namespace vm {

  class NOOP : public Instruction {
  public:
    NOOP(word opcode);

    word GetOpcode();
    void Execute(word operand, Memory *im, Memory *dm, Memory* stack, word& ip, word &sp, byte& flags);

  private:
    word opcode;
  };

}

#endif
