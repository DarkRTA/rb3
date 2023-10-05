#ifndef _ARKFILE_HPP
#define _ARKFILE_HPP
#include <types.h>
#include "file.hpp"
#include "string.hpp"

class ArkFile : File {
public:
	ArkFile(const char*, int);
	virtual ~ArkFile(); // fn_802E73FC
	virtual String GetStringMember(); // fn_802E7810
	virtual int Read(void*, int); // fn_802E748C
	virtual bool ReadAsync(void*, int); // fn_802E7500

	// in ieee's arkfile.cpp
	virtual int V_Unk5(void*, int); // links to fn_802E76D8, which returns 0
	virtual bool Write(const void*, int); // links to fn_8077BAA0, which returns 0
	virtual unsigned int Seek(int, int); // fn_802E76E0
	virtual unsigned int Tell(); // fn_802E7728
	virtual void Flush(); // fn_8076F540 - returns void
	virtual bool Eof(); // fn_802E7730

	virtual bool Fail(); // fn_802E7748
	virtual unsigned int Size(); // fn_802E7758
	virtual unsigned int UncompressedSize(); // fn_802E7760
	virtual int ReadDone(int&); // fn_802E7790
	
	virtual int V_Unk16(int*); // fn_802E77E4
	
	virtual void _Open() = 0;

	// u32 ReturnsZero(); // 0x802E76D8; marked to be labeled as fn_802E76D8_ret0 in syms.txt... but it's already labeled as ReturnsZero
	// u32 Seek(int offset, int mode);
	// u32 FilePos(void);
	// bool EndOfFile(void);

	void fn_800E1114();
	bool fn_802E4F2C();
	void TaskDone(int);
	

	s32 unk4;
	s32 unk8;
	s32 unkc;
	unsigned int size;
	unsigned int size_uncompressed;
	s32 unk18;
	s32 unk1c;
	u32 fpos;
	s32 unk24;
	s32 unk28;
	s8 unk2c;
	String str;
};
#endif
