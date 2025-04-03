#pragma once
#include "Platform/CriticalSection.h"
#include "Platform/ProfilingUnit.h"
#include "PluginObject.h"
#include "Plugins/Buffer.h"

namespace Quazal {
    class CompressionAlgorithm : public PluginObject {
    public:
        CompressionAlgorithm();
        virtual ~CompressionAlgorithm();
        virtual bool CompressImpl(const Buffer &, Buffer *) = 0;
        virtual bool DecompressImpl(const Buffer &, Buffer *) = 0;

        unsigned int mUncompressedDataSize; // 0x8
        unsigned int mCompressedDataSize; // 0xc
        CriticalSection mCSCompression; // 0x10
        ProfilingUnit m_puCompression; // 0x28
        ProfilingUnit m_puDecompression; // 0x70
    };
}