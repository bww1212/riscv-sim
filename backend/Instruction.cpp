#include "Instruction.hpp"

#include <string>
#include <map>

const std::string INST_NAME = "{INST}\t";
const std::string R_INSTR_FORMAT = "{RD}, {RS1}, {RS2}";
const std::string I_INSTR_FORMAT = "{RD}, {RS1}, {IMM}";
const std::string LOAD_INSTR_FORMAT = "{RD}, {IMM}({RS1})";
const std::string STORE_INSTR_FORMAT = "{RS2}, {IMM}({RS1})";
const std::string JAL_INSTR_FORMAT = "{RD}, {IMM}";

const std::string J_INSTR_FORMAT = "{INST}\t";

const std::map<uint8_t, std::map<uint8_t, std::string>> INSTRUCTION_NAME_MAP = {
    {
        OP_ALU_R,
        {
            {0x0 , "add"}, {0x20, "sub"}, {0x4, "xor"}, {0x6, "or"}, {0x7, "and"},
            {0x1, "sll"}, {0x5, "srl"}, {0x25, "sra"}, {0x2, "slt"}, {0x3, "sltu"}
        }
    },
    {
        OP_ALU_I,
        {
            {0x0, "addi"}, {0x4, "xori"}, {0x6, "ori"}, {0x7, "andi"}, {0x1, "slli"},
            {0x5, "slri"}, {0x25, "srai"}, {0x2, "slti"}, {0x3, "sltiu"}
        }

    },
    {
        OP_LOAD,
        {
            {0x0, "lb"}, {0x1, "lh"}, {0x2, "lw"}, {0x4, "lbu"}, {0x5, "lhu"}
        }
    },
    {
        OP_STORE,
        {
            {0x0, "sb"}, {0x1, "sh"}, {0x2, "sw"}
        }
    },
    {
        OP_BRANCH,
        {
            {0x0, "beq"}, {0x1, "bne"}, {0x4, "blt"}, {0x5, "bge"}, {0x6, "bltu"}, {0x7, "bgeu"}
        }
    },
    {
        OP_JUMP_LINK,
        {
            {0x0, "jal"}
        }
    },
    {
        OP_JUMP_LINK_REG,
        {
            {0x0, "jalr"}
        }
    },
    {
        OP_LOAD_UPPER,
        {
            {0x0, "lui"}
        }
    },
    {
        OP_ADD_UPPER,
        {
            {0x0, "auipc"}
        }
    }
};

std::string instructionString(uint32_t word) {
    Instruction instr(word);
    std::string instrFormat = INST_NAME;
    switch (instr.opcode) {
        case OP_ALU_R:
			break;
		case OP_ALU_I:
			break;
		case OP_LOAD:
			break;
		case OP_STORE:
			break;
		case OP_BRANCH:
			break;
		case OP_JUMP_LINK:
			break;
		case OP_JUMP_LINK_REG:
			break;
		case OP_LOAD_UPPER:
			break;
		case OP_ADD_UPPER:
			break;
		case OP_ENV:
			break;
    }
}
