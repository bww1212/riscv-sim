#ifndef __CPU_HPP
#define __CPU_HPP

#include "Register.hpp"
#include "Instruction.hpp"

#include <array>

class CPU {
    public:
        CPU();
        uint32_t executeInstruction();
        void loadProgram(uint8_t* bytes, uint size);
    private:
        void reset();
        // Data
        Register pc;
        Register registers[32];
        uint8_t memory[4096];
        Register &zero, &ra, &sp, &gp, &tp, &fp;
        Register &t0, &t1, &t2, &t3, &t4, &t5, &t6;
        Register &s0, &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9, &s10, &s11;
        Register &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7;
        // Execute
		void alu_r(RInstruction i);
		void alu_i(IInstruction i);
};

#endif
