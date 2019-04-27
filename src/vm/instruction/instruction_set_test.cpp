#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <map>

#include "instruction/instruction_set.h"
#include "instruction/mock_instruction.h"

using namespace ::testing;

namespace vm {

  class InstructionSetTest : public Test {
  public:
    InstructionSet *instruction_set;
    MockInstruction *instruction;
    word opcode;

    void SetUp() {
      instruction_set = new InstructionSet();
      instruction = new MockInstruction();
      opcode = 128;
    }

    void TearDown() {
      delete instruction;
      delete instruction_set;
    }
  };

  TEST_F(InstructionSetTest, Add) {
    std::map<word,Instruction&>::iterator it;
    EXPECT_CALL(*instruction, GetOpcode()).WillOnce(Return(opcode));
    instruction_set->Add(*instruction);
    it = instruction_set->set.find(opcode);
    ASSERT_TRUE(it != instruction_set->set.end());
  }

  TEST_F(InstructionSetTest, Fetch_Hit) {
    instruction_set->set.insert({opcode, *instruction});
    Instruction* out = instruction_set->Fetch(opcode);
    ASSERT_EQ(out, instruction);
  }

  TEST_F(InstructionSetTest, Fetch_Miss) {
    Instruction* out = instruction_set->Fetch(opcode);
    ASSERT_EQ(out, nullptr);
  }
}
