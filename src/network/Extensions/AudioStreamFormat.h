#pragma once
#include "Platform/RootObject.h"

namespace Quazal {

    class _DDL_AudioStreamFormat : public RootObject {
    public:
        _DDL_AudioStreamFormat() {}
        virtual ~_DDL_AudioStreamFormat() {}

        unsigned int mNbSamplesPerPacket; // 0x4
        unsigned int mNbChannels; // 0x8
        unsigned int mNbSamplesPerSec; // 0xc
        unsigned int mNbBitsPerSample; // 0x10
    };

    class AudioStreamFormat : public _DDL_AudioStreamFormat {
    public:
        AudioStreamFormat() { Init(8000, 1, 8000, 16); }
        virtual ~AudioStreamFormat() {}

        void Init(unsigned int u1, unsigned int u2, unsigned int u3, unsigned int u4) {
            mNbSamplesPerPacket = u1;
            mNbChannels = u2;
            mNbSamplesPerSec = u3;
            mNbBitsPerSample = u4;
        }
    };
}