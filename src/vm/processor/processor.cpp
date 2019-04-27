#include <iostream>

#include "processor/processor.h"

using namespace vm;
using namespace std;

Processor::Processor(InstructionSet& is, Memory* im, Memory* dm, Memory* stack)
: is(is), im(im), dm(dm), stack(stack), ip(0), sp(stack->GetSize() - 1), flags(0), error(0)
{}

Processor::~Processor() {

}

void Processor::ExecuteMachineCode() {

  if(im->GetSize() == 0) {
    error = ERROR_INSTRUCTION_MEMORY_ZERO;
    return;
  }

  if(im->GetSize() % 2 == 1) {
    error = ERROR_INSTRUCTION_MEMORY_NOT_EVEN;
    return;
  }

  if(dm->GetSize() == 0) {
    error = ERROR_DATA_MEMORY_ZERO;
    return;
  }

  if(stack->GetSize() == 0) {
    error = ERROR_STACK_MEMORY_ZERO;
    return;
  }

  while(!DetectHalt()) {
    word opcode = im->GetLocation(ip);
    Instruction* instruction = is.Fetch(opcode);

    if(instruction == nullptr) {
      error = ERROR_INVALID_INSTRUCTION;
      SetHaltStatus();
      continue;
    }

    ip++;

    word operand = im->GetLocation(ip);
    instruction->Execute(operand, stack, ip, sp, flags);

    if(ip < 0 || ip > im->GetSize()) {
      error = ERROR_INSTRUCTION_POINTER_OUT_OF_RANGE;
      SetHaltStatus();
      continue;
    }

    if(sp < 0 || sp > stack->GetSize()) {
      error = ERROR_STACK_POINTER_OUT_OF_RANGE;
      SetHaltStatus();
      continue;
    }
  }
}

bool Processor::DetectHalt() {
  return flags & STATUS_BITMASK_HALT;
}

void Processor::SetHaltStatus() {
  flags |= STATUS_BITMASK_HALT;
}

#ifdef GTEST

byte Processor::ReadCarryStatus() {
  return flags & STATUS_BITMASK_CARRY;
}

byte Processor::ReadOverflowStatus() {
  return flags & STATUS_BITMASK_OVERFLOW;
}

byte Processor::ReadZeroStatus() {
  return flags & STATUS_BITMASK_ZERO;
}

byte Processor::ReadNegativeStatus() {
  return flags & STATUS_BITMASK_NEGATIVE;
}

byte Processor::ReadHaltStatus() {
  return flags & STATUS_BITMASK_HALT;
}

byte Processor::ReadError() {
  return error;
}

word Processor::ReadInstructionPointer() {
  return ip;
}

word Processor::ReadStackPointer() {
  return sp;
}

#endif
