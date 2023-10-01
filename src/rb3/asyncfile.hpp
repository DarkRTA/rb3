#ifndef RB3_ASYNCFILE_HPP
#define RB3_ASYNCFILE_HPP
#include "file.hpp"
#include "string.hpp"

class AsyncFile: File {
public:
	AsyncFile(const char*, int);
	virtual ~AsyncFile();
	virtual String fn_802E8678();
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
	virtual void unk1() = 0;
	virtual void fn_8077BAA0();
	virtual void unk2() = 0;
	virtual void unk3() = 0;
	virtual void unk4() = 0;
	virtual void unk5() = 0;
	virtual void unk6() = 0;
	virtual void unk7() = 0;
	virtual void unk8() = 0;
	virtual void unk9() = 0;

	int unk4_async;
	char unk8_async;
	char unk9_async;
	String unkc_async;
	int unk18_async;
	int unk1c_async;
	int unk20_async;
	int unk24_async;
	int unk28_async;
	int unk2c_async;
	int unk30_async;
};

#endif
