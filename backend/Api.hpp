#ifndef __API_HPP
#define __API_HPP

extern "C" {

void setMemorySize(int bytes);
const char* getInstructionStream();
void loadProgram(uint8_t* bytes, uint size);
const char* getMemory();
const char* getRegisters();
char* getRegister(int registerId);
void execute();

} // extern C

#endif
