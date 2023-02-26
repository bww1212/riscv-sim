#include "Includes.hpp"
#include "CPU.hpp"
#include <fstream>
#include <iostream>
using namespace std;

/*
#include "Register.hpp"
static void testRegister() {
	Register x[32];
	x[1] = Register(32);
	Register y = x[1];
	printf("0: %x\n", y());
	y.setBit(3, 1);
	printf("8: %x\n", y());
	y.set(400);
	printf("190: %x\n", y());
	printf("190: %x\n", y(0, 31));
	printf("90: %x\n", y(0, 7));
	printf("1: %x\n", y(8, 15));
	printf("0: %x\n", y(16, 23));
	printf("0: %x\n", y(24, 31));
	return 0;
}*/

static std::string numToHex(uint digits, uint32_t value) {
    std::ostringstream out;
    out << std::hex << std::setw(digits) << std::setfill('0') << std::uppercase << value;
    return out.str();
}

static void runProgram(int argc, char** argv) {
	// Load the file
	if (argc != 2)
		throw runtime_error("Please provide the path to the object file to load");
	char* fname = argv[1];
	ifstream fobj(fname);
	if (!fobj)
		throw runtime_error("Could not open the provided file.");
	stringstream ss;
	ss << fobj.rdbuf();
	fobj.close();
	const string& str = ss.str();
	uint8_t* bytes = (uint8_t*)str.c_str();
	const int len = str.length();
	// Start execution
	CPU cpu;
	cpu.loadProgram(bytes, len);
	//printf("Program loaded.\nMain memory:\n%s", getMemory());
	printf("Press enter to execute instructions.\n");
	int i = 1;
	while (getchar()) {
		printf("Executing instruction %d...\n", i);
		cpu.executeInstruction();
		std::string registers;
    	for (int i = 0; i < 32; i++) {
			registers += CPU::registerName(i) + ":" + 
				numToHex(8, cpu.registerContents(i)) + "\n";
        }
        registers += std::string("PC:") + numToHex(8, cpu.pcContents()) + "\n";
		printf("Registers: %s\n", registers.c_str());
		++i;
	}
}

int main(int argc, char** argv) {
	runProgram(argc, argv);
	return 0;
}
