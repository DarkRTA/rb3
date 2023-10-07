#ifndef RB3_BINSTREAM_HPP
#define RB3_BINSTREAM_HPP
#include "symbol.hpp"
#include "string.hpp"
#include "rand2.hpp"

class BinStream {
public:
	BinStream(bool);
	virtual ~BinStream();
	virtual void V_Unk1() = 0;
	virtual void V_Unk2() = 0;
	virtual void V_Unk3() = 0;
	virtual bool Fail() = 0;
	virtual const char* Name() const; // fn_80342ACC
	virtual void V_Unk6(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk7(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk8() = 0;
	virtual void V_Unk9() = 0;
	virtual void V_Unk10() = 0;

	bool unk04;
	Rand2* unk08;

	// taken from RB2
	BinStream* operator<<(const char*);
	void WriteEndian(const void*, int);
	void Write(const void*, int);
	BinStream* operator<<(const Symbol&);
	BinStream* operator<<(const String&);
	void ReadString(char*, int);
	void ReadEndian(void*, int);
	void Read(void*, int);
	BinStream* operator>>(Symbol&);
	BinStream* operator>>(String&);
	void EnableReadEncryption();
	void EnableWriteEncryption(int);
	void DisableEncryption();
	//void Seek(int, BinStream::SeekType);

	BinStream* WriteEndian4(unsigned int);
	BinStream* ReadEndian4(unsigned int*);

	void fn_80342D98();
	void fn_80342DE4();

};

#endif
