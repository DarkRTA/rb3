#pragma once
#include "Platform/RefCountedObject.h"

namespace Quazal {
    class Buffer : public RefCountedObject {
    public:
        Buffer(unsigned int);
        Buffer(const Buffer &);
        virtual ~Buffer();

        unsigned int GetContentSize() const;
        bool AppendData(const void *, unsigned int, unsigned int);
        bool CopyContent(void *, unsigned int, unsigned int) const;
        void Clear();
        unsigned char &operator[](unsigned int);
        Buffer &operator=(const Buffer &);
        Buffer &operator+=(const Buffer &);
        bool operator==(const Buffer &) const;
        unsigned char *GetContentPtr() const;
        void SetContentSize(unsigned int);
        unsigned int GetSize() const;
        void Resize(unsigned int);

        unsigned char *mData; // 0x8
        unsigned int mContentSize; // 0xc
        unsigned int mBufSize; // 0x10
    };
}