#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "instruction/set/noop.h"
#include "memory/memory.h"

using namespace ::testing;

namespace vm {

  class NOOPTest : public Test {
  public:
    NOOP *instruction;

    word operand;
    Memory *im;
    Memory *dm;
    Memory* stack;
    word ip;
    word sp;
    byte flags;

    void SetUp() {
      instruction = new NOOP(OPCODE_NOOP);
      im = new Memory(1024);
      dm = new Memory(1024);
      stack = new Memory(1024);

      operand = 0;
      ip = 0;
      sp = 1023;
      flags = 0;
    }

    void TearDown() {
      delete stack;
      delete dm;
      delete im;
      delete instruction;
    }
  };

  TEST_F(NOOPTest, Execute) {
    word oldIP = ip;
    word oldSP = sp;
    byte oldFlags = flags;

    instruction->Execute(operand, im, dm, stack, ip, sp, flags);

    ASSERT_EQ(flags, oldFlags);
    ASSERT_EQ(sp, oldSP);
    ASSERT_EQ(ip, oldIP + 1);

    for(word i = 0; i < im->GetSize(); i++) {
      ASSERT_EQ(im->GetLocation(i), 0);
    }

    for(word i = 0; i < dm->GetSize(); i++) {
      ASSERT_EQ(dm->GetLocation(i), 0);
    }

    for(word i = 0; i < stack->GetSize(); i++) {
      ASSERT_EQ(stack->GetLocation(i), 0);
    }
  }

}
