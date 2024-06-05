inline auto CPU::readBus(n16 address) -> n8 {
  if(auto result = platform->cheat(address)) return *result;
  if(address <= 0x7fff) return ram.read(address);
  return cartridge.read(address);
}

inline auto CPU::writeBus(n16 address, n8 data) -> void {
  if(address <= 0x7fff) ram.write(address, data);
}

auto CPU::readDebugger(n16 address) -> n8 {
  return readBus(address);
}
