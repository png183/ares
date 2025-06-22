auto S1C88::instruction() -> void {
  n8 opcode = fetch();
  if(opcode == 0xce) return instructionCE(fetch());
  if(opcode == 0xcf) return instructionCF(fetch());
  return instruction(opcode);
}

#define op(id, name, ...) case id: return instruction##name(__VA_ARGS__);

auto S1C88::instruction(n8 opcode) -> void {
  switch(opcode) {
  op(0x00, ADD_r_r, A, A);
  op(0x01, ADD_r_r, A, B);
  op(0x02, ADD_r_n, A);
  //todo: 03-0f
  op(0x10, SUB_r_r, A, A);
  op(0x11, SUB_r_r, A, B);
  op(0x12, SUB_r_n, A);
  //todo: 13-1f
  op(0x20, AND_r_r, A, A);
  op(0x21, AND_r_r, A, B);
  op(0x22, AND_r_n, A);
  op(0x23, AND_r_irr, A, HL, EP);
  //todo: 24-25
  op(0x26, AND_r_irr, A, IX, XP);
  op(0x27, AND_r_irr, A, IY, YP);
  op(0x28, OR_r_r, A, A);
  op(0x29, OR_r_r, A, B);
  op(0x2a, OR_r_n, A);
  //todo: 2b-2f
  op(0x30, CP_r_r, A, A);
  op(0x31, CP_r_r, A, B);
  op(0x32, CP_r_n, A);
  op(0x33, CP_r_irr, A, HL, EP);
  //todo: 34-35
  op(0x36, CP_r_irr, A, IX, XP);
  op(0x37, CP_r_irr, A, IY, YP);
  op(0x38, XOR_r_r, A, A);
  op(0x39, XOR_r_r, A, B);
  //todo: 3a-3f
  op(0x40, LD_r_r, A, A);
  op(0x41, LD_r_r, A, B);
  op(0x42, LD_r_r, A, L);
  op(0x43, LD_r_r, A, H);
  op(0x44, LD_r_ir, A);
  op(0x45, LD_r_irr, A, HL, EP);
  op(0x46, LD_r_irr, A, IX, XP);
  op(0x47, LD_r_irr, A, IY, YP);
  op(0x48, LD_r_r, B, A);
  op(0x49, LD_r_r, B, B);
  op(0x4a, LD_r_r, B, L);
  op(0x4b, LD_r_r, B, H);
  op(0x4c, LD_r_ir, B);
  op(0x4d, LD_r_irr, B, HL, EP);
  op(0x4e, LD_r_irr, B, IX, XP);
  op(0x4f, LD_r_irr, B, IY, YP);
  op(0x50, LD_r_r, L, A);
  op(0x51, LD_r_r, L, B);
  op(0x52, LD_r_r, L, L);
  op(0x53, LD_r_r, L, H);
  op(0x54, LD_r_ir, L);
  op(0x55, LD_r_irr, L, HL, EP);
  op(0x56, LD_r_irr, L, IX, XP);
  op(0x57, LD_r_irr, L, IY, YP);
  op(0x58, LD_r_r, H, A);
  op(0x59, LD_r_r, H, B);
  op(0x5a, LD_r_r, H, L);
  op(0x5b, LD_r_r, H, H);
  op(0x5c, LD_r_ir, H);
  op(0x5d, LD_r_irr, H, HL, EP);
  op(0x5e, LD_r_irr, H, IX, XP);
  op(0x5f, LD_r_irr, H, IY, YP);
  op(0x60, LD_irr_r, IX, XP, A);
  op(0x61, LD_irr_r, IX, XP, B);
  op(0x62, LD_irr_r, IX, XP, L);
  op(0x63, LD_irr_r, IX, XP, H);
  //todo: 64-67
  op(0x68, LD_irr_r, HL, EP, A);
  op(0x69, LD_irr_r, HL, EP, B);
  op(0x6a, LD_irr_r, HL, EP, L);
  op(0x6b, LD_irr_r, HL, EP, H);
  //todo: 6c-6f
  op(0x70, LD_irr_r, IY, YP, A);
  op(0x71, LD_irr_r, IY, YP, B);
  op(0x72, LD_irr_r, IY, YP, L);
  op(0x73, LD_irr_r, IY, YP, H);
  //todo: 74
  op(0x75, LD_irr_irr, IY, YP, HL, EP);
  op(0x76, LD_irr_irr, IY, YP, IX, XP);
  op(0x77, LD_irr_irr, IY, YP, IY, YP);
  op(0x78, LD_ir_r, A);
  op(0x79, LD_ir_r, B);
  op(0x7a, LD_ir_r, L);
  op(0x7b, LD_ir_r, H);
  //7c is UNDEFINED
  op(0x7d, LD_ir_irr, HL, EP);
  op(0x7e, LD_ir_irr, IX, YP);
  op(0x7f, LD_ir_irr, IY, YP);
  op(0x80, INC_r, A);
  op(0x81, INC_r, B);
  op(0x82, INC_r, L);
  op(0x83, INC_r, H);
  op(0x84, INC_r, BR);
  //todo: 85
  op(0x86, INC_irr, HL, EP);
  op(0x87, INC_rr, SP);
  op(0x88, DEC_r, A);
  op(0x89, DEC_r, B);
  op(0x8a, DEC_r, L);
  op(0x8b, DEC_r, H);
  op(0x8c, DEC_r, BR);
  //todo: 8d-8e
  op(0x8f, DEC_rr, SP);
  op(0x90, INC_rr, BA);
  op(0x91, INC_rr, HL);
  op(0x92, INC_rr, IX);
  op(0x93, INC_rr, IY);
  //todo: 94-95
  op(0x96, BIT_r_n, A);
  op(0x97, BIT_r_n, B);
  op(0x98, DEC_rr, BA);
  op(0x99, DEC_rr, HL);
  op(0x9a, DEC_rr, IX);
  op(0x9b, DEC_rr, IY);
  op(0x9c, AND_r_n, SC);
  op(0x9d, OR_r_n, SC);
  //todo: 9e
  op(0x9f, LD_r_n, SC);
  op(0xa0, PUSH_rr, BA);
  op(0xa1, PUSH_rr, HL);
  op(0xa2, PUSH_rr, IX);
  op(0xa3, PUSH_rr, IY);
  op(0xa4, PUSH_r, BR);
  op(0xa5, PUSH_r, EP);
  op(0xa6, PUSH_rr, IP);
  op(0xa7, PUSH_r, SC);
  op(0xa8, POP_rr, BA);
  op(0xa9, POP_rr, HL);
  op(0xaa, POP_rr, IX);
  op(0xab, POP_rr, IY);
  op(0xac, POP_r, BR);
  op(0xad, POP_r, EP);
  op(0xae, POP_rr, IP);
  op(0xaf, POP_r, SC);
  op(0xb0, LD_r_n, A);
  op(0xb1, LD_r_n, B);
  op(0xb2, LD_r_n, L);
  op(0xb3, LD_r_n, H);
  op(0xb4, LD_r_n, BR);
  op(0xb5, LD_irr_n, HL, EP);
  op(0xb6, LD_irr_n, IX, XP);
  op(0xb7, LD_irr_n, IY, YP);
  op(0xb8, LD_rr_inn, BA);
  op(0xb9, LD_rr_inn, HL);
  op(0xba, LD_rr_inn, IX);
  op(0xbb, LD_rr_inn, IY);
  op(0xbc, LD_inn_rr, BA);
  op(0xbd, LD_inn_rr, HL);
  op(0xbe, LD_inn_rr, IX);
  op(0xbf, LD_inn_rr, IY);
  op(0xc0, ADD_rr_nn, BA);
  op(0xc1, ADD_rr_nn, HL);
  op(0xc2, ADD_rr_nn, IX);
  op(0xc3, ADD_rr_nn, IY);
  op(0xc4, LD_rr_nn, BA);
  op(0xc5, LD_rr_nn, HL);
  op(0xc6, LD_rr_nn, IX);
  op(0xc7, LD_rr_nn, IY);
  //todo: c8-cb
  op(0xcc, EX_r_r, A, B);
  //todo: cd
  //ce and cf are prefixes
  op(0xd0, SUB_rr_nn, BA);
  op(0xd1, SUB_rr_nn, HL);
  op(0xd2, SUB_rr_nn, IX);
  op(0xd3, SUB_rr_nn, IY);
  op(0xd4, CP_rr_nn, BA);
  op(0xd5, CP_rr_nn, HL);
  op(0xd6, CP_rr_nn, IX);
  op(0xd7, CP_rr_nn, IY);
  op(0xd8, AND_ir_n);
  op(0xd9, OR_ir_n);
  //todo: da-dc
  op(0xdc, BIT_ir_n);
  op(0xdd, LD_ir_n);
  //todo: de-e3
  op(0xe4, JRS_c_n, CF == 1);
  op(0xe5, JRS_c_n, CF == 0);
  op(0xe6, JRS_c_n, ZF == 1);
  op(0xe7, JRS_c_n, ZF == 0);
  //todo: e8-eb
  op(0xec, JRL_c_nn, CF == 1);
  op(0xed, JRL_c_nn, CF == 0);
  op(0xee, JRL_c_nn, ZF == 1);
  op(0xef, JRL_c_nn, ZF == 0);
  //todo: f0
  op(0xf1, JRS_c_n, 1);
  op(0xf2, CARL);
  op(0xf3, JRL_c_nn, 1);
  //todo: f4
  op(0xf5, DJR);
  //todo: f6-f7
  op(0xf8, RET);
  //todo: f9-fd
  //fe is UNDEFINED
  op(0xff, NOP);
  default: running = false; return;  //todo: filter out?
  }
}

