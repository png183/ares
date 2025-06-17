auto S1C88::disassembleFetch(n16 pc) -> n8 {
  n24 address = pc;
  if(pc.bit(15)) address |= CB << 15;
  return read(address);
}

auto S1C88::disassembleInstruction() -> string {
  n8 opcode = disassembleFetch(PC);
  string s;
  if(opcode == 0xce) {
    opcode = disassembleFetch(PC + 1);
    s.append(disassembleInstructionCE(opcode));
  } else if(opcode == 0xcf) {
    opcode = disassembleFetch(PC + 1);
    s.append(disassembleInstructionCF(opcode));
  } else {
    s.append(disassembleInstruction(opcode));
  }

  return pad(s, -20);
}


#define op(id, name, ...) case id: return {name, " ", vector<string>{__VA_ARGS__}.merge(",")};
//todo: macro-ify the strings used here
//todo: also make signed values display as such
//todo: also fix some immediate values having incorrect brackets
//todo: also modes that have an immediate after a BRn term are messed up here

auto S1C88::disassembleInstruction(n8 opcode) -> string {
  string n = {"[", hex(disassembleFetch(PC + 1), 2L), "]"};
  string nn = {"[", hex(disassembleFetch(PC + 1) | disassembleFetch(PC + 2) << 8, 4L), "]"};
  string BRn = {"[BR:", hex(disassembleFetch(PC + 1), 2L), "]"};
  switch(opcode) {
  op(0x22, "and", "A", n);
  op(0x38, "xor", "A", "A");
  op(0x39, "xor", "A," "B");
  op(0x40, "ld", "A", "A");
  op(0x41, "ld", "A", "B");
  op(0x42, "ld", "A", "L");
  op(0x43, "ld", "A", "H");
  op(0x45, "ld", "A", "[HL]");
  op(0x46, "ld", "A", "[IX]");
  op(0x47, "ld", "A", "[IY]");
  op(0x48, "ld", "B", "A");
  op(0x49, "ld", "B", "B");
  op(0x4a, "ld", "B", "L");
  op(0x4b, "ld", "B", "H");
  op(0x4d, "ld", "B", "[HL]");
  op(0x4e, "ld", "B", "[IX]");
  op(0x4f, "ld", "B", "[IY]");
  op(0x50, "ld", "L", "A");
  op(0x51, "ld", "L", "B");
  op(0x52, "ld", "L", "L");
  op(0x53, "ld", "L", "H");
  op(0x55, "ld", "L", "[HL]");
  op(0x56, "ld", "L", "[IX]");
  op(0x57, "ld", "L", "[IY]");
  op(0x58, "ld", "H", "A");
  op(0x59, "ld", "H", "B");
  op(0x5a, "ld", "H", "L");
  op(0x5b, "ld", "H", "H");
  op(0x5d, "ld", "H", "[HL]");
  op(0x5e, "ld", "H", "[IX]");
  op(0x5f, "ld", "H", "[IY]");
  op(0x60, "ld", "[IX]", "A");
  op(0x61, "ld", "[IX]", "B");
  op(0x62, "ld", "[IX]", "L");
  op(0x63, "ld", "[IX]", "H");
  op(0x68, "ld", "[HL]", "A");
  op(0x69, "ld", "[HL]", "B");
  op(0x6a, "ld", "[HL]", "L");
  op(0x6b, "ld", "[HL]", "H");
  op(0x70, "ld", "[IY]", "A");
  op(0x71, "ld", "[IY]", "B");
  op(0x72, "ld", "[IY]", "L");
  op(0x73, "ld", "[IY]", "H");
  op(0x75, "ld", "[IY]", "[HL]");
  op(0x76, "ld", "[IY]", "[IX]");
  op(0x77, "ld", "[IY]", "[IY]");
  op(0x78, "ld", BRn, "A");
  op(0x79, "ld", BRn, "B");
  op(0x7a, "ld", BRn, "L");
  op(0x7b, "ld", BRn, "H");
  op(0x80, "inc", "A");
  op(0x81, "inc", "B");
  op(0x82, "inc", "L");
  op(0x83, "inc", "H");
  op(0x84, "inc", "BR");
  op(0x86, "inc", "[HL]");
  op(0x87, "inc", "SP");
  op(0x90, "inc", "BA");
  op(0x91, "inc", "HL");
  op(0x92, "inc", "IX");
  op(0x93, "inc", "IY");
  op(0x96, "bit", "A", n);
  op(0x97, "bit", "B", n);
  op(0x98, "dec", "BA");
  op(0x99, "dec", "HL");
  op(0x9a, "dec", "IX");
  op(0x9b, "dec", "IY");
  op(0x9c, "and", "SC", n);
  op(0x9f, "ld", "SC", n);
  op(0xa0, "push", "BA");
  op(0xa1, "push", "HL");
  op(0xa2, "push", "IX");
  op(0xa3, "push", "IY");
  op(0xa4, "push", "BR");
  op(0xa5, "push", "EP");
  op(0xa6, "push", "IP");
  op(0xa7, "push", "SC");
  op(0xa8, "pop", "BA");
  op(0xa9, "pop", "HL");
  op(0xaa, "pop", "IX");
  op(0xab, "pop", "IY");
  op(0xac, "pop", "BR");
  op(0xad, "pop", "EP");
  op(0xae, "pop", "IP");
  op(0xaf, "pop", "SC");
  op(0xb0, "ld", "A", n);
  op(0xb1, "ld", "B", n);
  op(0xb2, "ld", "L", n);
  op(0xb3, "ld", "H", n);
  op(0xb4, "ld", "BR", n);
  op(0xb5, "ld", "[HL]", n);
  op(0xb6, "ld", "[IX]", n);
  op(0xb7, "ld", "[IY]", n);
  op(0xb8, "ld", "BA", nn);
  op(0xb9, "ld", "HL", nn);
  op(0xba, "ld", "IX", nn);
  op(0xbb, "ld", "IY", nn);
  op(0xbc, "ld", nn, "BA");
  op(0xbd, "ld", nn, "HL");
  op(0xbe, "ld", nn, "IX");
  op(0xbf, "ld", nn, "IY");
  op(0xc4, "ld", "BA", nn);
  op(0xc5, "ld", "HL", nn);
  op(0xc6, "ld", "IX", nn);
  op(0xc7, "ld", "IY", nn);
  op(0xcc, "ex", "A", "B");
  op(0xd8, "and", BRn, n);
  op(0xd9, "or", BRn, n);
  op(0xdd, "ld", BRn, n);
  op(0xe4, "jrs", "C", n);
  op(0xe5, "jrs", "NC", n);
  op(0xe6, "jrs", "Z", n);
  op(0xe7, "jrs", "NZ", n);
  op(0xec, "jrl", "C", nn);
  op(0xed, "jrl", "NC", nn);
  op(0xee, "jrl", "Z", nn);
  op(0xef, "jrl", "NZ", nn);
  op(0xf1, "jrs", n);
  op(0xf2, "carl", nn);
  op(0xf3, "jrl", nn);
  op(0xf5, "djr", "NZ", n);
  op(0xf8, "ret");
  default: running = false; return { hex(opcode, 2L), " (UNKNOWN) "};
  }
  unreachable;
}

