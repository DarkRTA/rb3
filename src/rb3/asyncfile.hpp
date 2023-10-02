#ifndef RB3_ASYNCFILE_HPP
#define RB3_ASYNCFILE_HPP
#include "file.hpp"
#include "string.hpp"

class AsyncFile : File {
public:
	AsyncFile(const char*, int);
	virtual ~AsyncFile();
	virtual String GetStringMember();
	virtual void fn_802E7E8C();
	virtual void fn_802E7F7C();
	virtual void fn_802E7F00();
	virtual void fn_802E81D4();
	virtual void fn_802E8300();
	virtual void fn_802E84AC();
	virtual void fn_802E84B4();
	virtual void fn_802E85E0();
	virtual void fn_802E85F8();
	virtual void fn_802E8600();
	virtual void fn_802E8608();
	virtual void fn_802E8030();
	virtual void fn_802E81AC();
	virtual void v_unk1() = 0;
	virtual void fn_8077BAA0();
	virtual void v_unk2() = 0;
	virtual void v_unk3() = 0;
	virtual void v_unk4() = 0;
	virtual void v_unk5() = 0;
	virtual void v_unk6() = 0;
	virtual void v_unk7() = 0;
	virtual void v_unk8() = 0;
	virtual void v_unk9() = 0;

	int unk4;
	char unk8;
	char unk9;
	String unkc;
	int unk18;
	int unk1c;
	int unk20;
	int unk24;
	int unk28;
	int unk2c;
	int unk30;
};

#endif
