#include "Register.hpp"

int main(void) {
	Register x[32];
	x[1] = Register(32);
	Register y = x[1];
	printf("1: %x\n", y());
	y.setBit(3, 1);
	printf("2: %x\n", y());
	y.set(32768);
	printf("3: %x\n", y());
	printf("4: %x\n", y(0, 7));
	printf("5: %x\n", y(7, 15));
	return 0;
}
