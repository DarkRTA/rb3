#pragma once
#include "ui/UIList.h"
#include "world/ColorPalette.h"

class BandSwatch : public UIList {
public:
    BandSwatch();
    OBJ_CLASSNAME(BandSwatch)
    OBJ_SET_TYPE(BandSwatch)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~BandSwatch();
    virtual void PreLoad(BinStream&);
    virtual void Enter();
    virtual int NumData() const;
    virtual RndMat* Mat(int, int, UIListMesh*) const;
    virtual UIColor* SlotColorOverride(int, int, class UIListWidget*, UIColor* c) const;

    void UpdateColors();
    void SetColors(ColorPalette*);

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(BandSwatch);
    }
    NEW_OBJ(BandSwatch);
    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    static void Terminate();
    static ColorPalette* sDummyPalette;

    std::vector<UIColor*> unk1e8; // 0x1e8
    ObjPtr<ColorPalette, ObjectDir> mColorPalette; // 0x1f0
};