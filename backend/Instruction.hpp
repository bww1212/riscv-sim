#ifndef __INSTRUCTION_HPP
#define __INSTRUCTION_HPP

#include "Includes.hpp"

#define OP_ALU_R 0b0110011
#define OP_ALU_I 0b0010011
#define OP_LOAD 0b0000011
#define OP_STORE 0b0100011
#define OP_BRANCH 0b1100011
#define OP_JUMP_LINK 0b1101111
#define OP_JUMP_LINK_REG 0b1100111
#define OP_LOAD_UPPER 0b0110111
#define OP_ADD_UPPER 0b0010111
#define OP_ENV 0b1110011

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
    inline uint32_t uimm() {
    	return imm11_0;
    }
    inline int32_t imm() {
        return SIGN_EXTEND_32BIT(12, imm11_0);
    }
    inline int32_t imm11_5() {
    	return imm11_0 >> 5;
    }
    inline int32_t imm4_0() {
    	return imm11_0 & 0b11111;
    }
} IInstruction;

typedef struct SInstruction {
    uint opcode: 7;
    uint imm4_0: 5;
    uint funct3: 3;
    uint rs1: 5;
    uint rs2: 5;
    uint imm11_5: 7;
    inline uint32_t uimm() {
    	return (imm11_5 << 5) | imm4_0;
    }
    inline int32_t imm() {
        return SIGN_EXTEND_32BIT(12, uimm());
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
    inline uint32_t uimm() {
    	return (imm12 << 12) | (imm11 << 11) | (imm10_5 << 5) | (imm4_1 << 1);
    }
    inline int32_t imm() {
        return SIGN_EXTEND_32BIT(13, uimm());
    }
} BInstruction;

typedef struct UInstruction {
    uint opcode: 7;
    uint rd: 5;
    uint imm31_12: 20;
    inline uint32_t uimm() {
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
        return SIGN_EXTEND_32BIT(21, uimm());
    }
    inline uint32_t uimm() {
    	return (imm20 << 20) | (imm19_12 << 12) | (imm11 << 11) | (imm10_1 << 1);
    }
} JInstruction;

typedef union Instruction {
    Instruction(uint32_t bits) : raw(bits) {}
    uint32_t raw;
    uint opcode: 7;
	RInstruction r;
	IInstruction i;
	SInstruction s;
	BInstruction b;
	UInstruction u;
	JInstruction j;
} Instruction;

std::string instructionString(uint32_t word);

#endif
