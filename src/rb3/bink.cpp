#include "string.hpp"
#include "textstream.hpp"
#include "binstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "symbol.hpp"
#include "bufstream.hpp"
#include "bufstreamnand.hpp"
#include "idatachunk.hpp"
#include "cacheid.hpp"
#include "cacheidwii.hpp"

#pragma dont_inline on
unsigned int ReverseByte(unsigned int* ui, unsigned int lol){
	// loads byte ui in reverse endian order
	asm{ lwbrx r3, r4, r3 }
}
#pragma dont_inline reset

// fn_80341EDC
void intelendian(void* v, unsigned int ui){
	unsigned int u2;
	unsigned int* uv = (unsigned int*)v;

	u2 = ui + 3 >> 2U;
	while(!(u2-- == 0)) *uv++ = ReverseByte(uv, 0);
}

// fn_803422B4
long long SwapDataDoubleWord(long long lol){

}
