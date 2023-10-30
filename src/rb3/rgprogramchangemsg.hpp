#ifndef RB3_RGPROGRAMCHANGEMSG_HPP
#define RB3_RGPROGRAMCHANGEMSG_HPP
#include "message.hpp"

class RGProgramChangeMsg : Message {
public:
	RGProgramChangeMsg(int, int); // fn_80314474
	~RGProgramChangeMsg(); // fn_800A7FF4
};

#endif
