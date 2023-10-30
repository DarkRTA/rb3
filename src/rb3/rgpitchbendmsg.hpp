#ifndef RB3_RGPITCHBENDMSG_HPP
#define RB3_RGPITCHBENDMSG_HPP
#include "message.hpp"

class RGPitchBendMsg : Message {
public:
	RGPitchBendMsg(int, int); // fn_803141EC
	~RGPitchBendMsg(); // fn_800A7FF4
};

#endif
