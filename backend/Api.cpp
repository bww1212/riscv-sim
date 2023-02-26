#include "CPU.hpp"
#include "CPU.cpp"
#include "Register.hpp"
#include "Register.cpp"

#include <sstream>
#include <string>
#include <iomanip>

CPU cpu;

std::string numToHex(uint digits, uint32_t value) {
    std::ostringstream out;
    out << std::hex << std::setw(digits) << std::setfill('0') << std::uppercase << value;
    return out.str();
}

extern "C" {
    // Allocate this many bytes of memory. Always call this before execution.
    void setMemorySize(int bytes) { ; }
    // Returns empty string if beyond end of the program
    // Offset is relative to the PC
    char* getInstructionStream(int offset) { return "add x1 x1 x1"; }
    // Load program into memory and start executing
    void loadProgram(uint8_t* bytes, uint size) {
        cpu.loadProgram(bytes, size);
    }
    // Returns all of memory in hex
    const char* getMemory() {
        std::string ret;
        for (int i = 0; i < 4096; i += 4) {
            ret += numToHex(8, i) + ":" + numToHex(8, cpu.wordAtMemory(i)) + "\n";
        }
        return ret.c_str();
    }
    // Get a list of all registers
    const char* getRegisters() { 
        std::string ret;
        for (int i = 0; i < 32; i++) {
            ret += CPU::registerName(i) + ":" + 
                numToHex(8, cpu.registerContents(i)) + "\n";
        }
        ret += std::string("PC:") + numToHex(8, cpu.pcContents()) + "\n";
        return ret.c_str();
    }
    // Returns the hex value of the register ID
    char* getRegister(int registerId) { return "00000000"; }
    // Execute the current instruction and step forward
    void execute() {
        cpu.executeInstruction();
    }
}