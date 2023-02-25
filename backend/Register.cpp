#include "Register.hpp"
using namespace std;

void Register::Register(int bits) {
	this.nbits = bits;
	this.data = (uint8_t*)malloc(bits);
}

void Register::~Register() {
	free(this.data);
}

void Register::send(Register o, int lsrc, int usrc, int tgt) {
	int len = usrc - lsrc;
	if (tgt + len > o.nbits)
		throw runtime_error("Register send failed: target register doesn't have enough bits");
	taddr = o.data + tgt;
	for (int i=lsrc; i<usrc; ++i) {
		*taddr = this.data[i];
		++taddr;
	}
}

void Register::operator()(int lower, int upper) {
	(void)lower;
	(void)upper;
}

void Register::operator()(int bit) {
	(void)bit;
}

void Register::operator()(void) {
	;
}
