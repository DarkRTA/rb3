#ifndef QUAZAL_STRINGSTREAM_HPP
#define QUAZAL_STRINGSTREAM_HPP
#include "rootobject.hpp"

namespace Quazal {
    class StringStream : RootObject {
    public:
        StringStream();
        ~StringStream();
        void FreeBuffer();
        void ResizeBuffer(unsigned int);

        char *unk0;
        int unk4;
        char *unk8;
        char unk_arr[0x100];
        char unk10c;
        char unk10d;
        char unk10e;
    };
}

#endif