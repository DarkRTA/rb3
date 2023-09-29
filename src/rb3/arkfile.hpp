#ifndef _ARKFILE_HPP
#define _ARKFILE_HPP
#include <types.h>
class ArkFile {
public:
//	void fn_802E7500(s32 param_1, u32 param_2); // big headache. baaad.
	u32 ReturnsZero(); // 0x802E76D8; marked to be labeled as fn_802E76D8_ret0 in syms.txt... but it's already labeled as ReturnsZero
	u32 Seek(int offset, int mode);
	u32 FilePos(void);
	bool EndOfFile(void);
	u8 unkBlock1[16];
	u32 filesize;
	u8 unkBlock2[12];
	u32 fpos;
};
#endif
