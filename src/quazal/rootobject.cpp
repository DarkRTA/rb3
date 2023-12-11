#include "rootobject.hpp"
#include "memorymanager.hpp"

void Quazal::RootObject::operator delete(void* v){
    Quazal::MemoryManager::Free(Quazal::MemoryManager::GetDefaultMemoryManager(), v, Quazal::MemoryManager::_InstType3);
}