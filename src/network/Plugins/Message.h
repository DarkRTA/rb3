#pragma once
#include "EndPoint.h"
#include "Platform/Result.h"
#include "Platform/Time.h"
#include "Plugins/Buffer.h"
#include "Plugins/ByteStream.h"

namespace Quazal {
    class Message : public ByteStream {
    public:
        Message();
        Message(Buffer *);
        ~Message();

        void SetSourceEndPoint(EndPoint *);
        void SetToBegining();
        bool IsValid();
        void SetIOTime(Time &);
        Time GetIOTime();
        void Clear();
        Buffer *GetBuffer();
        unsigned int GetHeaderSize() const;
        unsigned int GetSize();
        unsigned int GetPayloadSize() const;
        qResult GetLastError();
        void AddDataFromMessage(const Message &);
        Message &AppendMessage(Message &);
        Message &ExtractMessage(Message &);

        qResult mLastError; // 0xc
        Time mIOTime; // 0x18
        int unk20; // 0x20
        int unk24; // 0x24
        int unk28; // 0x28
        EndPoint *mSourceEndPoint; // 0x2c
    };
}