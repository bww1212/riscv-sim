#include "CPU.hpp"

#include <memory>
#include <cstring>

using namespace std;

const char* REGISTER_NAMES[] = {
    "ZERO", "RA", "SP", "GP", "TP", "T0", "T1", "T2",
    "S0/FP", "S1", "A0", "A1", "A2", "A3", "A4", "A5",
    "A6", "A7", "S2", "S3", "S4", "S5", "S6", "S7",
    "S8", "S9", "S10", "S11", "T3", "T4", "T5", "T6"
};

CPU::CPU() : pc(32), zero(registers[0]), ra(registers[1]), sp(registers[2]), gp(registers[3]),
    tp(registers[4]), t0(registers[5]), t1(registers[6]), t2(registers[7]), s0(registers[8]),
    fp(registers[8]), s1(registers[9]), a0(registers[10]), a1(registers[11]), a2(registers[12]),
    a3(registers[13]), a4(registers[14]), a5(registers[15]), a6(registers[16]), a7(registers[17]),
    s2(registers[18]), s3(registers[19]), s4(registers[20]), s5(registers[21]), s6(registers[22]),
    s7(registers[23]), s8(registers[24]), s9(registers[25]), s10(registers[26]), s11(registers[27]),
    t3(registers[28]), t4(registers[29]), t5(registers[30]), t6(registers[31]) {
    reset();
}

const uint8_t* CPU::memoryPointer(uint16_t address) {
	return memory + address;
}

uint8_t CPU::byteAtMemory(uint16_t address) {
	return memory[address];
}

uint16_t CPU::halfWordAtMemory(uint16_t address) {
	return *((uint16_t*) (memory + address));
}

uint32_t CPU::wordAtMemory(uint16_t address) {
	return *((uint32_t*) (memory + address));
}

uint32_t CPU::registerContents(uint8_t index) {
	return registers[index]();
}

uint32_t CPU::pcContents() {
	return pc();
}

void CPU::reset() {
    for (int i = 0; i < 32; i++)
        registers[i] = Register(32);
    pc = Register(32);
    memset(memory, 0, MEMSIZE);
}

void CPU::loadProgram(uint8_t* bytes, uint size) {
    reset();
    memcpy(memory, bytes, size);
}

uint32_t CPU::executeInstruction() {
	Instruction instr(wordAtMemory(pc()));
	pc.set(pc() + 4);
	switch (instr.opcode) {
		case OP_ALU_R:
			alu_r(instr.r);
			break;
		case OP_ALU_I:
			alu_i(instr.i);
			break;
		case OP_LOAD:
			load(instr.i);
			break;
		case OP_STORE:
			store(instr.s);
			break;
		case OP_BRANCH:
			branch(instr.b);
			break;
		case OP_JUMP_LINK:
			jump_link(instr.j);
			break;
		case OP_JUMP_LINK_REG:
			jump_link_reg(instr.i);
			break;
		case OP_LOAD_UPPER:
			load_upper(instr.u);
			break;
		case OP_ADD_UPPER:
			add_upper(instr.u);
			break;
		case OP_ENV:
			environ(instr.i);
			break;
		default:
			throw runtime_error("Invalid instruction");
	}
    return pc();
}

void CPU::alu_r(RInstruction i) {
	switch (i.funct3) {
		case 0x0:
			if (i.funct7 == 0)
				registers[i.rd].set(registers[i.rs1]() + registers[i.rs2]()); // ADD
			else if (i.funct7 == 0x20)
				registers[i.rd].set(registers[i.rs1]() - registers[i.rs2]()); // SUB
			else
				throw runtime_error("Instruction (ADD/SUB) has invalid funct7");
			break;
		case 0x4:
			registers[i.rd].set(registers[i.rs1]() ^ registers[i.rs2]()); // XOR
			break;
		case 0x6:
			registers[i.rd].set(registers[i.rs1]() | registers[i.rs2]()); // OR
			break;
		case 0x7:
			registers[i.rd].set(registers[i.rs1]() & registers[i.rs2]()); // AND
			break;
		case 0x1:
			registers[i.rd].set(registers[i.rs1]() << registers[i.rs2]()); // SLL
			break;
		case 0x5:
			if (i.funct7 == 0)
				registers[i.rd].set( ((uint32_t)registers[i.rs1]()) >> registers[i.rs2]()); // SRL
			else if (i.funct7 == 0x20)
				registers[i.rd].set( (( int32_t)registers[i.rs1]()) >> registers[i.rs2]() ); // SRA
			else
				throw runtime_error("Instruction (SRL/SRA) has invalid funct7");
			break;
		case 0x2:
			registers[i.rd].set( (( int32_t)registers[i.rs1]()) < (( int32_t)registers[i.rs2]()) ); // SLT
			break;
		case 0x3:
			registers[i.rd].set( ((uint32_t)registers[i.rs1]()) < ((uint32_t)registers[i.rs2]()) ); // SLTU
			break;
		default:
			throw runtime_error("Instruction (register-register ALU) has invalid funct3");
	}
}

