#include "Includes.hpp"
#include "Api.hpp"
#include <fstream>
#include <sstream>
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
	loadProgram(bytes, len);
	printf("Program loaded.\nMain memory:\n%s", getMemory());
	printf("Press enter to execute instructions.\n");
	while (getchar()) {
		execute();
		printf("%s", getRegisters());
	}
}

int main(int argc, char** argv) {
	runProgram(argc, argv);
	return 0;
}
