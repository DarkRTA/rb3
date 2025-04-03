#include "network/Plugins/Message.h"
#include "EndPoint.h"
#include "Platform/Result.h"
#include "Plugins/Buffer.h"
#include "Plugins/ByteStream.h"

namespace Quazal {
    Message::Message() : unk28(0) {
        unk20 = 0;
        unk24 = 0;
        mSourceEndPoint = 0;
        Clear();
        mIOTime = 0;
        SetLength(4);
        int size = mBuffer->GetContentSize();
        SetLength(0);
        int write = size - 4;
        Append((unsigned char *)&write, 4, 1);
        SetLength(size);
        SetPosition(4);
        mLastError = qResult(0x10001);
        SetPosition(4);
    }

    Message::Message(Buffer *buf) : ByteStream(buf), unk28(0) {
        unk20 = 0;
        unk24 = 0;
        mSourceEndPoint = 0;
        mIOTime = 0;
        mLastError = qResult(0x10001);
        SetPosition(4);
    }

    Message::~Message() {
        if (mSourceEndPoint)
            mSourceEndPoint->Close();
    }

    void Message::SetSourceEndPoint(EndPoint *point) {
        if (point) {
            mSourceEndPoint = point;
            mSourceEndPoint->Open();
        }
    }

    void Message::SetToBegining() {
        mLastError = qResult(0x10001);
        SetPosition(4);
    }

    bool Message::IsValid() {
        int i1 = mBuffer->GetContentSize();
        int i2 = mBuffer->GetContentSize();
        SetLength(0);
        int i14 = i2 - 4;
        Append((unsigned char *)&i14, 4, 1);
        SetLength(i2);
        i2 = mPosition;
        SetPosition(0);
        int extracted;
        Extract((unsigned char *)&extracted, 4, 1);
        SetPosition(i2);
        return extracted == i1 - 4;
    }

    void Message::SetIOTime(Time &time) { mIOTime = time; }
    Time Message::GetIOTime() { return mIOTime; }

    void Message::Clear() {
        ByteStream::Clear();
        mIOTime = 0;
        SetLength(4);
        unsigned int size = mBuffer->GetContentSize();
        SetLength(0);
        unsigned int write = size - 4;
        Append((unsigned char *)&write, 4, 1);
        SetLength(size);
        SetPosition(4);
    }

    Buffer *Message::GetBuffer() {
        unsigned int size = mBuffer->GetContentSize();
        SetLength(0);
        unsigned int write = size - 4;
        Append((unsigned char *)&write, 4, 1);
        SetLength(size);
        return mBuffer;
    }

    unsigned int Message::GetHeaderSize() const { return 4; }

    unsigned int Message::GetSize() {
        unsigned int size = mBuffer->GetContentSize();
        SetLength(0);
        unsigned int read;
        unsigned int write = size - 4;
        Append((unsigned char *)&write, 4, 1);
        SetLength(size);
        unsigned int pos = mPosition;
        SetPosition(0);
        Extract((unsigned char *)&read, 4, 1);
        SetPosition(pos);
        return read;
    }

    unsigned int Message::GetPayloadSize() const { return mBuffer->GetContentSize() - 4; }

    qResult Message::GetLastError() {
        if (mErrorHasOccurred) {
            mLastError = qResult(0x8001000F);
        }
        return mLastError;
    }

    void Message::AddDataFromMessage(const Message &msg) {
        AppendRaw(msg.mBuffer->GetContentPtr() + 4, msg.mBuffer->GetContentSize() - 4);
    }

    Message &Message::AppendMessage(Message &msg) {
        unsigned int u1 = msg.mBuffer->GetContentSize();
        msg.SetLength(0);
        unsigned int write2;
        unsigned int write1 = u1 - 4;
        msg.Append((unsigned char *)&write1, 4, 1);
        msg.SetLength(u1);

        Buffer *msgBuf = msg.mBuffer;
        u1 = msg.mBuffer->GetContentSize();
        msg.SetLength(0);
        write2 = u1 - 4;
        msg.Append((unsigned char *)&write2, 4, 1);
        msg.SetLength(u1);

        Buffer *msgBuf0 = msg.mBuffer;
        AppendRaw(msgBuf0->GetContentPtr(), msgBuf->GetContentSize());
        return *this;
    }

    Message &Message::ExtractMessage(Message &msg) {
        unsigned int i14;
        Extract((unsigned char *)&i14, 4, 1);
        unsigned int pos = mPosition;
        unsigned int u1 = mBuffer->GetContentSize();
        SetLength(0);
        unsigned int write = u1 - 4;
        Append((unsigned char *)&write, 4, 1);
        SetLength(u1);
        msg.AppendRaw(mBuffer->GetContentPtr() + pos, i14);
        SetPosition(i14 + mPosition);
        return *this;
    }
}