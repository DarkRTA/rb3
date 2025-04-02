#pragma once
#include "Platform/CriticalSection.h"
#include "Platform/qStd.h"
#include "Plugins/Buffer.h"
#include "Plugins/Key.h"

namespace Quazal {
    class KeyCache {
    public:
        bool RetrieveKey(unsigned int, const Buffer &, Key *);
        void AddKey(unsigned int, const Buffer &, const Key &);

        qMap<unsigned int, Buffer> mPassword;
        qMap<unsigned int, Key> mKey;
        CriticalSection mKeyCache;
    };
}