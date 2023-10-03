#ifndef RB3_FILE_HPP
#define RB3_FILE_HPP
#include "string.hpp"

class File {
public:
	File();
	virtual ~File();
	virtual String GetStringMember();
	virtual int V_Unk3(char*, int) = 0;
	virtual bool V_Unk4(char*, int) = 0;
	virtual int V_Unk5(char*, int) = 0;
	virtual bool V_Unk6(char*, int); // links to fn_8077BAA0, which returns 0
	virtual unsigned int V_Unk7(int, int) = 0;
	virtual unsigned int V_Unk8() = 0;
	virtual void V_Unk9() = 0;
	virtual bool V_Unk10() = 0;
	virtual bool V_Unk11() = 0;
	virtual unsigned int GetFileSize() = 0;
	virtual int V_Unk13() = 0;
	virtual int V_Unk14(int*) = 0;
	virtual int V_Unk15(int*); // fn_802E7818
	virtual int V_Unk16() = 0;
	virtual void V_Unk17(); // links to fn_8077BAA0, which returns 0

	static int sOpenCount[4];
};

#endif
