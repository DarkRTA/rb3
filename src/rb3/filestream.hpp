#ifndef RB3_FILESTREAM_HPP
#define RB3_FILESTREAM_HPP
#include "binstream.hpp"
#include "string.hpp"
#include "asyncfilewii.hpp"

class FileStream : BinStream {
public:
	FileStream(char, char*, int);
	FileStream(char);
	virtual ~FileStream(); // fn_8034CB20

	virtual void V_Unk1(); // fn_8034CCA8
	virtual void V_Unk2(); // fn_8034CD30
	virtual void V_Unk3(); // fn_8034CD44
	virtual void V_Unk4(); // fn_8034CD7C
	virtual const char* GetStreamName(); // fn_800C20FC
	virtual void V_Unk6(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk7(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk8(); // fn_8034CBCC
	virtual void V_Unk9(); // fn_8034CC50
	virtual void V_Unk10(); // fn_8034CCBC

	char unkc; // actually supposed to be the class AsyncFileWii - NewFile() will return this
	String str;
	int unk1c; // either a char or bool, probably a bool
	int unk20;
	int unk24;
};

#endif
