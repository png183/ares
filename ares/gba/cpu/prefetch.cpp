auto CPU::prefetchSync(n32 address) -> void {
  if(address == prefetch.baseAddr) return;

  prefetch.baseAddr = address;
  prefetch.wait = _wait(Half | Nonsequential, prefetch.next());
  prefetch.buffer.flush();
}

auto CPU::prefetchStep(u32 clocks) -> void {
  step(clocks);
  if(!wait.prefetch || context.dmaActive) return;

  while(!prefetch.buffer.full() && clocks--) {
    if(--prefetch.wait) continue;
    prefetch.buffer.write(cartridge.read(Half, prefetch.next()));
    prefetch.wait = _wait(Half | Sequential, prefetch.next());
  }
}

auto CPU::prefetchWait() -> void {
  if(!wait.prefetch || context.dmaActive || prefetch.buffer.full()) return;

  prefetchStep(prefetch.wait);
  prefetch.wait = _wait(Half | Nonsequential, prefetch.next());
}

auto CPU::prefetchRead() -> n16 {
  if(prefetch.buffer.empty()) prefetchStep(prefetch.wait);
  else prefetchStep(1);

  if(prefetch.buffer.full()) prefetch.wait = _wait(Half | Sequential, prefetch.next());

  n16 half = prefetch.buffer.read(0);
  prefetch.baseAddr += 2;
  return half;
}
