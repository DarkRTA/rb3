#ifndef RB3_NETSTREAM_HPP
#define RB3_NETSTREAM_HPP
#include "binstream.hpp"
#include "types.h"
class NetStream : BinStream {
	// NetStream(); // not in the vtable? odd
	~NetStream();
	virtual void V_Unk2(); // links to fn_8076F540, which returns nothing
	virtual void V_Unk3(); // links to fn_8077BAA0, which returns 0
	unsigned int fn_80308880();
	u8 fn_800DB158();
	// BinStream::Name (?)
	virtual void V_Unk7(); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk8(); // links to fn_8077BAA0, which returns 0
	void fn_803088BC(void *, size_t); // TODO figure out actual types
	void fn_803089D4(int, int); // see above comment

	u8 undef1[4];
	u8 aaaa;
	u8 undef2[3];
	BinStream *binstream_maybe; // ????
	u8 undef3[16];
};
#endif
