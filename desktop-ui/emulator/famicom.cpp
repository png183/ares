struct Famicom : Emulator {
  Famicom();
  auto load() -> LoadResult override;
  auto save() -> bool override;
  auto pak(ares::Node::Object) -> shared_pointer<vfs::directory> override;
};

Famicom::Famicom() {
  manufacturer = "Nintendo";
  name = "Famicom";

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
    device.digital("Microphone", virtualPorts[id].pad.north);
    port.append(device); }

  { InputDevice device{"Zapper"};
    device.relative("X",         virtualPorts[id].mouse.x);
    device.relative("Y",         virtualPorts[id].mouse.y);
    device.digital ("Trigger",   virtualPorts[id].mouse.left);
    port.append(device);
    }

    ports.append(port);
  }
}

auto Famicom::load() -> LoadResult {
  game = mia::Medium::create("Famicom");
  string location = Emulator::load(game, configuration.game);
  if(!location) return noFileSelected;
  LoadResult result = game->load(location);
  if(result != successful) return result;

  system = mia::System::create("Famicom");
  result = system->load();
  if(result != successful) return result;

  auto region = Emulator::region();
  if(!ares::Famicom::load(root, {"[Nintendo] Famicom (", region, ")"})) return otherError;

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

  return successful;
}

auto Famicom::save() -> bool {
  root->save();
  system->save(system->location);
  game->save(game->location);
  return true;
}

auto Famicom::pak(ares::Node::Object node) -> shared_pointer<vfs::directory> {
  if(node->name() == "Famicom") return system->pak;
  if(node->name() == "Famicom Cartridge") return game->pak;
  return {};
}
