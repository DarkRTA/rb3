#pragma once
#include "obj/Object.h"
#include "math/Key.h"

class FileLoader;

/** "Represents a hue translation for LightPresets" */
class LightHue : public Hmx::Object {
public:
    LightHue();
    virtual ~LightHue();
    OBJ_CLASSNAME(LightHue);
    OBJ_SET_TYPE(LightHue);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);

    void Sync();
    void TranslateColor(const Hmx::Color &, Hmx::Color &);
    DataNode OnSaveDefault(DataArray *);

    DECLARE_REVS

    FileLoader *mLoader; // 0x1c
    FilePath mPath; // 0x20
    Keys<Vector3, Vector3> mKeys; // 0x2c

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(LightHue)
    static void Init() { REGISTER_OBJ_FACTORY(LightHue) }
};
