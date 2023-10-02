#ifndef RB3_FILE_HPP
#define RB3_FILE_HPP
#include "string.hpp"

class File {
public:
	File();
	virtual ~File();
	virtual String GetStringMember();
	virtual void v_unk1() = 0;
	virtual void v_unk2() = 0;
	virtual void v_unk3() = 0;
	virtual void fn_8077BAA0();
	virtual void v_unk4() = 0;
	virtual void v_unk5() = 0;
	virtual void v_unk6() = 0;
	virtual void v_unk7() = 0;
	virtual void v_unk8() = 0;
	virtual void v_unk9() = 0;
	virtual void v_unk10() = 0;
	virtual void v_unk11() = 0;
	virtual void fn_802E7818();
	virtual void v_unk12() = 0;
	// virtual void fn_8077BAA0();

	static int sOpenCount[4];
};

#endif
