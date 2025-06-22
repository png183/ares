auto S1C88::instructionADD_r_n(n8& dst) -> void {
  dst = ADD(dst, fetch());
}

auto S1C88::instructionADD_r_r(n8& dst, n8& src) -> void {
  dst = ADD(dst, src);
}

auto S1C88::instructionADD_rr_nn(n16& dst) -> void {
  dst = ADD16(dst, fetch16());
}

auto S1C88::instructionADD_rr_rr(n16& dst, n16& src) -> void {
  dst = ADD16(dst, src);
}

auto S1C88::instructionAND_r_n(n8& dst) -> void {
  dst = AND(dst, fetch());
}

auto S1C88::instructionAND_ir_n() -> void {
  n24 address = EP << 16 | BR << 8 | fetch();
  n8 x = read(address);
  n8 y = fetch();
  write(address, AND(x, y));
}

auto S1C88::instructionBIT_ir_n() -> void {
  n24 address = EP << 16 | BR << 8 | fetch();
  n8 x = read(address);
  n8 y = fetch();
  AND(x, y);
}

auto S1C88::instructionBIT_r_n(n8& dst) -> void {
  AND(dst, fetch());
}

auto S1C88::instructionCARL() -> void {
  s16 offset = fetch16();
  push(CB);
  push16(PC);
  PC += offset - 1;
  CB = NB;
}

auto S1C88::instructionCPL_r(n8& dst) -> void {
  dst = CPL(dst);
}

auto S1C88::instructionDEC_r(n8& dst) -> void {
  dst = DEC(dst);
}

auto S1C88::instructionDEC_rr(n16& dst) -> void {
  dst = DEC16(dst);
}

auto S1C88::instructionDJR() -> void {
  B = DEC(B);
  s8 offset = fetch();
  if(!ZF) {
    PC += offset - 1;
    CB = NB;
  } else {
    NB = CB;
  }
}

auto S1C88::instructionEX_r_r(n8& dst, n8& src) -> void {
  n8 tmp = dst;
  dst = src;
  src = tmp;
}

auto S1C88::instructionINC_irr(n16& index, n8& page) -> void {
  n24 address = page << 16 | index;
  n8 data = read(address);
  data = INC(data);
  write(address, data);
}

auto S1C88::instructionINC_r(n8& dst) -> void {
  dst = INC(dst);
}

auto S1C88::instructionINC_rr(n16& dst) -> void {
  dst = INC16(dst);
}

auto S1C88::instructionJRL_c_nn(bool cond) -> void {
  s16 offset = fetch16();
  if(cond) {
    PC += offset - 1;
    CB = NB;
  } else {
    NB = CB;
  }
}

auto S1C88::instructionJRS_c_n(bool cond) -> void {
  s8 offset = fetch();
  if(cond) {
    PC += offset - 1;
    CB = NB;
  } else {
    NB = CB;
  }
}

auto S1C88::instructionLD_inn_r(n8& src) -> void {
  n24 address = EP << 16 | fetch16();
  write(address, src);
}

auto S1C88::instructionLD_inn_rr(n16& src) -> void {
  n24 address = EP << 16 | fetch16();
  write16(address, src);
}

auto S1C88::instructionLD_ir_irr(n16& index, n8& page) -> void {
  n24 daddr = EP << 16 | BR << 8 | fetch();
  n24 saddr = page << 16 | index;
  write(daddr, read(saddr));
}

auto S1C88::instructionLD_ir_n() -> void {
  n24 address = EP << 16 | BR << 8 | fetch();
  write(address, fetch());
}

auto S1C88::instructionLD_ir_r(n8& src) -> void {
  n24 address = EP << 16 | BR << 8 | fetch();
  write(address, src);
}

auto S1C88::instructionLD_irr_irr(n16& dindex, n8& dpage, n16& sindex, n8& spage) -> void {
  n24 saddr = spage << 16 | sindex;
  n24 daddr = dpage << 16 | dindex;
  write(daddr, read(saddr));
}

auto S1C88::instructionLD_irr_n(n16& index, n8& page) -> void {
  n24 address = page << 16 | index;
  write(address, fetch());
}

auto S1C88::instructionLD_irr_r(n16& index, n8& page, n8& src) -> void {
  n24 address = page << 16 | index;
  write(address, src);
}

auto S1C88::instructionLD_irr_rr(n16& index, n8& page, n16& src) -> void {
  n24 address = page << 16 | index;
  write16(address, src);
}

