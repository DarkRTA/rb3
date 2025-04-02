#include "network/Plugins/Buffer.h"
#include "Platform/MemoryManager.h"

namespace Quazal {
    Buffer::Buffer(unsigned int ui) : mContentSize(0), mBufSize(ui) {
        mData =
            (unsigned char *)MemoryManager::Allocate(mBufSize, MemoryManager::_InstType1);
    }

    Buffer::~Buffer() { QUAZAL_DEFAULT_FREE(mData, _InstType1); }
}