#pragma once

#include <ares/ares.hpp>

#include <component/processor/mos6502/mos6502.hpp>

namespace ares::Base6502 {
  #include <ares/inline.hpp>
  auto enumerate() -> vector<string>;
  auto load(Node::System& node, string name) -> bool;

  #include <base6502/system/system.hpp>
  #include <base6502/cartridge/cartridge.hpp>
  #include <base6502/cpu/cpu.hpp>
  #include <base6502/ppu/ppu.hpp>
}
