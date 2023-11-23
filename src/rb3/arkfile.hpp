#ifndef _ARKFILE_HPP
#define _ARKFILE_HPP
#include <types.h>
#include "file.hpp"
#include "string.hpp"

class ArkFile : File {
public:
	ArkFile(const char *, int);
	virtual ~ArkFile(); // fn_802E73FC
	virtual String Filename(); // fn_802E7810
	virtual int Read(void *, int); // fn_802E748C
	virtual bool ReadAsync(void *, int); // fn_802E7500
	virtual int V_Unk5(void *, int); // links to fn_802E76D8, which returns 0
	virtual bool Write(const void *, int); // links to fn_8077BAA0, which returns 0
	virtual unsigned int Seek(int, int); // fn_802E76E0
	virtual unsigned int Tell(); // fn_802E7728
	virtual void Flush(); // fn_8076F540 - returns void
	virtual bool Eof(); // fn_802E7730

	virtual bool Fail(); // fn_802E7748
	virtual unsigned int Size(); // fn_802E7758
	virtual unsigned int UncompressedSize(); // fn_802E7760
	virtual int ReadDone(int &); // fn_802E7790

	virtual int V_Unk16(int *); // fn_802E77E4

	virtual void _Open() = 0;

	void fn_800E1114();
	bool fn_802E4F2C();
	void TaskDone(int);

	int unk4;
	unsigned long long unk8;
	int size; // 0x10
	int size_uncompressed; // 0x14
	s32 unk18;
	s32 unk1c;
	u32 fpos;
	s32 unk24;
	s32 unk28;
	s8 unk2c;
	String fname;
};
#endif
