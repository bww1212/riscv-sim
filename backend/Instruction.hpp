#ifndef __INSTRUCTION_HPP
#define __INSTRUCTION_HPP

#include "Includes.hpp"

#define SIGN_EXTEND_32BIT(B, V) ((V >> (B - 1)) & 1) ? \
    (0xFFFFFFFF << B) | V : V

struct RInstruction {
    uint opcode: 7;
    uint rd: 5;
    uint funct3: 3;
    uint rs1: 5;
    uint rs2: 5;
    uint funct7: 7;
};

struct IInstruction {
    uint opcode: 7;
    uint rd: 5;
    uint funct3: 3;
    uint rs1: 5;
    uint imm11_0: 12;
    inline int32_t imm() {
        return SIGN_EXTEND_32BIT(12, imm11_0);
    }
};

struct SInstruction {
    uint opcode: 7;
    uint imm4_0: 5;
    uint funct3: 3;
    uint rs1: 5;
    uint rs2: 5;
    uint imm11_5: 7;
    inline int32_t imm() {
        return SIGN_EXTEND_32BIT(12, (imm11_5 << 5) | imm4_0);
    }
};

struct BInstruction {
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
};

struct UInstruction {
    uint opcode: 7;
    uint rd: 5;
    uint imm31_12: 20;
    inline int32_t imm() {
        return imm31_12 << 12;
    }
};

struct JInstruction {
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
};

#endif