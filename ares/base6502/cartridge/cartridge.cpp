#include <base6502/base6502.hpp>

namespace ares::Base6502 {

Cartridge& cartridge = cartridgeSlot.cartridge;
#include "slot.cpp"

auto Cartridge::allocate(Node::Port parent) -> Node::Peripheral {
  return node = parent->append<Node::Peripheral>(string{system.name(), " Cartridge"});
}

auto Cartridge::load(Memory::Readable<n8>& memory, string name) -> bool {
  if(auto fp = pak->read(name)) {
    memory.allocate(fp->size(), 0xff);
    memory.load(fp);
    return true;
  }
  return false;
}

auto Cartridge::connect() -> void {
  if(!node->setPak(pak = platform->pak(node))) return;

  information = {};
  information.title  = pak->attribute("title");

  load(rom, "program.rom");

  power();
}

auto Cartridge::disconnect() -> void {
  if(!node) return;
  pak.reset();
  node.reset();
}

auto Cartridge::read(n32 address) -> n8 {
  return rom.read(address);
}

}
