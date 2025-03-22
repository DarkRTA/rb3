#pragma once
#include "utl/Loader.h"
#include "obj/Object.h"
#include "obj/Dir.h"

class DirUnloader : public Loader, public Hmx::Object {
public:
    DirUnloader(ObjectDir *);
    virtual ~DirUnloader();
    virtual const char *DebugText();
    virtual bool IsLoaded() const;
    virtual void PollLoading();

    std::vector<ObjPtr<Hmx::Object> > mObjects; // 0x34
};
