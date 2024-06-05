#include <base6502/base6502.hpp>

namespace ares::Base6502 {

auto enumerate() -> vector<string> {
  return {
    "[PLACEHOLDER] Base6502 (NTSC-U)",
  };
}

auto load(Node::System& node, string name) -> bool {
  if(!enumerate().find(name)) return false;
  return system.load(node, name);
}

Scheduler scheduler;
System system;
#include "controls.cpp"
#include "serialization.cpp"

auto System::game() -> string {
  if(cartridge.node) {
    return cartridge.title();
  }

  return "(no cartridge connected)";
}

auto System::run() -> void {
  scheduler.enter();
}

auto System::load(Node::System& root, string name) -> bool {
  if(node) unload();

  node = Node::System::create(information.name);
  node->setGame({&System::game, this});
  node->setRun({&System::run, this});
  node->setPower({&System::power, this});
  node->setUnload({&System::unload, this});
  node->setSerialize({&System::serialize, this});
  node->setUnserialize({&System::unserialize, this});
  root = node;

  scheduler.reset();
  controls.load(node);
  cpu.load(node);
  ppu.load(node);
  cartridgeSlot.load(node);
  return true;
}

auto System::unload() -> void {
  if(!node) return;
  cpu.unload();
  ppu.unload();
  cartridgeSlot.unload();
  node = {};
}

auto System::power(bool reset) -> void {
  for(auto& setting : node->find<Node::Setting::Setting>()) setting->setLatch();

  cartridge.power();
  cpu.power(reset);
  ppu.power();
  scheduler.power(cpu);
}

}
