#define BA ba.word
#define HL hl.word
#define IP ip.word

#define A  ba.byte.lo
#define B  ba.byte.hi
#define L  hl.byte.lo
#define H  hl.byte.hi
#define YP ip.byte.lo
#define XP ip.byte.hi

#define ZF  SC.bit(0)
#define CF  SC.bit(1)
#define VF  SC.bit(2)
#define NF  SC.bit(3)
#define DF  SC.bit(4)
#define UF  SC.bit(5)
#define IF0 SC.bit(6)
#define IF1 SC.bit(7)

#define F0 CC.bit(0)
#define F1 CC.bit(1)
#define F2 CC.bit(2)
#define F3 CC.bit(3)
