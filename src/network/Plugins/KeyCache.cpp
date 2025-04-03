#include "network/Plugins/KeyCache.h"
#include "Platform/ScopedCS.h"

namespace Quazal {
    bool KeyCache::RetrieveKey(unsigned int ui, const Buffer &buf, Key *key) {
        ScopedCS cs(mKeyCache);
        qMap<unsigned int, Buffer>::const_iterator it = mPassword.find(ui);
        if (it != mPassword.end() && it->second == buf) {
            *key = mKey.find(ui)->second;
            return true;
        } else
            return false;
    }

    void KeyCache::AddKey(unsigned int ui, const Buffer &buf, const Key &key) {
        ScopedCS cs(mKeyCache);
        mPassword[ui] = buf;
        mKey[ui] = key;
    }
}