#include "network/Extensions/CodecManager.h"

namespace Quazal {
    CodecManager CodecManager::s_oInstance;

    CodecManager::~CodecManager() {}

    bool CodecManager::RegisterCodec(unsigned char key, Codec *val) {
        if (mMapCodec.find(key) == mMapCodec.end()) {
            mMapCodec[key] = val;
            return true;
        } else
            return false;
    }

    Codec *CodecManager::GetCodec(unsigned char key) {
        if (mMapCodec.find(key) != mMapCodec.end()) {
            return mMapCodec[key];
        } else
            return nullptr;
    }

}