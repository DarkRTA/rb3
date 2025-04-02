#pragma once
#include "PluginObject.h"
#include "Plugins/Buffer.h"
#include "Plugins/Key.h"

namespace Quazal {
    class ChecksumAlgorithm : public PluginObject {
    public:
        ChecksumAlgorithm();
        virtual ~ChecksumAlgorithm();
        virtual bool ComputeChecksum(const Buffer &, Buffer *) = 0;
        virtual bool IsReady() const { return true; }
        virtual unsigned int GetChecksumLength() = 0;

        bool AppendChecksum(Buffer *);
        bool RemoveChecksum(Buffer *);
        Key DeriveKey(const Buffer &, unsigned int);
        Key DeriveKey(const char *, unsigned int);

        unsigned char mTransmittedChecksumLength; // 0x8
    };
}