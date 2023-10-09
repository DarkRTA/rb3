#ifndef RB3_FIXEDSIZESAVABLESTREAM_HPP
#define RB3_FIXEDSIZESAVABLESTREAM_HPP
#include "bufstream.hpp"

class FixedSizeSaveableStream : BufStream {
public:
	FixedSizeSaveableStream(void*, int, bool); // fn_8050FA30, vtable lbl_8088BE40
	virtual ~FixedSizeSaveableStream(); // fn_8050FA88
	
	virtual void Unk11(); // links to fn_8077BAA0, which returns 0
	virtual void unk12(); // links to fn_8077BAA0, which returns 0
};

#endif
