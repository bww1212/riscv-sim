#include "Register.hpp"

int main(void) {
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
}