auto S1C88::disassembleInstructionCE(n8 opcode) -> string {
  string n = {"[", hex(disassembleFetch(PC + 2), 2L), "]"};
  string nn = {"[", hex(disassembleFetch(PC + 2) | disassembleFetch(PC + 3) << 8, 4L), "]"};
  string BRn = {"[BR:", hex(disassembleFetch(PC + 2), 2L), "]"};
  switch(opcode) {
  op(0x84, "sll", "A");
  op(0x85, "sll", "B");
  op(0x88, "sra", "A");
  op(0x89, "sra", "B");
  op(0xb0, "and", "B", n);
  op(0xb1, "and", "L", n);
  op(0xb2, "and", "H", n);
  op(0xc0, "ld", "A", "BR");
  op(0xc1, "ld", "A", "SC");
  op(0xc2, "ld", "BR", "A");
  op(0xc3, "ld", "SC", "A");
  op(0xc4, "ld", "NB", n);
  op(0xc5, "ld", "EP", n);
  op(0xc6, "ld", "XP", n);
  op(0xc7, "ld", "YP", n);
  op(0xc8, "ld", "A", "NB");
  op(0xc9, "ld", "A", "EP");
  op(0xca, "ld", "A", "XP");
  op(0xcb, "ld", "A", "YP");
  op(0xcc, "ld", "NB", "A");
  op(0xcd, "ld", "EP", "A");
  op(0xce, "ld", "XP", "A");
  op(0xcf, "ld", "YP", "A");
  op(0xd0, "ld", "A", nn);
  op(0xd1, "ld", "B", nn);
  op(0xd2, "ld", "L", nn);
  op(0xd3, "ld", "H", nn);
  op(0xd4, "ld", nn, "A");
  op(0xd5, "ld", nn, "B");
  op(0xd6, "ld", nn, "H");
  op(0xd7, "ld", nn, "L");
  default: running = false; return { hex(0xce, 2L), " ", hex(opcode, 2L), " (UNKNOWN) "};
  }
  unreachable;
}

