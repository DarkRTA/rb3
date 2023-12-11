#include "rootobject.hpp"
#include "memorymanager.hpp"

void* Quazal::RootObject::operator new(unsigned long ul, const char* cc, unsigned int ui){
    Quazal::MemoryManager::Allocate(Quazal::MemoryManager::GetDefaultMemoryManager(), ul, cc, ui, Quazal::MemoryManager::_InstType3);
}

void* Quazal::RootObject::operator new[](unsigned long ul, const char* cc, unsigned int ui){
    Quazal::MemoryManager::Allocate(Quazal::MemoryManager::GetDefaultMemoryManager(), ul, cc, ui, Quazal::MemoryManager::_InstType4);
}

void Quazal::RootObject::operator delete(void* v){
    Quazal::MemoryManager::Free(Quazal::MemoryManager::GetDefaultMemoryManager(), v, Quazal::MemoryManager::_InstType3);
}

void Quazal::RootObject::operator delete[](void* v){
    Quazal::MemoryManager::Free(Quazal::MemoryManager::GetDefaultMemoryManager(), v, Quazal::MemoryManager::_InstType4);
}