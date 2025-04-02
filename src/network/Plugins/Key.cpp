#include "network/Plugins/Key.h"

namespace Quazal {
    Key::Key() {}

    Key::~Key() {}

    Key &Key::operator=(const Key &key) {
        mData = key.mData;
        return *this;
    }

    int Key::GetLength() const { return mData.size(); }

    const unsigned char *Key::GetContentPtr() const {
        if (mData.empty())
            return nullptr;
        else
            return &mData.front();
    }

    void Key::PrepareContentPtr(unsigned int size) { mData.resize(size); }
}