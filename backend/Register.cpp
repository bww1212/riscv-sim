#include "Register.hpp"
using namespace std;

void Register::Register(void) {
	// Dummy constructor
	this.nbits = 0;
	this.data = NULL;
}

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

uint32_t Register::operator()(int lower, int upper) {
	if (lower < 0 || upper >= this.nbits)
		throw runtime_error("Register read by bounds failed: invalid bounds");
	uint32_t ret = 0;
	for (int i=lower; i<=upper; ++i) {
		ret <<= 1;
		ret |= this.data[i];
	}
	return ret;
}

uint8_t Register::operator()(int bit) {
	if (bit < 0 || bit >= this.nbits)
		throw runtime_error("Register read bit failed: invalid index");
	return this.data[bit];
}

uint32_t Register::operator()(void) {
	return *(uint32_t*)this.data;
}
