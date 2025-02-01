#include "Memcard.h"
#include "Debug.h"
#include "decomp.h"

void Memcard::Init() { SetName("memcard", ObjectDir::sMainDir); }

void Memcard::Poll() {}

void Memcard::ShowDeviceSelector(const ContainerId &, bool, Hmx::Object *o, int) {
    if (o)
        o->Handle(DeviceChosenMsg(-1), false);
}

bool Memcard::IsDeviceValid(const ContainerId &) { return true; }

void Memcard::DestroyContainer(MCContainer *pContainer) {
    MILO_ASSERT(pContainer, 0x34);
    MILO_ASSERT(!pContainer->IsMounted(), 0x35);
    delete pContainer;
}

void MCContainer::DestroyMCFile(MCFile *pFile) {
    MILO_ASSERT(pFile, 69);
    if (pFile->IsOpen())
        pFile->Close();
    delete pFile;
}

String MCContainer::BuildPath(const char *pPath) { return pPath; }
