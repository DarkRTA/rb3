#include "network/Plugins/KeyedChecksumAlgorithm.h"

namespace Quazal {
    KeyedChecksumAlgorithm::KeyedChecksumAlgorithm(unsigned int ui1, unsigned int ui2)
        : mMinKeyLength(ui1), mMaxKeyLength(ui2) {}
    KeyedChecksumAlgorithm::~KeyedChecksumAlgorithm() {}

    bool KeyedChecksumAlgorithm::SetKey(const Key &key) {
        if (key.GetLength() >= mMinKeyLength && key.GetLength() <= mMaxKeyLength) {
            mChecksum = key;
            KeyHasChanged();
            return true;

        } else {
            return false;
        }
    }
}