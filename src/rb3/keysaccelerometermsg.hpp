#ifndef RB3_KEYSACCELEROMETERMSG_HPP
#define RB3_KEYSACCELEROMETERMSG_HPP
#include "message.hpp"

class KeysAccelerometerMsg : Message {
public:
	KeysAccelerometerMsg(int, int, int, int); // fn_803157A8
	virtual ~KeysAccelerometerMsg(); // fn_800A7FF4
};

#endif
