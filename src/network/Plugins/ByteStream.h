#pragma once
#include "Platform/RootObject.h"
#include "Plugins/Buffer.h"

namespace Quazal {
    class ByteStream : public RootObject {
    public:
        ByteStream();
        ByteStream(Buffer *);
        ~ByteStream();

        void Clear();
        bool SetLength(unsigned int);
        bool AppendRaw(const unsigned char *, unsigned int);
        bool ValidateBufferLimit(unsigned int);
        bool SetPosition(unsigned int);
        bool Append(const unsigned char *, unsigned int, unsigned int);
        bool Extract(unsigned char *, unsigned int, unsigned int);

        ByteStream &operator<<(const Buffer &);
        ByteStream &operator>>(Buffer &);
        ByteStream &operator<<(const bool &);
        ByteStream &operator>>(bool &);

        bool mErrorHasOccurred; // 0x0
        Buffer *mBuffer; // 0x4
        unsigned int mPosition; // 0x8
    };
}