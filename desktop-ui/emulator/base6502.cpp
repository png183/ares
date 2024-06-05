struct Base6502 : Emulator {
  Base6502();
  auto load() -> bool override;
  auto save() -> bool override;
  auto pak(ares::Node::Object) -> shared_pointer<vfs::directory> override;
};

Base6502::Base6502() {
  manufacturer = "PLACEHOLDER";
  name = "Base6502";

  for(auto id : range(2)) {
    InputPort port{string{"Controller Port ", 1 + id}};

  { InputDevice device{"Gamepad"};
    device.digital("Up",         virtualPorts[id].pad.up);
    device.digital("Down",       virtualPorts[id].pad.down);
    device.digital("Left",       virtualPorts[id].pad.left);
    device.digital("Right",      virtualPorts[id].pad.right);
    device.digital("B",          virtualPorts[id].pad.west);
    device.digital("A",          virtualPorts[id].pad.south);
    device.digital("Select",     virtualPorts[id].pad.select);
    device.digital("Start",      virtualPorts[id].pad.start);
    port.append(device); }

    ports.append(port);
  }
}

auto Base6502::load() -> bool {
  game = mia::Medium::create("Base6502");
  if(!game->load(Emulator::load(game, configuration.game))) return false;

  system = mia::System::create("Base6502");
  if(!system->load()) return false;

  auto region = Emulator::region();
  if(!ares::Base6502::load(root, {"[PLACEHOLDER] Base6502 (", region, ")"})) return false;

  if(auto port = root->find<ares::Node::Port>("Cartridge Slot")) {
    port->allocate();
    port->connect();
  }

  if(auto port = root->find<ares::Node::Port>("Controller Port 1")) {
    port->allocate("Gamepad");
    port->connect();
  }

  if(auto port = root->find<ares::Node::Port>("Controller Port 2")) {
    port->allocate("Gamepad");
    port->connect();
  }

  if(game->pak->attribute("system") == "EPSM") {
    if(auto port = root->find<ares::Node::Port>("Expansion Port")) {
      port->allocate("EPSM");
      port->connect();
    }
  }

  return true;
}

auto Base6502::save() -> bool {
  root->save();
  system->save(system->location);
  game->save(game->location);
  return true;
}

auto Base6502::pak(ares::Node::Object node) -> shared_pointer<vfs::directory> {
  if(node->name() == "Base6502") return system->pak;
  if(node->name() == "Base6502 Cartridge") return game->pak;
  return {};
}
