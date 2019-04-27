#include "instruction/instruction_set.h"

using namespace vm;

void InstructionSet::Add(Instruction& instruction) {
  set.insert({instruction.GetOpcode(), instruction});
}

Instruction* InstructionSet::Fetch(word mc) {
  std::map<word,Instruction&>::iterator it;

  it = set.find(mc);
  if(it != set.end()) {
    return &(it->second);
  }

  return nullptr;
}
