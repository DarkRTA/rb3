#include "memorymanager.hpp"
#include "watermark.hpp"
#include "mutexprimitive.hpp"

Quazal::MemoryManager::MemoryManager(char *c) {
    unk4 = c;
    unk8 = 0;
    unkc = 0;
    unk10 = 0;
    unk14 = 0;
    unk18 = 0;
    unk18 = new ("MemoryManager.cpp", 0x7E) MutexPrimitive();
    unk14 = new ("MemoryManager.cpp", 0x80) WaterMark(c, true, 60000);
}

Quazal::MemoryManager::~MemoryManager() {
}

int Quazal::MemoryManager::GetHeaderSize() {
    if (s_uiHeaderSize == 0)
        s_uiHeaderSize = 4;
    return s_uiHeaderSize;
}

Quazal::MemoryManager *Quazal::MemoryManager::GetDefaultMemoryManager() {
    return 0;
}