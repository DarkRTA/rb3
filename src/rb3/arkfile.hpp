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
	virtual int V_Unk3(char*, int); // fn_802E748C
	virtual bool V_Unk4(char*, int); // fn_802E7500

	// no function definitions found for these?
	virtual int V_Unk5(char*, int); // fn_802E76D8
	virtual bool V_Unk6(char*, int); // links to fn_8077BAA0, which returns 0
	virtual unsigned int V_Unk7(int, int); // fn_802E76E0
	virtual unsigned int V_Unk8(); // fn_802E7728
	virtual void V_Unk9(); // fn_8076F540 - returns
	virtual bool V_Unk10(); // fn_802E7730

	virtual bool V_Unk11(); // fn_802E7748
	virtual unsigned int GetFileSize(); // fn_802E7758
	virtual int V_Unk13(); // fn_802E7760
	virtual int V_Unk14(int*); // fn_802E7790
	virtual int V_Unk15(int*); // fn_802E7818
	virtual int V_Unk16(); // fn_802E77E4
	virtual void V_Unk17(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk18() = 0;

	u32 ReturnsZero(); // 0x802E76D8; marked to be labeled as fn_802E76D8_ret0 in syms.txt... but it's already labeled as ReturnsZero
	u32 Seek(int offset, int mode);
	u32 FilePos(void);
	bool EndOfFile(void);

	void fn_800E1114();
	bool fn_802E4F2C();

	s32 unk4;
	s32 unk8;
	s32 unkc;
	u32 filesize;
	s32 unk14;
	s32 unk18;
	s32 unk1c;
	u32 fpos;
	s32 unk24;
	s32 unk28;
	s8 unk2c;
	String str;
};
#endif
