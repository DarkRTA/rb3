#pragma once
#include "Extensions/Codec.h"
#include "Platform/RootObject.h"
#include "Platform/qStd.h"

namespace Quazal {
    class CodecManager : public RootObject {
    public:
        CodecManager() {}
        ~CodecManager();

        bool RegisterCodec(unsigned char, Codec *);
        Codec *GetCodec(unsigned char);

        static CodecManager s_oInstance;

        qMap<unsigned char, Codec *> mMapCodec;
    };
}