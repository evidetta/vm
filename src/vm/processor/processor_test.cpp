#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "processor/processor.h"
#include "instruction/mock_instruction.h"

#include <iostream>

using namespace testing;
using namespace std;

namespace vm {

  class ProcessorTest : public Test {};

  TEST_F(ProcessorTest, Processor) {
    InstructionSet is = InstructionSet();
    Memory im = Memory(1024);
    Memory dm = Memory(1024);
    Memory stack = Memory(1024);
    Processor processor = Processor(is, &im, &dm, &stack);

    byte carry = processor.ReadCarryStatus();
    byte overflow =  processor.ReadOverflowStatus();
    byte zero = processor.ReadZeroStatus();
    byte negative = processor.ReadNegativeStatus();
    byte halt = processor.ReadHaltStatus();
    byte error = processor.ReadError();
    word ip = processor.ReadInstructionPointer();
    word sp = processor.ReadStackPointer();

    ASSERT_EQ(carry, (byte)0);
    ASSERT_EQ(overflow, (byte)0);
    ASSERT_EQ(zero, (byte)0);
    ASSERT_EQ(negative, (byte)0);
    ASSERT_EQ(halt, (byte)0);
    ASSERT_EQ(error, (byte)0);
    ASSERT_EQ(ip, 0);
    ASSERT_EQ(sp, 1023);
  }

  TEST_F(ProcessorTest, ExecuteMachineCode_InstructionMemoryNotEven) {
    InstructionSet is = InstructionSet();
    Memory im = Memory(1023);
    Memory dm = Memory(1024);
    Memory stack = Memory(1024);
    Processor processor = Processor(is, &im, &dm, &stack);

    processor.ExecuteMachineCode();

    byte error = processor.ReadError();
    ASSERT_EQ(error, ERROR_INSTRUCTION_MEMORY_NOT_EVEN);
  }

  TEST_F(ProcessorTest, ExecuteMachineCode_InstructionMemoryZero) {
    InstructionSet is = InstructionSet();
    Memory im = Memory(0);
    Memory dm = Memory(1024);
    Memory stack = Memory(1024);
    Processor processor = Processor(is, &im, &dm, &stack);

    processor.ExecuteMachineCode();

    byte error = processor.ReadError();
    ASSERT_EQ(error, ERROR_INSTRUCTION_MEMORY_ZERO);
  }

  TEST_F(ProcessorTest, ExecuteMachineCode_DataMemoryZero) {
    InstructionSet is = InstructionSet();
    Memory im = Memory(1024);
    Memory dm = Memory(0);
    Memory stack = Memory(1024);
    Processor processor = Processor(is, &im, &dm, &stack);

    processor.ExecuteMachineCode();

    byte error = processor.ReadError();
    ASSERT_EQ(error, ERROR_DATA_MEMORY_ZERO);
  }

  TEST_F(ProcessorTest, ExecuteMachineCode_StackMemoryZero) {
    InstructionSet is = InstructionSet();
    Memory im = Memory(1024);
    Memory dm = Memory(1024);
    Memory stack = Memory(0);
    Processor processor = Processor(is, &im, &dm, &stack);

    processor.ExecuteMachineCode();

    byte error = processor.ReadError();
    ASSERT_EQ(error, ERROR_STACK_MEMORY_ZERO);
  }

  TEST_F(ProcessorTest, ExecuteMachineCode_InvalidInstruction) {
    InstructionSet is = InstructionSet();
    Memory im = Memory(1024);
    Memory dm = Memory(1024);
    Memory stack = Memory(1024);
    Processor processor = Processor(is, &im, &dm, &stack);

    processor.ExecuteMachineCode();

    byte error = processor.ReadError();
    ASSERT_EQ(error, ERROR_INVALID_INSTRUCTION);
  }

  TEST_F(ProcessorTest, ExecuteMachineCode_InstructionPointerOutOfRange) {
    InstructionSet is = InstructionSet();
    Memory im = Memory(1024);
    Memory dm = Memory(1024);
    Memory stack = Memory(1024);

    word opcode = 0;
    MockInstruction instruction = MockInstruction();

    EXPECT_CALL(instruction, GetOpcode()).WillOnce(Return(opcode));
    EXPECT_CALL(instruction, Execute(_, _, _, _, _)).WillOnce(Invoke([](word operand, Memory* stack, word& ip, word &sp, byte& flags){
      ip = 1025;
    }));

    is.Add(instruction);

    Processor processor = Processor(is, &im, &dm, &stack);

    processor.ExecuteMachineCode();

    byte error = processor.ReadError();
    ASSERT_EQ(error, ERROR_INSTRUCTION_POINTER_OUT_OF_RANGE);
  }

  TEST_F(ProcessorTest, ExecuteMachineCode_StackPointerOutOfRange) {
    InstructionSet is = InstructionSet();
    Memory im = Memory(1024);
    Memory dm = Memory(1024);
    Memory stack = Memory(1024);

    word opcode = 0;
    MockInstruction instruction = MockInstruction();

    EXPECT_CALL(instruction, GetOpcode()).WillOnce(Return(opcode));
    EXPECT_CALL(instruction, Execute(_, _, _, _, _)).WillOnce(Invoke([](word operand, Memory* stack, word& ip, word &sp, byte& flags){
      sp = stack->GetSize() + 1;
    }));

    is.Add(instruction);

    Processor processor = Processor(is, &im, &dm, &stack);

    processor.ExecuteMachineCode();

    byte error = processor.ReadError();
    ASSERT_EQ(error, ERROR_STACK_POINTER_OUT_OF_RANGE);
  }

  TEST_F(ProcessorTest, ExecuteMachineCode_Success) {
    InstructionSet is = InstructionSet();
    Memory im = Memory(1024);
    Memory dm = Memory(1024);
    Memory stack = Memory(1024);

    word opcode = 0;
    MockInstruction instruction = MockInstruction();

    EXPECT_CALL(instruction, GetOpcode()).WillOnce(Return(opcode));
    EXPECT_CALL(instruction, Execute(_, _, _, _, _)).WillOnce(Invoke([](word operand, Memory* stack, word& ip, word &sp, byte& flags){
      flags |= STATUS_BITMASK_HALT;
    }));

    is.Add(instruction);

    Processor processor = Processor(is, &im, &dm, &stack);

    processor.ExecuteMachineCode();

    byte error = processor.ReadError();
    ASSERT_EQ(error, ERROR_NO_ERROR);
  }
}
