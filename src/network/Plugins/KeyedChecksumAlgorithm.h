#pragma once
#include "Plugins/ChecksumAlgorithm.h"
#include "Plugins/Key.h"

namespace Quazal {
    class KeyedChecksumAlgorithm : public ChecksumAlgorithm {
    public:
        KeyedChecksumAlgorithm(unsigned int, unsigned int);
        virtual ~KeyedChecksumAlgorithm();
        virtual bool ComputeChecksum(const Buffer &, Buffer *) = 0;
        virtual bool IsReady() const {
            return mChecksum.GetLength() >= mMinKeyLength
                && mChecksum.GetLength() <= mMaxKeyLength;
        }
        virtual unsigned int GetChecksumLength() = 0;
        virtual void KeyHasChanged() {}

        bool SetKey(const Key &);

        Key mChecksum; // 0xc
        unsigned int mMinKeyLength; // 0x1c
        unsigned int mMaxKeyLength; // 0x20
    };
}