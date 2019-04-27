#ifndef PROCESSOR_H
#define PROCESSOR_H

#ifdef GTEST
#include <gtest/gtest.h>
#endif

#include "vm.h"
#include "memory/memory.h"
#include "instruction/instruction_set.h"

namespace vm {

  class Processor {
  public:
    Processor(InstructionSet& is, Memory* im, Memory* dm, Memory* stack);
    ~Processor();

    void ExecuteMachineCode();

  private:
    InstructionSet& is;
    Memory* im;
    Memory* dm;
    Memory* stack;

    word ip;
    word sp;
    byte flags;
    byte error;

    bool DetectHalt();
    void SetHaltStatus();

    #ifdef GTEST
    friend class ProcessorTest;
    FRIEND_TEST(ProcessorTest, Processor);
    FRIEND_TEST(ProcessorTest, ExecuteMachineCode_InstructionMemoryNotEven);
    FRIEND_TEST(ProcessorTest, ExecuteMachineCode_InstructionMemoryZero);
    FRIEND_TEST(ProcessorTest, ExecuteMachineCode_DataMemoryZero);
    FRIEND_TEST(ProcessorTest, ExecuteMachineCode_StackMemoryZero);
    FRIEND_TEST(ProcessorTest, ExecuteMachineCode_InvalidInstruction);
    FRIEND_TEST(ProcessorTest, ExecuteMachineCode_InstructionPointerOutOfRange);
    FRIEND_TEST(ProcessorTest, ExecuteMachineCode_StackPointerOutOfRange);
    FRIEND_TEST(ProcessorTest, ExecuteMachineCode_Success);

    byte ReadCarryStatus();
    byte ReadOverflowStatus();
    byte ReadZeroStatus();
    byte ReadNegativeStatus();
    byte ReadHaltStatus();
    byte ReadError();

    word ReadInstructionPointer();
    word ReadStackPointer();
    #endif
  };

}

#endif
