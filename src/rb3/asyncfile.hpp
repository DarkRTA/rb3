#ifndef RB3_ASYNCFILE_HPP
#define RB3_ASYNCFILE_HPP
#include "file.hpp"
#include "string.hpp"

class AsyncFile : File {
public:
	AsyncFile(const char*, int);
	virtual ~AsyncFile();
	virtual String GetStringMember();
	virtual int Read(void*, int); // fn_802E7E8C
	virtual bool ReadAsync(void*, int); // fn_802E7F7C
	virtual int V_Unk5(void*, int); // fn_802E7F00
	virtual bool Write(const void*, int); // fn_802E81D4
	virtual unsigned int Seek(int, int); // fn_802E8300
	virtual unsigned int Tell(); // fn_802E84AC
	virtual void Flush(); // fn_802E84B4
	virtual bool Eof(); // fn_802E85E0
	virtual bool Fail(); // fn_802E85F8
	virtual unsigned int Size(); // fn_802E8600
	virtual unsigned int UncompressedSize(); // fn_802E8608
	virtual int ReadDone(int&); // fn_802E8030
	virtual int V_Unk15(int*); // fn_802E81AC
	virtual int V_Unk16(int*) = 0;
	
	virtual void _Open() = 0;
	virtual int V_Unk19() = 0;
	virtual int _Write(const void*, int) = 0;
	virtual int V_Unk21() = 0;
	virtual void V_Unk22() = 0;
	virtual void V_Unk23() = 0;
	virtual int _ReadDone() = 0;
	virtual void _Close() = 0;

	void FillBuffer(); // fn_802E8530
	void Terminate(); // fn_802E7E2C

	// fn_802E7AA8 - possibly New__9AsyncFileFPCci
	// fn_802E7BE4 - possibly Init__9AsyncFileFv

	int unk4;
	bool failed;
	char unk9;
	String str;
	unsigned int fpos;
	int unk1c;
	unsigned int size;
	unsigned int size_uncompressed;
	char* unk28;
	char* unk2c;
	int unk30;
	int unk34;
};

#endif
