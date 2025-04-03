#pragma once
#include "Plugins/ChecksumAlgorithm.h"

namespace Quazal {
    class MD5Checksum : public ChecksumAlgorithm {
    public:
        MD5Checksum();
        virtual ~MD5Checksum();
        virtual bool ComputeChecksum(const Buffer &, Buffer *);
        virtual unsigned int GetChecksumLength();
    };
}