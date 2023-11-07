#ifndef RB3_KEYBOARDKEYRELEASEDMSG_HPP
#define RB3_KEYBOARDKEYRELEASEDMSG_HPP
#include "message.hpp"

class KeyboardKeyReleasedMsg : Message {
public:
	KeyboardKeyReleasedMsg(int, int); // fn_80315298
	virtual ~KeyboardKeyReleasedMsg(); // fn_800A7FF4
};

#endif
