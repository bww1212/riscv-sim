#include Register.hpp

void main(void) {
	Register x[32];
	x[1] = Register(32);
	y = x[1];
	printf("1: %lx", y());
	y.setBit(3, 1);
	printf("2: %lx", y());
	y.setValue(32768);
	printf("3: %lx", y());
	printf("4: %lx", y(0, 7));
	printf("5: %lx", y(7, 15));
}
