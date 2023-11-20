#ifndef RB3_RAND_HPP
#define RB3_RAND_HPP

class Rand {
public:
	Rand(int); // fn_802DD9A4
	void Seed(int); // fn_802DDA04
	int Int();

	unsigned int unk00;
	unsigned int unk04;
	unsigned int unk_arr[0x100];
};

#endif
