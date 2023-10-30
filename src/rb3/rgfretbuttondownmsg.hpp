#ifndef RB3_RGFRETBUTTONDOWNMSG_HPP
#define RB3_RGFRETBUTTONDOWNMSG_HPP
#include "message.hpp"

class RGFretButtonDownMsg : Message {
public:
	RGFretButtonDownMsg(int, int, int); // fn_80314624
	~RGFretButtonDownMsg(); // fn_800A7FF4
};

#endif
