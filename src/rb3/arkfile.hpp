#ifndef _ARKFILE_HPP
#define _ARKFILE_HPP
#include <types.h>
class ArkFile {
public:
//	void fn_802E7500(s32 param_1, u32 param_2); // big headache. baaad.
	u32 fn_802E76D8_stub();
	u32 Seek(int offset, int mode);
	u32 FilePos(void);
	bool EndOfFile(void);
	u8 unkBlock1[16];
	u32 filesize;
	u8 unkBlock2[12];
	u32 fpos;
};
#endif
