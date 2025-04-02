#include "network/Plugins/ChecksumAlgorithm.h"
#include "Plugins/Buffer.h"

namespace Quazal {
    ChecksumAlgorithm::ChecksumAlgorithm() : mTransmittedChecksumLength(0) {}
    ChecksumAlgorithm::~ChecksumAlgorithm() {}

    bool ChecksumAlgorithm::AppendChecksum(Buffer *buf) {
        if (!IsReady())
            return false;
        else {
            if (mTransmittedChecksumLength == 0) {
                mTransmittedChecksumLength = GetChecksumLength();
            }
            Buffer buffer((unsigned char)GetChecksumLength());
            ComputeChecksum(*buf, &buffer);
            unsigned int it = mTransmittedChecksumLength;
            if (it < (unsigned char)GetChecksumLength()) {
                unsigned char len = GetChecksumLength();
                for (; it < len; it++) {
                    buffer[mTransmittedChecksumLength - 1] ^= buffer[it];
                }
                buffer.SetContentSize(mTransmittedChecksumLength);
            }
            buf->AppendData(buffer.GetContentPtr(), buffer.GetContentSize(), -1);
            return true;
        }
    }

    bool ChecksumAlgorithm::RemoveChecksum(Buffer *buf) {
        if (!IsReady())
            return false;
        else {
            if (mTransmittedChecksumLength == 0) {
                mTransmittedChecksumLength = GetChecksumLength();
            }
            if (buf->GetContentSize() < mTransmittedChecksumLength) {
                return false;
            } else {
                Buffer buffer(0x400);
                buf->SetContentSize(buf->GetContentSize() - mTransmittedChecksumLength);
                buffer.AppendData(
                    buf->GetContentPtr() + buf->GetContentSize(),
                    mTransmittedChecksumLength,
                    -1
                );
                Buffer buf38((unsigned char)GetChecksumLength());
                ComputeChecksum(*buf, &buf38);
                unsigned int it = mTransmittedChecksumLength;
                if (it < (unsigned char)GetChecksumLength()) {
                    unsigned char len = GetChecksumLength();
                    for (; it < len; it++) {
                        buf38[mTransmittedChecksumLength - 1] ^= buf38[it];
                    }
                    buf38.SetContentSize(mTransmittedChecksumLength);
                }
                if (buffer == buf38)
                    return true;
                else
                    return false;
            }
        }
    }

    Key ChecksumAlgorithm::DeriveKey(const Buffer &buf, unsigned int ui) {
        Buffer buf24(buf);
        uint i = 0;
        Buffer buf38((unsigned char)GetChecksumLength());
        for (; i < ui; i++) {
            buf38.Clear();
            ComputeChecksum(buf24, &buf38);
            buf24 = buf38;
        }
        return Key(buf24.GetContentPtr(), buf24.GetContentSize());
    }

    Key ChecksumAlgorithm::DeriveKey(const char *cc, unsigned int ui) {
        Buffer buf28(0x400);
        buf28.AppendData(cc, strlen(cc), -1);
        return DeriveKey(buf28, ui);
    }
}