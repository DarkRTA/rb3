#ifndef RB3_ASYNCFILEWII_HPP
#define RB3_ASYNCFILEWII_HPP
#include "asyncfile.hpp"
#include "file.hpp"
#include "string.hpp"

class AsyncFileWii : AsyncFile {
public:
	AsyncFileWii(const char*, int);
	virtual ~AsyncFileWii();
	// virtual String fn_802E8678(); // reused from AsyncFile
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
	virtual void fn_8077BAA0();
	// virtual void fn_8077BAA0();
	virtual void fn_802E8BCC();
	virtual int fn_802E8C48();
	virtual void fn_802E8C50();
	virtual int fn_802E8C54();
	virtual void fn_802E8C5C();
	virtual void fn_802E8CB8();
	virtual void fn_802E8D28();
	virtual void fn_802E8F1C();

	int unk34;
	int unk38;
	char unk3c;
	int unk40;
	int unk44;
	int unk48, unk4c, unk50, unk54, unk58, unk5c, unk60, unk64, unk68, unk6c, unk70, unk74;
	int unk78;
};

#endif
