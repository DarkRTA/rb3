#pragma once
#include "Platform/RootObject.h"
#include "Plugins/Buffer.h"

namespace Quazal {
    class BitStream : public RootObject {
    public:
        BitStream();
        BitStream(Buffer *);
        ~BitStream();

        void AdjustLength();
        void AppendRaw(const unsigned char *, unsigned int);
        void ExtractRaw(unsigned char *, unsigned int);
        void Append(const unsigned char *, unsigned int, unsigned int);
        void Extract(unsigned char *, unsigned int, unsigned int);

        BitStream &operator<<(const Buffer &);
        BitStream &operator>>(Buffer &);
        BitStream &operator>>(BitStream &);

        bool mErrorHasOccurred; // 0x0
        Buffer *mBuffer; // 0x4
        unsigned int mCurrentByteOffset; // 0x8
        unsigned int mCurrentBitShift; // 0xc
        unsigned int mLength; // 0x10
    };
}