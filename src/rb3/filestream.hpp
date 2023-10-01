#ifndef RB3_FILESTREAM_HPP
#define RB3_FILESTREAM_HPP
#include "binstream.hpp"
#include "string.hpp"

class FileStream : BinStream {
public:
	FileStream(char, char*, int);
	FileStream(char);
	virtual ~FileStream(); // fn_8034CB20
	virtual void fn_8034CCA8();
	virtual void fn_8034CD30();
	virtual void fn_8034CD44();
	virtual void fn_8034CD7C();
	virtual void fn_800C20FC();
	virtual void fn_8077BAA0();
	// virtual void fn_8077BAA0();
	virtual void fn_8034CBCC();
	virtual void fn_8034CC50();
	virtual void fn_8034CCBC();
	// from BinStream
	virtual void unk1();
	virtual void unk2();
	virtual void unk3();
	virtual void unk4();
	virtual void unk5();
	virtual void unk6();
	virtual void unk7();

	char cc; // actually supposed to be the class AsyncFileWii - NewFile() will return this
	String str;
	int unk1c; // either a char or bool, probably a bool
	int unk20;
	int unk24;
};

#endif
