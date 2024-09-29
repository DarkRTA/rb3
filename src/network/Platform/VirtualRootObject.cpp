#include "Platform/VirtualRootObject.h"
#include "Platform/MemoryManager.h"

namespace Quazal {

    void *VirtualRootObject::operator new(unsigned long ul, char *cc, unsigned int ui) {
        return MemoryManager::Allocate(
            MemoryManager::GetDefaultMemoryManager(), ul, cc, ui, MemoryManager::_InstType3
        );
    }

    void VirtualRootObject::operator delete(void *v) {
        MemoryManager::Free(
            MemoryManager::GetDefaultMemoryManager(), v, MemoryManager::_InstType3
        );
    }

}
