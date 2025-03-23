#pragma once
#include "bandobj/PatchDir.h"
#include "meta_band/BandProfile.h"
#include "meta_band/EditSetlistPanel.h"
#include "obj/Object.h"
#include "rndobj/Mat.h"
#include "ui/UIGridProvider.h"
#include "ui/UIList.h"
#include "ui/UIListProvider.h"
#include "ui/UIPanel.h"
#include "utl/Std.h"

class PatchProvider : public UIListProvider, public Hmx::Object {
public:
    PatchProvider(std::vector<PatchDir *> &patches) : mPatches(patches), mEmptyMat(0) {}
    virtual ~PatchProvider() { DeleteAll(unk24); }
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual int NumData() const;
    virtual void InitData(RndDir *);

    PatchDir *GetPatchDir(int) const;
    bool HasAnyPatches() const;

    std::vector<PatchDir *> &mPatches; // 0x20
    std::vector<RndMat *> unk24; // 0x24
    RndMat *mEmptyMat; // 0x2c
};

class PatchSelectPanel : public UIPanel {
public:
    PatchSelectPanel();
    OBJ_CLASSNAME(PatchSelectPanel);
    OBJ_SET_TYPE(PatchSelectPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~PatchSelectPanel() {}
    virtual void Draw();
    virtual void Enter();
    virtual void Load();
    virtual void Unload();
    virtual void FinishLoad();
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    int DuplicatePatch(PatchDir *);
    void SetupForBandLogo(BandProfile *);
    void SetDescriptor(PatchDescriptor *);
    void SetupForSetlistArt(EditSetlistPanel *, BandProfile *);
    void SetupForCharacterPatch();
    void Confirm(int);

    PatchProvider *mPatchProvider; // 0x38
    UIGridProvider *mGridProvider; // 0x3c
    UIList *mPatchList; // 0x40
    PatchDescriptor *mDescriptor; // 0x44
    BandProfile *mSourceProfile; // 0x48
    int mStartingPatchIx; // 0x4c
    bool mStartWithMenu; // 0x50
};