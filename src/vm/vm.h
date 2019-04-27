#ifndef VM_H
#define VM_H

namespace vm {

  typedef unsigned char byte;
  typedef unsigned long long word;

  const byte STATUS_BITMASK_CARRY = 0x01;
  const byte STATUS_BITMASK_OVERFLOW = 0x02;
  const byte STATUS_BITMASK_ZERO = 0x04;
  const byte STATUS_BITMASK_NEGATIVE = 0x08;
  const byte STATUS_BITMASK_HALT = 0x10;

  const byte ERROR_NO_ERROR = 0x00;
  const byte ERROR_INSTRUCTION_MEMORY_NOT_EVEN = 0x01;
  const byte ERROR_INSTRUCTION_MEMORY_ZERO = 0x02;
  const byte ERROR_INVALID_INSTRUCTION = 0x03;
  const byte ERROR_DATA_MEMORY_ZERO = 0x04;
  const byte ERROR_STACK_MEMORY_ZERO =0x05;
  const byte ERROR_INSTRUCTION_POINTER_OUT_OF_RANGE = 0x06;
  const byte ERROR_STACK_POINTER_OUT_OF_RANGE = 0x07;

}

#endif
