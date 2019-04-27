#include "instruction/set/noop.h"

using namespace vm;

NOOP::NOOP(word opcode) : opcode(opcode) {}

word NOOP::GetOpcode() {
  return opcode;
}

void NOOP::Execute(word operand, Memory *im, Memory *dm, Memory* stack, word& ip, word &sp, byte& flags) {
  ip++;
  return;
}
