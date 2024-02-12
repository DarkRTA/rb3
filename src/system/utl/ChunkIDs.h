#ifndef UTL_CHUNKIDS_H
#define UTL_CHUNKIDS_H
#include <string.h>

class ChunkID {
public:
    char mStr[4];
    ChunkID(const char* str){
        memcpy(mStr, str, 4);
    }
};

#endif
