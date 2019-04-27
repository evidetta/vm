#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "vm.h"
#include "memory/memory.h"

namespace vm {

  class Instruction {
  public:
    virtual ~Instruction() = 0;

    virtual word GetOpcode() = 0;
    virtual void Execute(word operand, Memory* stack, word& ip, word &sp, byte& flags) = 0;
  };
}

#endif
