#ifndef RB3_BINSTREAM_HPP
#define RB3_BINSTREAM_HPP

class BinStream {
public:
	BinStream(char);
	virtual ~BinStream();
	virtual void unk1() = 0;
	virtual void unk2() = 0;
	virtual void unk3() = 0;
	virtual void unk4() = 0;
	virtual const char* GetLabelUnnamed(); // fn_80342ACC
	virtual void fn_8077BAA0();
	// virtual void fn_8077BAA0();
	virtual void unk5() = 0;
	virtual void unk6() = 0;
	virtual void unk7() = 0;

	char unk04;
	char* unk08;
};

#endif
