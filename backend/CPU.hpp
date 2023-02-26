#ifndef __CPU_HPP
#define __CPU_HPP

#include "Register.hpp"
#include "Instruction.hpp"

#include <array>

#define MEMSIZE 4096

class CPU {
    public:
        CPU();
        uint32_t executeInstruction();
        void loadProgram(uint8_t* bytes, uint size);
        const uint8_t* memoryPointer(uint16_t address = 0);
        uint8_t byteAtMemory(uint16_t address);
        uint16_t halfWordAtMemory(uint16_t address);
        uint32_t wordAtMemory(uint16_t address);
        uint32_t registerContents(uint8_t index);
        uint32_t pcContents();
    private:
        void reset();
        // Data
        Register pc;
        Register registers[32];
        uint8_t memory[MEMSIZE];
        Register &zero, &ra, &sp, &gp, &tp, &fp;
        Register &t0, &t1, &t2, &t3, &t4, &t5, &t6;
        Register &s0, &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9, &s10, &s11;
        Register &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7;
        // Execute
		void  alu_r(RInstruction i);
		void  alu_i(IInstruction i);
		void   load(IInstruction i);
		void  store(SInstruction i);
		void branch(BInstruction i);
		void jump_link(JInstruction i);
		void jump_link_reg(IInstruction i);
		void load_upper(UInstruction i);
		void  add_upper(UInstruction i);
		void environ(IInstruction i);
};

#endif
