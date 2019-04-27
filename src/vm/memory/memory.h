#ifndef MEMORY_H
#define MEMORY_H

#include "vm.h"

namespace vm {

  class Memory {
  public:
    Memory(word size);
    ~Memory();

    word GetSize();
    word GetLocation(const word index);
    void SetLocation(const word index, word value);

  private:
    word *ptr;
    word size;
  };

}

#endif
