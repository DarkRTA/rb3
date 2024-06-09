#ifndef OBJ_DIRUNLOADER_H
#define OBJ_DIRUNLOADER_H
#include "utl/Loader.h"
#include "obj/Object.h"
#include "obj/Dir.h"

class DirUnloader : public Loader, public Hmx::Object {
public:
    DirUnloader(ObjectDir*);
    virtual ~DirUnloader();
    virtual const char* DebugText();
    virtual bool IsLoaded() const { return false; }
    virtual void PollLoading();

    std::vector<ObjPtr<Hmx::Object, ObjectDir> > mObjects; // 0x34
};

#endif
