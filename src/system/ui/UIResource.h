#ifndef UI_UIRESOURCE_H
#define UI_UIRESOURCE_H

#include "utl/FilePath.h"
#include "rndobj/Dir.h"

// class RndDir : public ObjectDir {int penis;};

class UIResource {
    public:
    int mRefCount; // 0x0
    FilePath mResourcePath; // 0x4
    ObjDirPtr<RndDir> mDir; // 0x10

    UIResource(const FilePath&);
    void Load(bool);
    void PostLoad();
    void Release();
    void ForceRelease();
};

#endif
