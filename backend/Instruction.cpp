#include "Instruction.hpp"

#include "CPU.hpp"
#include <string>
#include <regex>
#include <map>

const std::string INST_NAME_FORMAT = "INST\t";
const std::string R_INSTR_FORMAT = "RD, RS1, RS2";
const std::string I_INSTR_FORMAT = "RD, RS1, IMM";
const std::string LOAD_INSTR_FORMAT = "RD, IMM(RS1)";
const std::string STORE_INSTR_FORMAT = "RS2, IMM(RS1)";
const std::string BRANCH_INSTR_FORMAT = "RS1, RS2, IMM";
const std::string JAL_INSTR_FORMAT = "RD, IMM";
const std::string U_INSTR_FORMAT = "RD, IMM";

std::map<uint8_t, std::map<uint8_t, std::string>> INSTRUCTION_NAME_MAP = {
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

void replaceField(std::string& str, char* field, std::string rep) {
    str = std::regex_replace(str, std::regex(field), rep);
}

std::string instructionString(uint32_t word) {
    Instruction instr(word);
    std::string instrName;
    std::string instrFormat = INST_NAME_FORMAT;
    auto replaceField = [&instrFormat](const char* field, std::string rep) {
        instrFormat = std::regex_replace(instrFormat, std::regex(field), rep);
    };
    switch (instr.opcode) {
        case OP_ALU_R:
            instrFormat += R_INSTR_FORMAT;
            instrName = INSTRUCTION_NAME_MAP[OP_ALU_R][instr.r.funct3 | instr.r.funct7];
            replaceField("RD", CPU::registerName(instr.r.rd));
            replaceField("RS1", CPU::registerName(instr.r.rs1));
            replaceField("RS2", CPU::registerName(instr.r.rs2));
			break;
		case OP_ALU_I:
            instrFormat += I_INSTR_FORMAT;
            instrName = INSTRUCTION_NAME_MAP[OP_ALU_I][instr.i.funct3 != 5 ? instr.i.funct3 : instr.i.imm11_5() | instr.i.funct3];
            replaceField("RD", CPU::registerName(instr.i.rd));
            replaceField("RS1", CPU::registerName(instr.i.rs1));
            replaceField("IMM", std::to_string(instr.i.imm()));
			break;
		case OP_LOAD:
            instrFormat += LOAD_INSTR_FORMAT;
            instrName = INSTRUCTION_NAME_MAP[OP_LOAD][instr.i.funct3];
            replaceField("RD", CPU::registerName(instr.i.rd));
            replaceField("RS1", CPU::registerName(instr.i.rs1));
            replaceField("IMM", std::to_string(instr.i.imm()));
			break;
		case OP_STORE:
            instrFormat += STORE_INSTR_FORMAT;
            instrName = INSTRUCTION_NAME_MAP[OP_STORE][instr.s.funct3];
            replaceField("RS1", CPU::registerName(instr.s.rs1));
            replaceField("RS2", CPU::registerName(instr.s.rs2));
            replaceField("IMM", std::to_string(instr.s.imm()));
			break;
		case OP_BRANCH:
            instrFormat += BRANCH_INSTR_FORMAT;
            instrName = INSTRUCTION_NAME_MAP[OP_BRANCH][instr.b.funct3];
            replaceField("RS1", CPU::registerName(instr.b.rs1));
            replaceField("RS2", CPU::registerName(instr.b.rs2));
            replaceField("IMM", std::to_string(instr.b.imm()));
			break;
		case OP_JUMP_LINK:
            instrFormat += JAL_INSTR_FORMAT;
            instrName = INSTRUCTION_NAME_MAP[OP_JUMP_LINK][0];
            replaceField("RD", CPU::registerName(instr.j.rd));
            replaceField("IMM", std::to_string(instr.j.imm()));
			break;
		case OP_JUMP_LINK_REG:
            instrFormat += I_INSTR_FORMAT;
            instrName = INSTRUCTION_NAME_MAP[OP_JUMP_LINK_REG][0];
            replaceField("RD", CPU::registerName(instr.i.rd));
            replaceField("RS1", CPU::registerName(instr.i.rs1));
            replaceField("IMM", std::to_string(instr.i.imm()));
			break;
		case OP_LOAD_UPPER:
            instrFormat += U_INSTR_FORMAT;
            instrName = INSTRUCTION_NAME_MAP[OP_LOAD_UPPER][0];
            replaceField("RD", CPU::registerName(instr.u.rd));
            replaceField("IMM", std::to_string(instr.u.uimm()));
			break;
		case OP_ADD_UPPER:
            instrFormat += U_INSTR_FORMAT;
            instrName = INSTRUCTION_NAME_MAP[OP_ADD_UPPER][0];
            replaceField("RD", CPU::registerName(instr.u.rd));
            replaceField("IMM", std::to_string(instr.u.uimm()));
			break;
        default:
            return "";
    }
    replaceField("INST", instrName);
    return instrFormat;
}
