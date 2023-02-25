class Register {
	Register(int bits);
	~Register();
	void send(Register o, int lsrc, int usrc, int tgt);
	void send(Register o);
	long operator()(int lower, int upper);
	uint8_t operator()(int bit);
}
