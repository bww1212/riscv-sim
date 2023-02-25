#include "Register.hpp"
using namespace std;

Register::Register(void) {
	// Dummy constructor
	this->nbits = 0;
	this->data = 0;
}

Register::Register(int bits) {
	if (bits > 32)
		throw runtime_error("Registers cannot be longer than 32 bits");
	this->nbits = bits;
	this->data = 0;
}

Register::~Register() {}

void Register::set(uint32_t value) {
	this->data = value;
}

void Register::setBit(uint8_t bit, uint8_t value) {
	if (value != 0 && value != 1)
		throw runtime_error("Register set bit failed: value must be 0 or 1");
	if (bit >= this->nbits)
		throw runtime_error("Register set bit failed: invalid bit index");
	uint32_t mask = ~(1 << bit);
	this->data &= mask;         // Clear the desired bit
	this->data |= value << bit; // Set the bit if requested
}

void Register::send(Register* o, int lsrc, int usrc, int tgt) {
	if (usrc < lsrc)
		throw runtime_error("Register send failed; starting index must be before ending index");
	if ((usrc - lsrc) + tgt > o->nbits)
		throw runtime_error("Register send failed: target register doesn't have enough bits");
	uint32_t mask = 0xFFFFFFFFu << (this->nbits - usrc); // Shift out the upper bits
	mask >>= (this->nbits - usrc) + lsrc; // Shift out the lower bits
	mask <<= lsrc; // Bring it back to the right location
	
	o->data &= ~mask;
	o->data |= (this->data & mask);
}

uint32_t Register::operator()(int lower, int upper) {
	if (lower < 0 || upper >= this->nbits)
		throw runtime_error("Register read by bounds failed: invalid bounds");
	uint32_t bits = this->data << (this->nbits - upper); // Shift out the upper bits
	data >>= (this->nbits - upper) + lower; // Shift out the lower bits
	// Leave as-is, in the lowermost bits
	return data;
}

uint8_t Register::operator()(int bit) {
	if (bit < 0 || bit >= this->nbits)
		throw runtime_error("Register read bit failed: invalid index");
	uint32_t this_bit = 1 << bit;
	this_bit = this_bit & data;
	this_bit >>= bit;
	return this_bit;
}

uint32_t Register::operator()(void) {
	return this->data;
}
