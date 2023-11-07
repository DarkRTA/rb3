#ifndef RB3_KEYBOARDCONNECTEDACCESSORIESMSG_HPP
#define RB3_KEYBOARDCONNECTEDACCESSORIESMSG_HPP
#include "message.hpp"

class KeyboardConnectedAccessoriesMsg : Message {
public:
	KeyboardConnectedAccessoriesMsg(int, int); // fn_80315520
	virtual ~KeyboardConnectedAccessoriesMsg(); // fn_800A7FF4
	virtual void Unk1() = 0;
};

#endif
