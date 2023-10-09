#ifndef RB3_FILESTREAM_HPP
#define RB3_FILESTREAM_HPP
#include "binstream.hpp"
#include "string.hpp"
#include "file.hpp"
#include "streamchecksum.hpp"

class FileStream : BinStream {
public:

	enum FileType {
		FileType0, FileType1, FileType2, FileType3
	};

	FileStream(const char*, FileType, bool); // RB2 says this is FileStream(const char*, FileStream::FileType, bool)
	FileStream(File*, bool); // RB2 says this is FileStream(File*, bool)
	virtual ~FileStream(); // fn_8034CB20

	virtual void Flush(); // fn_8034CCA8
	virtual int Tell(); // fn_8034CD30
	virtual bool Eof(); // fn_8034CD44
	virtual bool Fail(); // fn_8034CD7C
	virtual const char* Name() const; // fn_800C20FC
	virtual void V_Unk6(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk7(); // links to fn_8077BAA0, which returns 0
	virtual void ReadImpl(void*, int); // fn_8034CBCC // ReadImpl
	virtual void WriteImpl(const void*, int); // fn_8034CC50
	virtual void SeekImpl(int, SeekType); // fn_8034CCBC
	
	void DeleteChecksum();
	void StartChecksum();

	File* file;
	String fname;
	bool failed;
	StreamChecksum* unk20;
	int unk24; // probably a ptr to another class
};

#endif
