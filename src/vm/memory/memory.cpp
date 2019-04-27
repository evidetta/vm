#include "memory.h"
#include <iostream>

using namespace vm;

Memory::Memory(word size) {
  this->size = size;
  this->ptr = new word[size];

  for(word i = 0; i < size; i++) {
    ptr[i] = 0;
  }
}

Memory::~Memory() {
  if(ptr != nullptr) {
    delete[] ptr;
    ptr = nullptr;
  }
}

word Memory::GetSize() {
  return size;
}

word Memory::GetLocation(const word index) {
  return ptr[index];
}

void Memory::SetLocation(const word index, word value) {
  ptr[index] = value;
}
