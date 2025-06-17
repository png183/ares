#pragma once

//Seiko S1C88

namespace ares {

struct S1C88 {
  //s1c88.cpp
  auto power() -> void;

  //memory.cpp
  virtual auto read(n24 address) -> n8 = 0;
  virtual auto write(n24 address, n8 data) -> void = 0;
  auto pop() -> n8;
  auto pop16() -> n16;
  auto push(n8 data) -> void;
  auto push16(n16 data) -> void;
  auto fetch() -> n8;
  auto fetch16() -> n16;
  auto read16(n24 address) -> n16;
  auto write16(n24 address, n16 data) -> void;

  //algorithms.cpp
  auto AND(n8 x, n8 y) -> n8;
  auto DEC(n8 x) -> n8;
  auto DEC16(n16 x) -> n16;
  auto INC(n8 x) -> n8;
  auto INC16(n16 x) -> n16;
  auto OR(n8 x, n8 y) -> n8;
  auto SLL(n8 x) -> n8;
  auto SRA(n8 x) -> n8;
  auto XOR(n8 x, n8 y) -> n8;

  //instruction.cpp
  auto instruction() -> void;
  auto instruction(n8 opcode) -> void;
  auto instructionCE(n8 opcode) -> void;
  auto instructionCF(n8 opcode) -> void;

  //instructions.cpp
  auto instructionAND_r_n(n8& dst) -> void;
  auto instructionAND_ir_n(n8& base) -> void;
  auto instructionBIT_r_n(n8& dst) -> void;
  auto instructionCARL() -> void;
  auto instructionDEC_r(n8& dst) -> void;
  auto instructionDEC_rr(n16& dst) -> void;
  auto instructionDJR() -> void;
  auto instructionEX_r_r(n8& dst, n8& src) -> void;
  auto instructionINC_irr(n16& index, n8& page) -> void;
  auto instructionINC_r(n8& dst) -> void;
  auto instructionINC_rr(n16& dst) -> void;
  auto instructionJRL_c_nn(bool cond) -> void;
  auto instructionJRS_c_n(bool cond) -> void;
  auto instructionLD_inn_r(n8& src) -> void;
  auto instructionLD_inn_rr(n16& src) -> void;
  auto instructionLD_ir_n(n8& base) -> void;
  auto instructionLD_ir_r(n8& base, n8& src) -> void;
  auto instructionLD_irr_irr(n16& dindex, n8& dpage, n16& sindex, n8& spage) -> void;
  auto instructionLD_irr_n(n16& index, n8& page) -> void;
  auto instructionLD_irr_r(n16& index, n8& page, n8& src) -> void;
  auto instructionLD_irr_rr(n16& index, n8& page, n16& src) -> void;
  auto instructionLD_r_irr(n8& dst, n16& index, n8& page) -> void;
  auto instructionLD_r_inn(n8& dst) -> void;
  auto instructionLD_r_n(n8& dst) -> void;
  auto instructionLD_r_r(n8& dst, n8& src) -> void;
  auto instructionLD_rr_inn(n16& dst) -> void;
  auto instructionLD_rr_irr(n16& dst, n16& index, n8& page) -> void;
  auto instructionLD_rr_nn(n16& dst) -> void;
  auto instructionLD_rr_rr(n16& dst, n16& src) -> void;
  auto instructionOR_ir_n(n8& base) -> void;
  auto instructionPOP_r(n8& dst) -> void;
  auto instructionPOP_rr(n16& dst) -> void;
  auto instructionPUSH_all() -> void;
  auto instructionPUSH_r(n8& src) -> void;
  auto instructionPUSH_rr(n16& src) -> void;
  auto instructionRET() -> void;
  auto instructionSLL_r(n8& dst) -> void;
  auto instructionSRA_r(n8& dst) -> void;
  auto instructionXOR_r_r(n8& dst, n8& src) -> void;

  //disassembler.cpp
  auto disassembleFetch(n16 address) -> n8;
  auto disassembleInstruction() -> string;
  auto disassembleContext() -> string;
  auto disassembleInstruction(n8 opcode) -> string;
  auto disassembleInstructionCE(n8 opcode) -> string;
  auto disassembleInstructionCF(n8 opcode) -> string;

  //registers.hpp
  union Pair {
    Pair() : word(0) {}
    n16 word;
    struct Byte { n8 order_msb2(hi, lo); } byte;
  };

  Pair ba;  //data register
  Pair hl;  //index and data register
  Pair ip;  //expand page registers
  n16  IX;  //index register
  n16  IY;  //index register
  n16  PC;  //program counter
  n16  SP;  //stack pointer
  n8   BR;  //base register
  n8   SC;  //system condition flag register
  n8   NB;  //new code bank register
  n8   CB;  //code bank register
  n8   EP;  //expand page register

  //todo: remove once the processor is running properly
  bool running = true;
};

}
