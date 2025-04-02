#include "network/Plugins/ByteStream.h"
#include "Plugins/Buffer.h"

namespace Quazal {
    ByteStream::ByteStream() : mBuffer(new(__FILE__, 0x17) Buffer(0x400)) {
        mErrorHasOccurred = 0;
        mPosition = 0;
    }

    ByteStream::ByteStream(Buffer *buf) : mBuffer(buf) {
        mBuffer->AcquireRef();
        mErrorHasOccurred = 0;
        mPosition = 0;
    }

    ByteStream::~ByteStream() {
        mBuffer->ReleaseRef();
        mBuffer = nullptr;
    }

    void ByteStream::Clear() {
        mBuffer->Clear();
        mErrorHasOccurred = 0;
        mPosition = 0;
    }

    bool ByteStream::SetLength(unsigned int len) {
        if (len > mBuffer->GetSize()) {
            return false;
        } else {
            mBuffer->SetContentSize(len);
            return true;
        }
    }

    bool ByteStream::AppendRaw(const unsigned char *uc, unsigned int ui) {
        mBuffer->AppendData(uc, ui, -1);
        return true;
    }

    bool ByteStream::ValidateBufferLimit(unsigned int ui) {
        if (mBuffer->mContentSize - mPosition >= ui)
            return true;
        else {
            mErrorHasOccurred = true;
            return false;
        }
    }

    bool ByteStream::SetPosition(unsigned int ui) {
        if (ui > mBuffer->GetContentSize()) {
            return false;
        } else {
            mPosition = ui;
            return true;
        }
    }

    ByteStream &ByteStream::operator<<(const Buffer &buf) {
        mBuffer->AppendData(buf.GetContentPtr(), buf.GetContentSize(), -1);
        return *this;
    }

    ByteStream &ByteStream::operator>>(Buffer &buf) {
        buf.AppendData(
            mBuffer->GetContentPtr() + mPosition,
            mBuffer->GetContentSize() - mPosition,
            -1
        );
        mPosition = mBuffer->GetContentSize();
        return *this;
    }

    ByteStream &ByteStream::operator<<(const bool &b) {
        bool theBool = b;
        mBuffer->AppendData(&theBool, 1, -1);
        return *this;
    }
}