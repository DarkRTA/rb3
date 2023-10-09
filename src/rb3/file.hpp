#ifndef RB3_FILE_HPP
#define RB3_FILE_HPP
#include "string.hpp"

class File {
public:
	File();
	virtual ~File();
	virtual String GetStringMember();
	virtual int Read(void *, int) = 0;
	virtual bool ReadAsync(void *, int) = 0;
	virtual int V_Unk5(char *, int) = 0;
	virtual bool
	Write(const void *, int); // links to fn_8077BAA0, which returns 0
	virtual unsigned int Seek(int, int) = 0;
	virtual unsigned int Tell() = 0;
	virtual void Flush() = 0;
	virtual bool Eof() = 0;
	virtual bool Fail() = 0;
	virtual unsigned int Size() = 0;
	virtual unsigned int UncompressedSize() = 0;
	virtual int ReadDone(int &) = 0;
	virtual int V_Unk15(int *); // fn_802E7818
	virtual int V_Unk16(int *) = 0;
	virtual void V_Unk17(); // links to fn_8077BAA0, which returns 0

	static int sOpenCount[4];
};

#endif
