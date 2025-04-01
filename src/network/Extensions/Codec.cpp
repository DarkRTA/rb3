#include "network/Extensions/Codec.h"

namespace Quazal {
    Codec::Codec() {}
    Codec::~Codec() {}

    float Codec::GetCompressionRatio() {
        return (float)(GetNbSamplesPerFrame() * 2) / (float)GetNbBytesPerEncodedFrame();
    }
}