#pragma once
#include "ui/UIComponent.h"
#include "ui/UIListCustom.h"
#include "bandobj/BandLabel.h"

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

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(PlayerDiffIcon);
    }
    NEW_OBJ(PlayerDiffIcon);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<RndMesh*> mPlayerMeshes; // 0x110
    RndMat* mPlayerMat; // 0x118
    RndMat* mNoPlayerMat; // 0x11c
    std::vector<BandLabel*> mDiffLabels; // 0x120
    int mNumPlayers; // 0x128
    int mDiff; // 0x12c
    float mAlpha; // 0x130
    Hmx::Color mColor; // 0x134
};