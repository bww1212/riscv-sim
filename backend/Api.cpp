#include "CPU.hpp"

extern "C" {
    // Allocate this many bytes of memory. Always call this before execution.
    void setMemorySize(int bytes) { ; }
    // Returns empty string if beyond end of the program
    // Offset is relative to the PC
    char* getInstructionStream(int offset) { return "add x1 x1 x1"; }
    // Returns all of memory in hex
    char* getMemory() { return "00"; }
    // Returns the hex value of the register ID
    char* getRegister(int registerId) { return "00000000"; }
    // Execute the current instruction and step forward
    void execute() { ; }
}