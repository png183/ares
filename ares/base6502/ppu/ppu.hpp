struct PPU : Thread {
  Node::Object node;
  Node::Video::Screen screen;

  auto vlines() const -> u32 { return 262; }
  auto displayHeight() const -> u32 { return 242; }
  auto vOverscan() const -> u32 { return 16; }
  auto cyclesPerLine() const -> u32 { return 341; }
  auto displayWidth() const -> u32 { return 282; }
  auto hOverscan() const -> u32 { return 32; }

  //ppu.cpp
  auto load(Node::Object) -> void;
  auto unload() -> void;

  auto main() -> void;
  auto step(u32 clocks) -> void;

  auto scanline() -> void;
  auto frame() -> void;

  auto power() -> void;

  //color.cpp
  auto color(n32) -> n64;

  //serialization.cpp
  auto serialize(serializer&) -> void;

  u32* output;
};

extern PPU ppu;