void CPU::alu_i(IInstruction i) {
	switch (i.funct3) {
		case 0x0:
			registers[i.rd].set(registers[i.rs1]() + i.imm()); // ADDI
			break;
		case 0x4:
			registers[i.rd].set(registers[i.rs1]() ^ i.imm()); // XORI
			break;
		case 0x6:
			registers[i.rd].set(registers[i.rs1]() | i.imm()); // ORI
			break;
		case 0x7:
			registers[i.rd].set(registers[i.rs1]() & i.imm()); // ANDI
			break;
		case 0x1:
			registers[i.rd].set(registers[i.rs1]() << i.imm4_0()); // SLLI
			break;
		case 0x5:
			if (i.imm11_5() == 0)
				registers[i.rd].set( ((uint32_t)registers[i.rs1]()) >> i.imm4_0()); // SRLI
			else if (i.imm11_5() == 0x20)
				registers[i.rd].set( (( int32_t)registers[i.rs1]()) >> i.imm4_0()); // SRAI
			else
				throw runtime_error("Instruction (SRLI/SRAI) has invalid funct7");
			break;
		case 0x2:
			registers[i.rd].set( (( int32_t)registers[i.rs1]()) < i.imm()); // SLTI
			break;
		case 0x3:
			registers[i.rd].set( ((uint32_t)registers[i.rs1]()) < i.imm()); // SLTIU
			break;
		default:
			throw runtime_error("Instruction (register-immediate ALU) has invalid funct3");
	}
}

void CPU::load(IInstruction i) {
	switch (i.funct3) {
		case 0x0: {
			uint32_t byte = memory[ registers[i.rs1]() + i.imm() ];
			byte = SIGN_EXTEND_32BIT(8, byte);
			registers[i.rd].set(byte); // LB
			break;
		} case 0x1: {
			uint32_t addr = registers[i.rs1]() + i.imm();
			uint32_t half = memory[addr+1];
			half = (half << 8) | memory[addr];
			half = SIGN_EXTEND_32BIT(16, half);
			registers[i.rd].set(half); // LH
			break;
		} case 0x2: {
			uint32_t addr = registers[i.rs1]() + i.imm();
			uint32_t word = memory[addr+3];
			word = (word << 8) | memory[addr+2];
			word = (word << 8) | memory[addr+1];
			word = (word << 8) | memory[addr];
			registers[i.rd].set(word); // LW
			break;
		} case 0x4: {
			uint32_t byte = memory[ registers[i.rs1]() + i.imm() ];
			registers[i.rd].set(byte); // LBU
			break;
		} case 0x5: {
			uint32_t addr = registers[i.rs1]() + i.imm();
			uint32_t half = memory[addr+1];
			half = (half << 8) | memory[addr];
			registers[i.rd].set(half); // LHU
			break;
		}
	}
}

void CPU::store(SInstruction i) {
	uint32_t addr = registers[i.rs1]() + i.imm();
	switch(i.funct3) {
		case 0x0: {
			uint8_t byte = (uint8_t)registers[i.rs2]();
			if (addr >= MEMSIZE)
				throw runtime_error("Instruction store byte failed: invalid address");
			memory[addr] = byte; // SB
			break;
		} case 0x1: {
			uint16_t half = (uint16_t)registers[i.rs2]();
			if (addr >= MEMSIZE - 1)
				throw runtime_error("Instruction store half failed: invalid address");
			memory[addr] = (uint8_t)half;
			memory[addr+1] = (uint8_t)(half >> 8); // SH
			break;
		} case 0x2: {
			uint32_t word = registers[i.rs2]();
			if (addr >= MEMSIZE - 3)
				throw runtime_error("Instruction store word failed: invalid address");
			memory[addr] = (uint8_t)word;
			memory[addr+1] = (uint8_t)(word >>= 8);
			memory[addr+2] = (uint8_t)(word >>= 8);
			memory[addr+3] = (uint8_t)(word >> 8); // SW
			break;
		}
	}
}

void CPU::branch(BInstruction i) {
	switch(i.funct3) {
		case 0x0:
			if (registers[i.rs1]() == registers[i.rs2]()) // BEQ
				pc.set(pc() + i.imm());
			break;
		case 0x1:
			if (registers[i.rs1]() != registers[i.rs2]()) // BNE
				pc.set(pc() + i.imm());
			break;
		case 0x4:
			if ((int32_t)registers[i.rs1]() < (int32_t)registers[i.rs2]()) // BLT
				pc.set(pc() + i.imm());
			break;
		case 0x5:
			if ((int32_t)registers[i.rs1]() >= (int32_t)registers[i.rs2]()) // BGE
				pc.set(pc() + i.imm());
			break;
		case 0x6:
			if (registers[i.rs1]() < registers[i.rs2]()) // BLTU
				pc.set(pc() + i.imm());
			break;
		case 0x7:
			if (registers[i.rs1]() >= registers[i.rs2]()) // BGEU
				pc.set(pc() + i.imm());
			break;
	}
}

void CPU::jump_link(JInstruction i) {
	registers[i.rd].set(pc());
	pc.set(pc() + i.imm());
}

void CPU::jump_link_reg(IInstruction i) {
	registers[i.rd].set(pc());
	pc.set(registers[i.rs1]() + i.imm());
}

void CPU::load_upper(UInstruction i) {
	uint32_t upper = i.imm() << 12;
	uint32_t mask = 0x0000FFFF;
	uint32_t val = (registers[i.rd]() & mask) | upper;
	registers[i.rd].set(val);
}

void CPU::add_upper(UInstruction i) {
	uint32_t val = i.imm() << 12;
	val += pc();
	registers[i.rd].set(val);
}

void CPU::environ(IInstruction i) {
	throw runtime_error("Debugging instructions are not supported");
}

std::string CPU::registerName(uint8_t index, bool numeric) {
	if (!numeric)
		return REGISTER_NAMES[index];
	return std::string("x") + std::to_string(index);
}