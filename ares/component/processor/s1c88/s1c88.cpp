#include <ares/ares.hpp>
#include "s1c88.hpp"

namespace ares {

#include "registers.hpp"
#include "disassembler.cpp"
#include "algorithms.cpp"
#include "instruction.cpp"
#include "instructions.cpp"
#include "memory.cpp"

auto S1C88::power() -> void {
  NB = 0x01;  //todo: confirm this is correct power-on state?
  CB = 0x01;
}

}
