#ifndef __INSTRUCTION_HPP
#define __INSTRUCTION_HPP

#include "Includes.hpp"

#define SIGN_EXTEND_32BIT(B, V) ((V >> (B - 1)) & 1) ? \
    (0xFFFFFFFF << B) | V : V

typedef struct RInstruction {
    uint opcode: 7;
    uint rd: 5;
    uint funct3: 3;
    uint rs1: 5;
    uint rs2: 5;
    uint funct7: 7;
} RInstruction;

typedef struct IInstruction {
    uint opcode: 7;
    uint rd: 5;
    uint funct3: 3;
    uint rs1: 5;
    uint imm11_0: 12;
    inline int32_t imm() {
        return SIGN_EXTEND_32BIT(12, imm11_0);
    }
} IInstruction;

typedef struct SInstruction {
    uint opcode: 7;
    uint imm4_0: 5;
    uint funct3: 3;
    uint rs1: 5;
    uint rs2: 5;
    uint imm11_5: 7;
    inline int32_t imm() {
        return SIGN_EXTEND_32BIT(12, (imm11_5 << 5) | imm4_0);
    }
} SInstruction;

typedef struct BInstruction {
    uint opcode: 7;
    uint imm11: 1;
    uint imm4_1: 4;
    uint funct3: 3;
    uint rs1: 5;
    uint rs2: 5;
    uint imm10_5: 6;
    uint imm12: 1;
    inline int32_t imm() {
        return SIGN_EXTEND_32BIT(13, 
            (imm12 << 12) | (imm11 << 11) | (imm10_5 << 5) | (imm4_1 << 1));
    }
} BInstruction;

typedef struct UInstruction {
    uint opcode: 7;
    uint rd: 5;
    uint imm31_12: 20;
    inline int32_t imm() {
        return imm31_12 << 12;
    }
} UInstruction;

typedef struct JInstruction {
    uint opcode: 7;
    uint rd: 5;
    uint imm19_12: 8;
    uint imm11: 1;
    uint imm10_1: 10;
    uint imm20: 1;
    inline int32_t imm() {
        return SIGN_EXTEND_32BIT(21,
            (imm20 << 20) | (imm19_12 << 12) | (imm11 << 11) | (imm10_1 << 1));
    }
} JInstruction;

typedef union Instruction {
	RInstruction r;
	IInstruction i;
	SInstruction s;
	BInstruction b;
	UInstruction u;
	JInstruction j;
} Instruction;

#endif
