#ifndef RB3_BINSTREAM_HPP
#define RB3_BINSTREAM_HPP
#include "symbol.hpp"
#include "string.hpp"
#include "rand2.hpp"

class BinStream {
public:
	enum SeekType {
		SeekMode0, SeekMode1, SeekMode2
	};

	BinStream(bool);
	virtual ~BinStream();
	virtual void Flush() = 0;
	virtual int Tell() = 0;
	virtual bool Eof() = 0;
	virtual bool Fail() = 0;
	virtual const char* Name() const; // fn_80342ACC
	virtual void V_Unk6(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk7(); // links to fn_8077BAA0, which returns 0
	virtual void ReadImpl(void*, int) = 0;
	virtual void WriteImpl(const void*, int) = 0;
	virtual void SeekImpl(int, SeekType) = 0; // the second int should actually be of type BinStream::SeekType

	bool unk04;
	Rand2* unk08;

	// taken from RB2
	BinStream* operator<<(const char*);
	BinStream* operator<<(const Symbol&);
	BinStream* operator<<(const String&);
	BinStream* operator>>(Symbol&);
	BinStream* operator>>(String&);

	void WriteEndian(const void*, int);
	void Write(const void*, int);
	
	void ReadString(char*, int);
	void ReadEndian(void*, int);
	void Read(void*, int);
	
	void EnableReadEncryption();
	void EnableWriteEncryption(int);
	void DisableEncryption();
	void Seek(int, SeekType);

	// not taken from RB2, found in the asm
	BinStream* WriteEndian4(unsigned int);
	BinStream* ReadEndian4(unsigned int*);
	BinStream* ReadSingle(void*);
	BinStream* ReadSingleIntoBool(bool*);
	BinStream* WriteSingle(char);

};

#endif
