#pragma once
#include "ui/UIComponent.h"
#include "ui/UIListCustom.h"

class PlayerDiffIcon : public UIComponent, public UIListCustomTemplate {
public:
    PlayerDiffIcon();
    OBJ_CLASSNAME(PlayerDiffIcon);
    OBJ_SET_TYPE(PlayerDiffIcon);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual ~PlayerDiffIcon();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Update();
    virtual void SetAlphaColor(float, UIColor*);
    virtual void GrowBoundingBox(Box&) const;

    void SetNumPlayersDiff(int, int);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<int> unk110; // 0x110
    int unk118; // 0x118
    int unk11c; // 0x11c
    std::vector<int> unk120; // 0x120
    int mNumPlayers; // 0x128
    int mDiff; // 0x12c
    float unk130; // 0x130
    float unk134; // 0x134
    float unk138; // 0x138
    float unk13c; // 0x13c
    float unk140; // 0x140
};