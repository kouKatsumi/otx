/*
	X86Processor.h
*/

#import "ExeProcessor.h"

// Addressing modes in mod field of mod r/m byte.
// See table 2.2 in the Pentium manual.
#define MODimm	0	// [reg]
#define MOD8	1	// [reg] + disp8
#define MOD32	2	// [reg] + disp32
#define MODx	3	// ignored

// Addressing modes in r/m field of mod r/m byte.
// See table 2.2 in the Pentium manual.
#define DISP32	5	// disp32 when mod == 0

// Register identifiers in r/m field of mod r/m byte
enum {
	NOREG	= -1,
	EAX,	// 0
	ECX,	// 1
	EDX,	// 2
	EBX,	// 3
	ESP,	// 4
	EBP,	// 5
	ESI,	// 6
	EDI		// 7
};

// Macros for various ugly x86 data
#define LO(x)			((x) & 0xf)				// bits 0-3
#define HI(x)			(((x) >> 4) & 0xf)		// bits 4-7
//#define DIR(x)			(((x) >> 1) & 0x1)		// bit 1
#define MOD(x)			(((x) >> 6) & 0x3)		// bits 6-7
#define REG1(x)			(((x) >> 3) & 0x7)		// bits 3-5
#define REG2(x)			((x) & 0x7)				// bits 0-2
#define OPEXT(x)		REG1((x))
#define RM(x)			REG2((x))
#define HAS_SIB(x)		(MOD((x)) != MODx && REG2((x)) == ESP)
#define HAS_DISP8(x)	(MOD((x)) == MOD8)
#define HAS_DISP32(x)	(MOD((x)) == MOD32)

#define IS_JUMP(o)								\
	(((o) >= 0x71 && (o) <= 0x7f) ||			\
	(o) == 0xe3 || (o) == 0xe9 || (o) == 0xeb)

// ============================================================================

@interface X86Processor : ExeProcessor
{
	RegisterInfo	mRegInfos[8];
}

@end
