#pragma once
#include "Plugins/CompressionAlgorithm.h"

namespace Quazal {
    class ZLibCompression : public CompressionAlgorithm {
    public:
        ZLibCompression();
        virtual ~ZLibCompression();
        virtual bool CompressImpl(const Buffer &, Buffer *);
        virtual bool DecompressImpl(const Buffer &, Buffer *);

        int unkb8;
    };
}