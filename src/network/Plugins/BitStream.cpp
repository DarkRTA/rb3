#include "network/Plugins/BitStream.h"
#include "Plugins/Buffer.h"

namespace Quazal {
    BitStream::BitStream() : mBuffer(new(__FILE__, 0x15) Buffer(0x400)) {
        mErrorHasOccurred = 0;
        mLength = 0;
        mCurrentByteOffset = 0;
        mCurrentBitShift = 7;
    }

    BitStream::BitStream(Buffer *buf) : mBuffer(buf) {
        mBuffer->AcquireRef();
        mErrorHasOccurred = 0;
        mLength = 0;
        mCurrentByteOffset = 0;
        mCurrentBitShift = 7;
        mLength = mBuffer->GetContentSize() * 8;
    }

    BitStream::~BitStream() {
        mBuffer->ReleaseRef();
        mBuffer = nullptr;
    }

    void BitStream::AdjustLength() { mLength = mBuffer->GetContentSize() * 8; }

    void BitStream::Append(const unsigned char *uc, unsigned int ui2, unsigned int ui3) {
        for (int i = 0; i < ui3; i++) {
            int i1 = ui2 - 1;
            for (; i1 >= 0; i1--) {
                AppendRaw(&uc[i1 + ui2], 8);
            }
        }
    }

    BitStream &BitStream::operator<<(const Buffer &buf) {
        unsigned char *uchars;
        int size = buf.GetContentSize();
        for (int i = 3; i >= 0; i--) {
            AppendRaw(&uchars[i], 8);
        }
        if (buf.GetContentSize()) {
            int size = buf.GetContentSize();
            AppendRaw(buf.GetContentPtr(), size * 8);
        }
        return *this;
    }
}