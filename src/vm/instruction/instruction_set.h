#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#ifdef GTEST
#include <gtest/gtest.h>
#endif

#include <map>

#include "instruction/instruction.h"
#include "vm.h"

using namespace std;

namespace vm {

  class InstructionSet {
  public:
    void Add(Instruction& instruction);
    Instruction* Fetch(word mc);

  private:
    map<word, Instruction&> set;

    #ifdef GTEST
    friend class InstructionSetTest;
    FRIEND_TEST(InstructionSetTest, Add);
    FRIEND_TEST(InstructionSetTest, Fetch_Hit);
    FRIEND_TEST(InstructionSetTest, Fetch_Miss);
    #endif
  };

}

#endif
