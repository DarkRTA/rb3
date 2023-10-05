#ifndef RB3_FILESTREAM_HPP
#define RB3_FILESTREAM_HPP
#include "binstream.hpp"
#include "string.hpp"
#include "file.hpp"
#include "asyncfile.hpp"

class FileStream : BinStream {
public:
	FileStream(char, char*, int); // RB2 says this is FileStream(const char*, FileStream::FileType, bool)
	FileStream(char); // RB2 says this is FileStream(File*, bool)
	virtual ~FileStream(); // fn_8034CB20

	virtual void V_Unk1(); // fn_8034CCA8
	virtual void V_Unk2(); // fn_8034CD30
	virtual void V_Unk3(); // fn_8034CD44
	virtual bool Fail(); // fn_8034CD7C
	virtual const char* Name() const; // fn_800C20FC
	virtual void V_Unk6(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk7(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk8(); // fn_8034CBCC // ReadImpl
	virtual void V_Unk9(); // fn_8034CC50 - WriteImpl
	virtual void V_Unk10(); // fn_8034CCBC - SeekImpl

	// RB2 FileStream vtable methods:
	// Flush, Tell, Eof, Fail, Name, ReadImpl, WriteImpl, SeekImpl

	char unkc; // some sort of File (AsyncFile, AsyncFileWii, etc) - NewFile() will return this
	String fname;
	bool failed;
	int unk20;
	int unk24;
};

#endif
