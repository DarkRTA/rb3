#ifndef RB3_NOTETUBE_HPP
#define RB3_NOTETUBE_HPP
#include "hmx/object.hpp"
#include "types.h"

class NoteTube : Hmx::Object { // 0x64
	NoteTube();
	virtual ~NoteTube();

	u8 undef0[20];
	u32 undef02;
	u8 undef03;
	u8 undef04[3];
	u32 undef2;
	u8 undef3[4];
	u32 undef4;
	u8 undef5[4];
	float undef6[3];
	u32 undef7[6];
	float undef8;
	u32 undef9;
	u32 undef010;
	float undef10;
};

#endif
