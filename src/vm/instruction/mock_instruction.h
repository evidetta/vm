#ifndef MOCK_INSTRUCTION_H
#define MOCK_INSTRUCTION_H

#include <gmock/gmock.h>
#include "instruction/instruction.h"

namespace vm {

  class MockInstruction : public Instruction {
  public:
    MOCK_METHOD0(GetOpcode, word());
    MOCK_METHOD5(Execute, void(word, Memory*, word&, word&, byte&));
  };

}

#endif
