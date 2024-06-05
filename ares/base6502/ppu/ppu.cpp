#include <base6502/base6502.hpp>

namespace ares::Base6502 {

PPU ppu;
#include "color.cpp"
#include "serialization.cpp"

auto PPU::load(Node::Object parent) -> void {
  node = parent->append<Node::Object>("PPU");

  screen = node->append<Node::Video::Screen>("Screen", displayWidth(), displayHeight());
  screen->colors(1 << 4, {&PPU::color, this});
  screen->setSize(displayWidth(), displayHeight());
  screen->setScale(1.0, 1.0);
  screen->setAspect(8.0, 7.0);
  screen->refreshRateHint(system.frequency(), cyclesPerLine(), vlines());
}

auto PPU::unload() -> void {
  screen->quit();
  node->remove(screen);
  screen.reset();
  node.reset();
}

auto PPU::main() -> void {
  for(auto _ : range(vlines())) {
    scanline();
  }
  frame();
}

auto PPU::step(u32 clocks) -> void {
  while(clocks--) {
    Thread::step(1);
    Thread::synchronize(cpu);
  }
}

auto PPU::scanline() -> void {
  step(cyclesPerLine());
}

auto PPU::frame() -> void {
  if(screen->overscan()) {
    screen->setSize(displayWidth(), displayHeight());
    screen->setViewport(0, 0, displayWidth(), displayHeight());
  } else {
    int x = hOverscan() / 2;
    int y = vOverscan() / 2;
    int width = displayWidth() - hOverscan();
    int height = displayHeight() - vOverscan();

    screen->setSize(width, height);
    screen->setViewport(x, y, width, height);
  }

  screen->frame();
  scheduler.exit(Event::Frame);
}

auto PPU::power() -> void {
  Thread::create(system.frequency(), {&PPU::main, this});
}

}
