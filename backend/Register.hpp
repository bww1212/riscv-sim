#ifndef __REGISTER_HPP
#define __REGISTER_HPP

#include "Includes.hpp"

class Register {
	public:
	Register(void); // Dummy constructor for making arrays and such
	Register(int bits); // Valid range will be 0 to bits-1
	~Register();
	
	// Set contents
	void set(uint32_t value) { this->data = value; }
	void setBit(uint8_t bit, uint8_t value);
	// Send a register or part of a register to another
	void send(Register* o, int lsrc, int usrc, int tgt); // Source range (inclusive), destination start
	void send(Register* o) { o->data = this->data; }
	// Access contents of this register
	uint32_t operator()(int lower, int upper); // Range of bits, inclusive
	uint8_t  operator()(int bit); // A single bit
	uint32_t operator()(void) { return this->data; } // The whole register, truncated to the first 32 bits
	
	private:
	int nbits;
	uint32_t data;
};

#endif
