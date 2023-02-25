#include "CPU.hpp"

#include <memory>
#include <cstring>

CPU::CPU() : zero(registers[0]), ra(registers[1]), sp(registers[2]), gp(registers[3]),
    tp(registers[4]), t0(registers[5]), t1(registers[6]), t2(registers[7]), s0(registers[8]),
    fp(registers[8]), s1(registers[9]), a0(registers[10]), a1(registers[11]), a2(registers[12]),
    a3(registers[13]), a4(registers[14]), a5(registers[15]), a6(registers[16]), a7(registers[17]),
    s2(registers[18]), s3(registers[19]), s4(registers[20]), s5(registers[21]), s6(registers[22]),
    s7(registers[23]), s8(registers[24]), s9(registers[25]), s10(registers[26]), s11(registers[27]),
    t3(registers[28]), t4(registers[29]), t5(registers[30]), t6(registers[31]) {
    reset();
}

void CPU::reset() {
    for (int i = 0; i < 32; i++)
        registers[i] = Register(32);
    memset(memory, 0, 4096);
}

void CPU::loadProgram(uint8_t* bytes, uint size) {
    reset();
    memcpy(memory, bytes, size);
}

uint32_t CPU::executeInstruction() {
    return pc();
}

void CPU::alu_r(RInstruction i) {
	switch (i.funct3) {
		case 0x0:
			if (i.funct7 == 0) {
				registers[i.rd].set(registers[i.rs1]() + registers[i.rs2]()); // ADD
			} else {
				registers[i.rd].set(registers[i.rs1]() - registers[i.rs2]()); // SUB
			}
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
			else
				registers[i.rd].set( (( int32_t)registers[i.rs1]()) >> registers[i.rs2]() ); // SRA
			break;
		case 0x2:
			registers[i.rd].set( (( int32_t)registers[i.rs1]()) < (( int32_t)registers[i.rs2]()) ); // SLT
			break;
		case 0x3:
			registers[i.rd].set( ((uint32_t)registers[i.rs1]()) < ((uint32_t)registers[i.rs2]()) ); // SLTU
			break;
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
			else
				registers[i.rd].set( (( int32_t)registers[i.rs1]()) >> i.imm4_0()); // SRAI
			break;
		case 0x2:
			registers[i.rd].set( (( int32_t)registers[i.rs1]()) < i.imm()); // SLTI
			break;
		case 0x3:
			registers[i.rd].set( ((uint32_t)registers[i.rs1]()) < i.imm()); // SLTIU
			break;
	}
}
