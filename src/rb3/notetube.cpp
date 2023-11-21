#include "notetube.hpp"

void fn_803EA800(u32, u8*);

NoteTube::NoteTube() {
	u8* test;
	undef03 = 0;
	undef2 = -1;
	undef3[0] = 0;
	undef4 = -1;
	undef5[0] = 0;
	undef5[1] = 0;
	undef6[0] = 0.0f;
	undef6[1] = 0.0f;
	undef6[2] = 0.0f;
	undef7[0] = 0;
	undef7[1] = 0;
	undef7[2] = 0;
	undef7[3] = 0;
	undef7[4] = 0;
	undef7[5] = 0;
	undef8 = 0.0f;

	fn_803EA800(undef9, test);
	undef10 = 1.0f;
}
