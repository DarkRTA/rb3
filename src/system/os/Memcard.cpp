#include "Memcard.h"
#include "Debug.h"

void Memcard::Init() {
    this->SetName("memcard", ObjectDir::sMainDir);
}

void Memcard::Poll() {
    return;
}

void Memcard::DestroyContainer(MCContainer *pContainer) {
    MILO_ASSERT(pContainer, 0x34);
    MILO_ASSERT(!pContainer->mIsMounted, 0x35);
    if (pContainer != nullptr) {
        delete pContainer;
    }
}

void Memcard::SetContainerDisplayName(const wchar_t *pName) {
    return;
}

void Memcard::SetContainerName(const char *pName) {
    return;
}

MCContainer::~MCContainer() {
    return;
}