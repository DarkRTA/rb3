#ifndef WORLD_LIGHTHUE_H
#define WORLD_LIGHTHUE_H
#include "obj/Object.h"
#include "utl/Key.h"

class FileLoader;

class LightHue : public Hmx::Object {
public:
    LightHue();
    virtual ~LightHue();
    OBJ_CLASSNAME(LightHue);
    OBJ_SET_TYPE(LightHue);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    void Sync();

    DECLARE_REVS;

    FileLoader* mLoader;
    FilePath mPath;
    Keys<Vector3, Vector3> mKeys;

};

#endif
