#include <types.h>
class ArkFile {
public:
    u32 Seek(int offset, int mode);
    u32 FilePos(void);
    u8 unkBlock1[16];
    u32 filesize;
    u8 unkBlock2[12];
    u32 fpos;
};
