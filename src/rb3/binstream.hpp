#ifndef RB3_BINSTREAM_HPP
#define RB3_BINSTREAM_HPP

class BinStream {
public:
	BinStream(char);
	virtual ~BinStream();
	virtual void V_Unk1() = 0;
	virtual void V_Unk2() = 0;
	virtual void V_Unk3() = 0;
	virtual void V_Unk4() = 0;
	virtual const char* GetStreamName(); // fn_80342ACC
	virtual void V_Unk6(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk7(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk8() = 0;
	virtual void V_Unk9() = 0;
	virtual void V_Unk10() = 0;

	char unk04;
	char* unk08;
};

#endif
