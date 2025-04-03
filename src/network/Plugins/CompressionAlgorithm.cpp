#include "network/Plugins/CompressionAlgorithm.h"

namespace Quazal {
    CompressionAlgorithm::CompressionAlgorithm()
        : mCSCompression(0x40000000), m_puCompression("Compression", 0),
          m_puDecompression("Decompression", 0) {
        mUncompressedDataSize = 0;
        mCompressedDataSize = 0;
    }

    CompressionAlgorithm::~CompressionAlgorithm() {}
}