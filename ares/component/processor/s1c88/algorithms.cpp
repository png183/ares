auto S1C88::AND(n8 x, n8 y) -> n8 {
  n8 z = x & y;
  ZF = z == 0;
  NF = z.bit(7);
  return z;
}

auto S1C88::DEC(n8 x) -> n8 {
  x--;
  ZF = x == 0;
  return x;
}

auto S1C88::DEC16(n16 x) -> n16 {
  x--;
  ZF = x == 0;
  return x;
}

auto S1C88::INC(n8 x) -> n8 {
  x++;
  ZF = x == 0;
  return x;
}

auto S1C88::INC16(n16 x) -> n16 {
  x++;
  ZF = x == 0;
  return x;
}

auto S1C88::OR(n8 x, n8 y) -> n8 {
  n8 z = x | y;
  ZF = z == 0;
  NF = z.bit(7);
  return z;
}

auto S1C88::SLL(n8 x) -> n8 {
  CF = x.bit(7);
  x <<= 1;
  ZF = x == 0;
  NF = x.bit(7);
  return x;
}

auto S1C88::SRA(n8 x) -> n8 {
  CF = x.bit(0);
  x = (i8)x >> 1;
  ZF = x == 0;
  VF = 0;
  NF = x.bit(7);
  return x;
}

auto S1C88::XOR(n8 x, n8 y) -> n8 {
  n8 z = x ^ y;
  ZF = z == 0;
  NF = z.bit(7);
  return z;
}
