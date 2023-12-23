#include "memstream.hpp"

extern void fn_80119430(void *, int);

// fn_80354E6C
MemStream::MemStream(bool b) : BinStream(b)
{
	fn_80119430(&unk14, 0x1000);
	failed = false;
	pos = 0;
}