auto S1C88::instructionCE(n8 opcode) -> void {
  switch(opcode) {
  //todo: 00-2b
  op(0x2c, OR_irr_r, HL, EP, A);
  //todo: 2d-34
  op(0x35, CP_irr_n, HL, EP);
  //todo: 36-3f
  op(0x40, LD_r_irrpn, A, IX, XP);
  op(0x41, LD_r_irrpn, A, IY, YP);
  op(0x42, LD_r_irrpr, A, IX, XP, L);
  op(0x43, LD_r_irrpr, A, IY, XP, L);
  //todo: 44-45
  op(0x46, LD_irrpr_r, IX, XP, L, A);
  op(0x47, LD_irrpr_r, IY, YP, L, A);
  op(0x48, LD_r_irrpn, B, IX, XP);
  op(0x49, LD_r_irrpn, B, IY, YP);
  op(0x4a, LD_r_irrpr, B, IX, XP, L);
  op(0x4b, LD_r_irrpr, B, IY, XP, L);
  //todo: 4c-4d
  op(0x4e, LD_irrpr_r, IX, XP, L, B);
  op(0x4f, LD_irrpr_r, IY, YP, L, B);
  op(0x50, LD_r_irrpn, L, IX, XP);
  op(0x51, LD_r_irrpn, L, IY, YP);
  op(0x52, LD_r_irrpr, L, IX, XP, L);
  op(0x53, LD_r_irrpr, L, IY, XP, L);
  //todo: 54-55
  op(0x56, LD_irrpr_r, IX, XP, L, L);
  op(0x57, LD_irrpr_r, IY, YP, L, L);
  op(0x58, LD_r_irrpn, H, IX, XP);
  op(0x59, LD_r_irrpn, H, IY, YP);
  op(0x5a, LD_r_irrpr, H, IX, XP, L);
  op(0x5b, LD_r_irrpr, H, IY, XP, L);
  //todo: 5c-5d
  op(0x5e, LD_irrpr_r, IX, XP, L, H);
  op(0x5f, LD_irrpr_r, IY, YP, L, H);
  //todo: 60-83
  op(0x84, SLL_r, A);
  op(0x85, SLL_r, B);
  //todo: 86-87
  op(0x88, SRA_r, A);
  op(0x89, SRA_r, B);
  //todo: 8a-8b
  op(0x8c, SRL_r, A);
  op(0x8d, SRL_r, B);
  //todo: 8e-9f
  op(0x90, RL_r, A);
  op(0x91, RL_r, B);
  //todo: 92-93
  op(0x94, RLC_r, A);
  op(0x95, RLC_r, B);
  //todo: 96-9b
  op(0x9c, RRC_r, A);
  op(0x9d, RRC_r, B);
  //todo: 9e-9f
  op(0xa0, CPL_r, A);
  op(0xa1, CPL_r, B);
  //todo: a2-af
  op(0xb0, AND_r_n, B);
  op(0xb1, AND_r_n, L);
  op(0xb2, AND_r_n, H);
  //b3 is UNDEFINED
  op(0xb4, OR_r_n, B);
  op(0xb5, OR_r_n, L);
  op(0xb6, OR_r_n, H);
  //b7 is UNDEFINED
  //todo: b8-ba
  //bb is UNDEFINED
  op(0xbc, CP_r_n, B);
  op(0xbd, CP_r_n, L);
  op(0xbe, CP_r_n, H);
  op(0xbf, CP_r_n, BR);
  op(0xc0, LD_r_r, A, BR);
  op(0xc1, LD_r_r, A, SC);
  op(0xc2, LD_r_r, BR, A);
  op(0xc3, LD_r_r, SC, A);
  op(0xc4, LD_r_n, NB);
  op(0xc5, LD_r_n, EP);
  op(0xc6, LD_r_n, XP);
  op(0xc7, LD_r_n, YP);
  op(0xc8, LD_r_r, A, NB);
  op(0xc9, LD_r_r, A, EP);
  op(0xca, LD_r_r, A, XP);
  op(0xcb, LD_r_r, A, YP);
  op(0xcc, LD_r_r, NB, A);
  op(0xcd, LD_r_r, EP, A);
  op(0xce, LD_r_r, XP, A);
  op(0xcf, LD_r_r, YP, A);
  op(0xd0, LD_r_inn, A);
  op(0xd1, LD_r_inn, B);
  op(0xd2, LD_r_inn, L);
  op(0xd3, LD_r_inn, H);
  op(0xd4, LD_inn_r, A);
  op(0xd5, LD_inn_r, B);
  op(0xd6, LD_inn_r, L);
  op(0xd7, LD_inn_r, H);
  //todo: d8-ff
  default: running = false; return;  //todo: filter out?
  }
}

