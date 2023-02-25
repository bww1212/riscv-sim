#include "Register.hpp"

int main(void) {
	Register x[32];
	x[1] = Register(32);
	Register y = x[1];
	printf("1: %x", y());
	y.setBit(3, 1);
	printf("2: %x", y());
	y.set(32768);
	printf("3: %x", y());
	printf("4: %x", y(0, 7));
	printf("5: %x", y(7, 15));
	return 0;
}
