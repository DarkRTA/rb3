#pragma once
#include "Platform/RefCountedObject.h"
#include "Platform/qStd.h"

namespace Quazal {
    class Key : public RefCountedObject {
    public:
        Key();
        Key(unsigned char *, unsigned int);
        Key(const Key &);
        virtual ~Key();

        Key &operator=(const Key &);
        int GetLength() const;
        const unsigned char *GetContentPtr() const;
        void PrepareContentPtr(unsigned int);

        qVector<unsigned char> mData;
    };
}