#ifndef RB3_RGACCELEROMETERMSG_HPP
#define RB3_RGACCELEROMETERMSG_HPP
#include "message.hpp"

class RGAccelerometerMsg : Message {
public:
	RGAccelerometerMsg(int, int, int, int); // fn_80313FFC
	virtual ~RGAccelerometerMsg(); // fn_800A7FF4
};

#endif
