struct Base6502 : System {
  auto name() -> string override { return "Base6502"; }
  auto load(string location) -> bool override;
  auto save(string location) -> bool override;
};

auto Base6502::load(string location) -> bool {
  this->location = locate();
  pak = new vfs::directory;
  return true;
}

auto Base6502::save(string location) -> bool {
  return true;
}
