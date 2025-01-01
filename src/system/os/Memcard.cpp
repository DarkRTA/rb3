#include "Memcard.h"
#include "Debug.h"
#include "decomp.h"

void Memcard::Init() {
    this->SetName("memcard", ObjectDir::sMainDir);
}

void Memcard::Poll() {
    return;
}

void Memcard::ShowDeviceSelector(const ContainerId&, bool, Hmx::Object*, int) {

}

bool Memcard::IsDeviceValid(const ContainerId&) { return true; }

void Memcard::DestroyContainer(MCContainer *pContainer) {
    MILO_ASSERT(pContainer, 0x34);
    MILO_ASSERT(!pContainer->IsMounted(), 0x35);
    delete pContainer;
}

MCContainer::~MCContainer() {}

void MCContainer::DestroyMCFile(MCFile* pFile) {
    MILO_ASSERT(pFile, 69);
    if (pFile->IsOpen()) pFile->Close();
    delete pFile;
}

String MCContainer::BuildPath(const char* pPath) {
    return pPath;
}
