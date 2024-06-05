auto CPU::read(n16 address) -> n8 {
  n8 byte = readBus(address);
  step(rate());
  return byte;
}

auto CPU::write(n16 address, n8 data) -> void {
  writeBus(address, data);
  step(rate());
}

auto CPU::lastCycle() -> void {
  io.interruptPending = (io.irqLine & !P.i) | io.nmiPending;
}

auto CPU::cancelNmi() -> void {
  io.interruptPending = io.irqLine & !P.i;
}

auto CPU::delayIrq() -> void {
  io.interruptPending = io.nmiPending;
}

auto CPU::irqPending() -> bool {
  return io.irqLine & !P.i;
}

auto CPU::nmi(n16& vector) -> void {
  if(io.nmiPending) {
    io.nmiPending = false;
    vector = 0xfffa;
  }
}

auto CPU::nmiLine(bool line) -> void {
  //edge-sensitive (0->1)
  if(!io.nmiLine && line) io.nmiPending = true;
  io.nmiLine = line;
}

auto CPU::irqLine(bool line) -> void {
  //level-sensitive
  io.irqLine = line;
}
