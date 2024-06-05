struct Cartridge;

struct Cartridge {
  Node::Peripheral node;
  VFS::Pak pak;

  auto title() const -> string { return information.title; }

  //cartridge.cpp
  auto allocate(Node::Port) -> Node::Peripheral;
  auto connect() -> void;
  auto disconnect() -> void;

  auto power() -> void {}

  struct Information {
    string title;
  } information;

  Memory::Readable<n8> rom;

  auto read(n32 address) -> n8;

protected:
  auto load(Memory::Readable<n8>& memory, string name) -> bool;
};

#include "slot.hpp"
extern Cartridge& cartridge;