auto S1C88::disassembleInstructionCF(n8 opcode) -> string {
  string n = {"[", hex(disassembleFetch(PC + 2), 2L), "]"};
  string nn = {"[", hex(disassembleFetch(PC + 2) | disassembleFetch(PC + 3) << 8, 4L), "]"};
  string BRn = {"[BR:", hex(disassembleFetch(PC + 2), 2L), "]"};
  switch(opcode) {
  op(0x6e, "ld", "SP", nn);
  op(0xb0, "push", "A");
  op(0xb1, "push", "B");
  op(0xb2, "push", "L");
  op(0xb3, "push", "H");
  op(0xb4, "pop", "A");
  op(0xb5, "pop", "B");
  op(0xb6, "pop", "L");
  op(0xb7, "pop", "H");
  op(0xb8, "push", "all");
  op(0xc0, "ld", "[BA]", "[HL]");
  op(0xc1, "ld", "[HL]", "[HL]");
  op(0xc2, "ld", "[IX]", "[HL]");
  op(0xc3, "ld", "[IY]", "[HL]");
  op(0xc4, "ld", "[HL]", "BA");
  op(0xc5, "ld", "[HL]", "HL");
  op(0xc6, "ld", "[HL]", "IX");
  op(0xc7, "ld", "[HL]", "IY");
  op(0xd0, "ld", "[BA]", "[IX]");
  op(0xd1, "ld", "[HL]", "[IX]");
  op(0xd2, "ld", "[IX]", "[IX]");
  op(0xd3, "ld", "[IY]", "[IX]");
  op(0xd4, "ld", "[IX]", "BA");
  op(0xd5, "ld", "[IX]", "HL");
  op(0xd6, "ld", "[IX]", "IX");
  op(0xd7, "ld", "[IX]", "IY");
  op(0xd8, "ld", "[BA]", "[IY]");
  op(0xd9, "ld", "[HL]", "[IY]");
  op(0xda, "ld", "[IX]", "[IY]");
  op(0xdb, "ld", "[IY]", "[IY]");
  op(0xdc, "ld", "[IY]", "BA");
  op(0xdd, "ld", "[IY]", "HL");
  op(0xde, "ld", "[IY]", "IX");
  op(0xdf, "ld", "[IY]", "IY");
  op(0xe0, "ld", "BA", "BA");
  op(0xe1, "ld", "BA", "HL");
  op(0xe2, "ld", "BA", "IX");
  op(0xe3, "ld", "BA", "IY");
  op(0xe4, "ld", "HL", "BA");
  op(0xe5, "ld", "HL", "HL");
  op(0xe6, "ld", "HL", "IX");
  op(0xe7, "ld", "HL", "IY");
  op(0xe8, "ld", "IX", "BA");
  op(0xe9, "ld", "IX", "HL");
  op(0xea, "ld", "IX", "IX");
  op(0xeb, "ld", "IX", "IY");
  op(0xec, "ld", "IY", "BA");
  op(0xed, "ld", "IY", "HL");
  op(0xee, "ld", "IY", "IX");
  op(0xef, "ld", "IY", "IY");
  op(0xf0, "ld", "SP", "BA");
  op(0xf1, "ld", "SP", "HL");
  op(0xf2, "ld", "SP", "IX");
  op(0xf3, "ld", "SP", "IY");
  op(0xf4, "ld", "HL", "SP");
  op(0xf5, "ld", "HL", "PC");
  op(0xf8, "ld", "BA", "SP");
  op(0xf9, "ld", "SP", "PC");
  op(0xfa, "ld", "IX", "SP");
  op(0xfe, "ld", "IY", "SP");
  default: running = false; return { hex(0xcf, 2L), " ", hex(opcode, 2L), " (UNKNOWN) "};
  }
  unreachable;
}

#undef op

auto S1C88::disassembleContext() -> string {
  string s0;
  s0.append("BA:", hex(BA, 4L), " ");
  s0.append("HL:", hex(HL, 4L), " ");
  s0.append("IX:", hex(IX, 4L), " ");
  s0.append("IY:", hex(IY, 4L), " ");
  s0.append("PC:", hex(PC, 4L), " ");
  s0.append("SP:", hex(SP, 4L), " ");
  s0.append("BR:", hex(BR, 2L), " ");
  s0.append("SC:", hex(SC, 2L), " ");

  string s1;
  s1 = pad("", -20);
  s1.append("NB:", hex(NB, 2L), " ");
  s1.append("CB:", hex(CB, 2L), " ");
  s1.append("EP:", hex(EP, 2L), " ");
  s1.append("XP:", hex(XP, 2L), " ");
  s1.append("YP:", hex(YP, 2L), " ");

  return {s0, "\n", s1};
}
