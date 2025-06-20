auto S1C88::pop() -> n8 {
  n24 address = SPP << 16 | SP;
  n8 data = read(address);
  SP++;
  return data;
}

auto S1C88::pop16() -> n16 {
  n16 data = pop();
  data |= pop() << 8;
  return data;
}

auto S1C88::push(n8 data) -> void {
  SP--;
  n24 address = SPP << 16 | SP;
  write(address, data);
}

auto S1C88::push16(n16 data) -> void {
  push(data >> 8);
  push(data);
}

auto S1C88::fetch() -> n8 {
  n24 address = (n15)PC;
  if(PC.bit(15)) address |= CB << 15;
  n8 byte = read(address);
  PC++;
  return byte;
}

auto S1C88::fetch16() -> n16 {
  n16 word = fetch();
  word |= fetch() << 8;
  return word;
}

auto S1C88::read16(n24 address) -> n16 {
  //todo: may have a page wrapping bug?
  n16 word = read(address);
  word |= read(address + 1) << 8;
  return word;
}

auto S1C88::write16(n24 address, n16 data) -> void {
  //todo: may have a page wrapping bug?
  write(address + 0, data);
  write(address + 1, data >> 8);
}
