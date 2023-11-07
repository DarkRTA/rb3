#ifndef RB3_KEYBOARDMODMSG_HPP
#define RB3_KEYBOARDMODMSG_HPP
#include "message.hpp"

class KeyboardModMsg : Message {
public:
	KeyboardModMsg(int, int); // fn_80315370
	virtual ~KeyboardModMsg(); // fn_800A7FF4
};

#endif
