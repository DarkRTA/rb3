#include "network/Plugins/JobDeriveKey.h"
#include "Platform/String.h"

namespace Quazal {
    JobDeriveKey::JobDeriveKey(
        unsigned int ui1,
        ChecksumAlgorithm *ca,
        const Buffer *buf,
        unsigned int ui4,
        Key *key
    )
        : Job(DebugString()), unk34(ui1), unk38(ca), unk50(0), unk54(ui4), unk58(key) {
        unk3c = *buf;
        unk70 = 0;
        unk5c = *buf;
    }

    JobDeriveKey::~JobDeriveKey() { delete unk38; }
}