auto S1C88::instructionCF(n8 opcode) -> void {
  switch(opcode) {
  op(0x00, ADD_rr_rr, BA, BA);
  op(0x01, ADD_rr_rr, BA, HL);
  op(0x02, ADD_rr_rr, BA, IX);
  op(0x03, ADD_rr_rr, BA, IY);
  //todo: 04-07
  op(0x08, SUB_rr_rr, BA, BA);
  op(0x09, SUB_rr_rr, BA, HL);
  op(0x0a, SUB_rr_rr, BA, IX);
  op(0x0b, SUB_rr_rr, BA, IY);
  //todo: 0c-0f
  //10-17 is UNDEFINED
  op(0x18, CP_rr_rr, BA, BA);
  op(0x19, CP_rr_rr, BA, HL);
  op(0x1a, CP_rr_rr, BA, IX);
  op(0x1b, CP_rr_rr, BA, IY);
  //1c-1f is UNDEFINED
  op(0x20, ADD_rr_rr, HL, BA);
  op(0x21, ADD_rr_rr, HL, HL);
  op(0x22, ADD_rr_rr, HL, IX);
  op(0x23, ADD_rr_rr, HL, IY);
  //todo: 24-27
  op(0x28, SUB_rr_rr, HL, BA);
  op(0x29, SUB_rr_rr, HL, HL);
  op(0x2a, SUB_rr_rr, HL, IX);
  op(0x2b, SUB_rr_rr, HL, IY);
  //todo: 2c-2f
  //30-37 is UNDEFINED
  op(0x38, CP_rr_rr, HL, BA);
  op(0x39, CP_rr_rr, HL, HL);
  op(0x3a, CP_rr_rr, HL, IX);
  op(0x3b, CP_rr_rr, HL, IY);
  //3c-3f is UNDEFINED
  op(0x40, ADD_rr_rr, IX, BA);
  op(0x41, ADD_rr_rr, IX, HL);
  op(0x42, ADD_rr_rr, IY, BA);
  op(0x43, ADD_rr_rr, IY, HL);
  op(0x44, ADD_rr_rr, SP, BA);
  op(0x45, ADD_rr_rr, SP, HL);
  //46-47 is UNDEFINED
  op(0x48, SUB_rr_rr, IX, BA);
  op(0x49, SUB_rr_rr, IX, HL);
  op(0x4a, SUB_rr_rr, IY, BA);
  op(0x4b, SUB_rr_rr, IY, HL);
  op(0x4c, SUB_rr_rr, SP, BA);
  op(0x4d, SUB_rr_rr, SP, HL);
  //4e-5b is UNDEFINED
  op(0x5c, CP_rr_rr, SP, BA);
  op(0x5d, CP_rr_rr, SP, HL);
  //5e-5f is UNDEFINED
  //todo: 60-63
  //64-67 is UNDEFINED
  op(0x68, ADD_rr_nn, SP);
  //69 is UNDEFINED
  op(0x6a, SUB_rr_nn, SP);
  //6b is UNDEFINED
  op(0x6c, CP_rr_nn, SP);
  //6d is UNDEFINED
  op(0x6e, LD_rr_nn, SP);
  //6f is UNDEFINED
  op(0x70, LD_rr_irrpn, BA, SP, SPP);
  op(0x71, LD_rr_irrpn, HL, SP, SPP);
  op(0x72, LD_rr_irrpn, IX, SP, SPP);
  op(0x73, LD_rr_irrpn, IY, SP, SPP);
  //todo: 74-7c
  //7d-af is UNDEFINED
  op(0xb0, PUSH_r, A);
  op(0xb1, PUSH_r, B);
  op(0xb2, PUSH_r, L);
  op(0xb3, PUSH_r, H);
  op(0xb4, POP_r, A);
  op(0xb5, POP_r, B);
  op(0xb6, POP_r, L);
  op(0xb7, POP_r, H);
  op(0xb8, PUSH_all);
  op(0xb9, PUSH_ale);
  //ba-bb is UNDEFINED
  op(0xbc, POP_all);
  //todo: bd
  //be-bf is UNDEFINED
  op(0xc0, LD_rr_irr, BA, HL, EP);
  op(0xc1, LD_rr_irr, HL, HL, EP);
  op(0xc2, LD_rr_irr, IX, HL, EP);
  op(0xc3, LD_rr_irr, IY, HL, EP);
  op(0xc4, LD_irr_rr, HL, EP, BA);
  op(0xc5, LD_irr_rr, HL, EP, HL);
  op(0xc6, LD_irr_rr, HL, EP, IX);
  op(0xc7, LD_irr_rr, HL, EP, IY);
  //c8-cf is UNDEFINED
  op(0xd0, LD_rr_irr, BA, IX, XP);
  op(0xd1, LD_rr_irr, HL, IX, XP);
  op(0xd2, LD_rr_irr, IX, IX, XP);
  op(0xd3, LD_rr_irr, IY, IX, XP);
  op(0xd4, LD_irr_rr, IX, XP, BA);
  op(0xd5, LD_irr_rr, IX, XP, HL);
  op(0xd6, LD_irr_rr, IX, XP, IX);
  op(0xd7, LD_irr_rr, IX, XP, IY);
  op(0xd8, LD_rr_irr, BA, IY, YP);
  op(0xd9, LD_rr_irr, HL, IY, YP);
  op(0xda, LD_rr_irr, IX, IY, YP);
  op(0xdb, LD_rr_irr, IY, IY, YP);
  op(0xdc, LD_irr_rr, IY, YP, BA);
  op(0xdd, LD_irr_rr, IY, YP, HL);
  op(0xde, LD_irr_rr, IY, YP, IX);
  op(0xdf, LD_irr_rr, IY, YP, IY);
  op(0xe0, LD_rr_rr, BA, BA);
  op(0xe1, LD_rr_rr, BA, HL);
  op(0xe2, LD_rr_rr, BA, IX);
  op(0xe3, LD_rr_rr, BA, IY);
  op(0xe4, LD_rr_rr, HL, BA);
  op(0xe5, LD_rr_rr, HL, HL);
  op(0xe6, LD_rr_rr, HL, IX);
  op(0xe7, LD_rr_rr, HL, IY);
  op(0xe8, LD_rr_rr, IX, BA);
  op(0xe9, LD_rr_rr, IX, HL);
  op(0xea, LD_rr_rr, IX, IX);
  op(0xeb, LD_rr_rr, IX, IY);
  op(0xec, LD_rr_rr, IY, BA);
  op(0xed, LD_rr_rr, IY, HL);
  op(0xee, LD_rr_rr, IY, IX);
  op(0xef, LD_rr_rr, IY, IY);
  op(0xf0, LD_rr_rr, SP, BA);
  op(0xf1, LD_rr_rr, SP, HL);
  op(0xf2, LD_rr_rr, SP, IX);
  op(0xf3, LD_rr_rr, SP, IY);
  op(0xf4, LD_rr_rr, HL, SP);
  op(0xf5, LD_rr_rr, HL, PC);
  //f6-f7 is UNDEFINED
  op(0xf8, LD_rr_rr, BA, SP);
  op(0xf9, LD_rr_rr, SP, PC);
  op(0xfa, LD_rr_rr, IX, SP);
  //fb-fd is UNDEFINED
  op(0xfe, LD_rr_rr, IY, SP);
  //ff is UNDEFINED
  default: running = false; return;  //todo: filter out?
  }
}

#undef op
