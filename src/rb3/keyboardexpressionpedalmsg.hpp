#ifndef RB3_KEYBOARDEXPRESSIONPEDALMSG_HPP
#define RB3_KEYBOARDEXPRESSIONPEDALMSG_HPP
#include "message.hpp"

class KeyboardExpressionPedalMsg : Message {
public:
	KeyboardExpressionPedalMsg(int, int); // fn_80315448
	virtual ~KeyboardExpressionPedalMsg(); // fn_800A7FF4
};

#endif