auto S1C88::instructionLD_irrpr_r(n16& index, n8& page, n8& dst, n8& src) -> void {
  //todo: may have a page wrapping bug?
  s8 offset = dst;
  n24 address = page << 16 | (index + offset);
  write(address, src);
}

auto S1C88::instructionLD_r_ir(n8& dst) -> void {
  n24 address = EP << 16 | BR << 8 | fetch();
  dst = read(address);
}

auto S1C88::instructionLD_r_irr(n8& dst, n16& index, n8& page) -> void {
  n24 address = page << 16 | index;
  dst = read(address);
}

auto S1C88::instructionLD_r_irrpn(n8& dst, n16& index, n8& page) -> void {
  //todo: may have a page wrapping bug?
  s8 offset = fetch();
  n24 address = page << 16 | (index + offset);
  dst = read(address);
}

auto S1C88::instructionLD_r_irrpr(n8& dst, n16& index, n8& page, n8& src) -> void {
  //todo: may have a page wrapping bug?
  s8 offset = src;
  n24 address = page << 16 | (index + offset);
  dst = read(address);
}

auto S1C88::instructionLD_r_inn(n8& dst) -> void {
  n24 address = EP << 16 | fetch16();
  dst = read(address);
}

auto S1C88::instructionLD_r_n(n8& dst) -> void {
  dst = fetch();
}

auto S1C88::instructionLD_r_r(n8& dst, n8& src) -> void {
  dst = src;
}

auto S1C88::instructionLD_rr_inn(n16& dst) -> void {
  n24 address = EP << 16 | fetch16();
  dst = read16(address);
}

auto S1C88::instructionLD_rr_irr(n16& dst, n16& index, n8& page) -> void {
  n24 address = EP << 16 | index;
  dst = read16(address);
}

auto S1C88::instructionLD_rr_irrpn(n16& dst, n16& index, n8& page) -> void {
  //todo: may have a page wrapping bug?
  s8 offset = fetch();
  n24 address = page << 16 | (index + offset);
  dst = read16(address);
}

auto S1C88::instructionLD_rr_nn(n16& dst) -> void {
  dst = fetch16();
}

auto S1C88::instructionLD_rr_rr(n16& dst, n16& src) -> void {
  dst = src;
}

auto S1C88::instructionOR_irr_r(n16& index, n8& page, n8& src) -> void {
  n24 address = page << 16 | index;
  n8 dst = read(address);
  write(address, OR(dst, src));
}

auto S1C88::instructionOR_ir_n() -> void {
  n24 address = EP << 16 | BR << 8 | fetch();
  n8 x = read(address);
  n8 y = fetch();
  write(address, OR(x, y));
}

auto S1C88::instructionNOP() -> void {
  //no operation
}

auto S1C88::instructionPOP_all() -> void {
  BR = pop();
  IY = pop16();
  IX = pop16();
  HL = pop16();
  BA = pop16();
}

auto S1C88::instructionPOP_r(n8& dst) -> void {
  dst = pop();
}

auto S1C88::instructionPOP_rr(n16& dst) -> void {
  dst = pop16();
}

auto S1C88::instructionPUSH_all() -> void {
  push16(BA);
  push16(HL);
  push16(IX);
  push16(IY);
  push(BR);
}

auto S1C88::instructionPUSH_r(n8& src) -> void {
  push(src);
}

auto S1C88::instructionPUSH_rr(n16& src) -> void {
  push16(src);
}

auto S1C88::instructionRET() -> void {
  PC = pop16();
  CB = pop();
  NB = CB;
}

auto S1C88::instructionRL_r(n8& dst) -> void {
  dst = RL(dst);
}

auto S1C88::instructionRLC_r(n8& dst) -> void {
  dst = RLC(dst);
}

auto S1C88::instructionRRC_r(n8& dst) -> void {
  dst = RRC(dst);
}

auto S1C88::instructionSLL_r(n8& dst) -> void {
  dst = SLL(dst);
}

auto S1C88::instructionSRA_r(n8& dst) -> void {
  dst = SRA(dst);
}

auto S1C88::instructionSRL_r(n8& dst) -> void {
  dst = SRL(dst);
}

auto S1C88::instructionSUB_r_r(n8& dst, n8& src) -> void {
  dst = SUB(dst, src);
}

auto S1C88::instructionSUB_rr_nn(n16& dst) -> void {
  dst = SUB16(dst, fetch16());
}

auto S1C88::instructionSUB_rr_rr(n16& dst, n16& src) -> void {
  dst = SUB16(dst, src);
}

auto S1C88::instructionXOR_r_r(n8& dst, n8& src) -> void {
  dst = XOR(dst, src);
}
