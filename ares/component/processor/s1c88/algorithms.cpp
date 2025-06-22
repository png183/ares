auto S1C88::ADD(n8 x, n8 y) -> n8 {
  n9 z = x + y;
  ZF = n8(z) == 0;
  CF = z.bit(8);
  VF = n8(~(x ^ y) & (x ^ z)).bit(7);
  NF = z.bit(7);
  return z;
}

auto S1C88::ADD16(n16 x, n16 y) -> n16 {
  n17 z = x + y;
  ZF = n16(z) == 0;
  CF = z.bit(16);
  VF = n16(~(x ^ y) & (x ^ z)).bit(15);
  NF = z.bit(15);
  return z;
}

auto S1C88::AND(n8 x, n8 y) -> n8 {
  n8 z = x & y;
  ZF = z == 0;
  NF = z.bit(7);
  return z;
}

auto S1C88::CPL(n8 x) -> n8 {
  x = ~x;
  ZF = x == 0;
  NF = x.bit(7);
  return x;
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

auto S1C88::MLT(n8 x, n8 y) -> n16 {
  n16 z = x * y;
  ZF = z == 0;
  CF = 0;
  VF = 0;
  NF = z.bit(7);
  return z;
}

auto S1C88::OR(n8 x, n8 y) -> n8 {
  n8 z = x | y;
  ZF = z == 0;
  NF = z.bit(7);
  return z;
}

auto S1C88::RL(n8 x) -> n8 {
  n1 oldCarry = CF;
  CF = x.bit(7);
  x <<= 1;
  x.bit(0) = oldCarry;
  ZF = x == 0;
  NF = x.bit(7);
  return x;
}

auto S1C88::RLC(n8 x) -> n8 {
  CF = x.bit(7);
  x <<= 1;
  x.bit(0) = CF;
  ZF = x == 0;
  NF = x.bit(7);
  return x;
}

auto S1C88::RRC(n8 x) -> n8 {
  CF = x.bit(0);
  x >>= 1;
  x.bit(7) = CF;
  ZF = x == 0;
  NF = x.bit(7);
  return x;
}

auto S1C88::SEP(n8 x) -> n16 {
  return (i8)x;
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

auto S1C88::SRL(n8 x) -> n8 {
  CF = x.bit(0);
  x = x >> 1;
  ZF = x == 0;
  NF = 0;
  return x;
}

auto S1C88::SUB(n8 x, n8 y) -> n8 {
  n9 z = x - y;
  ZF = n8(z) == 0;
  CF = z.bit(8);
  VF = n8((x ^ y) & (x ^ z)).bit(7);
  NF = z.bit(7);
  return z;
}

auto S1C88::SUB16(n16 x, n16 y) -> n16 {
  n17 z = x - y;
  ZF = n16(z) == 0;
  CF = z.bit(16);
  VF = n16((x ^ y) & (x ^ z)).bit(15);
  NF = z.bit(15);
  return z;
}

auto S1C88::XOR(n8 x, n8 y) -> n8 {
  n8 z = x ^ y;
  ZF = z == 0;
  NF = z.bit(7);
  return z;
}
