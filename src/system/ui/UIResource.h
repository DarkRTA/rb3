#ifndef UI_UIRESOURCE_H
#define UI_UIRESOURCE_H

#include "utl/FilePath.h"
#include "obj/Dir.h"

// class RndDir : public ObjectDir {int penis;};

class UIResource {
    int mRefCount;
    FilePath mResourcePath;
    // ObjDirPtr<RndDir> mDir;

    UIResource(const FilePath&);
    void Load(bool);
    void PostLoad();
    void Release();
    void ForceRelease();
};

#endif
