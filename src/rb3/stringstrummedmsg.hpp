#ifndef RB3_STRINGSTRUMMEDMSG_HPP
#define RB3_STRINGSTRUMMEDMSG_HPP
#include "message.hpp"

class StringStrummedMsg : Message {
public:
	// has R4-R7, so should be StringStrummedMsg(r4, r5, r6, r7)
	StringStrummedMsg(); // fn_80313E98
	~StringStrummedMsg(); // fn_800A7FF4
};

#endif
