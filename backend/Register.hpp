#ifndef __REGISTER_HPP
#define __REGISTER_HPP

#include "Includes.hpp"

class Register {
	public:
	Register(int bits);
	~Register();
	void send(Register o, int lsrc, int usrc, int tgt);
	void send(Register o) { send(o, 0, this.nbits, 0); }
	uint32_t operator()(int lower, int upper);
	uint8_t  operator()(int bit);
	uint32_t operator()(void);
	
	private:
	int nbits;
	uint8_t* data;
}

#endif
