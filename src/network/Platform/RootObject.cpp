#include "Platform/RootObject.h"
#include "Platform/MemoryManager.h"

namespace Quazal {

    void* RootObject::operator new(unsigned long ul){
        MemoryManager::Allocate(
            MemoryManager::GetDefaultMemoryManager(), 
            ul, "Unknown", 0, 
            MemoryManager::_InstType3);
    }

    void* RootObject::operator new(unsigned long ul, const char *cc, unsigned int ui) {
        MemoryManager::Allocate(
            MemoryManager::GetDefaultMemoryManager(),
            ul, cc, ui,
            MemoryManager::_InstType3);
    }

    void* RootObject::operator new[](unsigned long ul) {
        MemoryManager::Allocate(
            MemoryManager::GetDefaultMemoryManager(),
            ul, "Unknown", 0,
            MemoryManager::_InstType4);
    }

    void* RootObject::operator new[](unsigned long ul, const char *cc, unsigned int ui) {
        MemoryManager::Allocate(
            MemoryManager::GetDefaultMemoryManager(),
            ul, cc, ui,
            MemoryManager::_InstType4);
    }

    void RootObject::operator delete(void *v) {
        MemoryManager::Free(
            MemoryManager::GetDefaultMemoryManager(),
            v, MemoryManager::_InstType3);
    }

    void RootObject::operator delete[](void *v) {
        MemoryManager::Free(
            MemoryManager::GetDefaultMemoryManager(),
            v, MemoryManager::_InstType4);
    }

}
