#pragma once
#include "Core/Job.h"
#include "Plugins/ChecksumAlgorithm.h"
#include "Plugins/KeyCache.h"

namespace Quazal {
    class JobDeriveKey : public Job {
    public:
        JobDeriveKey(unsigned int, ChecksumAlgorithm *, const Buffer *, unsigned int, Key *);
        virtual ~JobDeriveKey();
        virtual void Execute();

        unsigned int unk34;
        ChecksumAlgorithm *unk38;
        Buffer unk3c;
        int unk50;
        unsigned int unk54;
        Key *unk58;
        Buffer unk5c;
        KeyCache *unk70;
    };
}