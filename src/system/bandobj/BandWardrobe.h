#pragma once
#include "obj/Object.h"
#include "obj/Dir.h"
#include "char/FileMerger.h"
#include "bandobj/BandCamShot.h"

class BandWardrobe : public virtual Hmx::Object {
public:
    class TargetNames {
    public:
        Symbol names[4];
    };

    BandWardrobe();
    OBJ_CLASSNAME(BandWardrobe);
    OBJ_SET_TYPE(BandWardrobe);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~BandWardrobe();

    Symbol GetPlayMode();
    void SetVenueDir(ObjectDir*);
    void StartVenueShot(BandCamShot*);
    ObjectDir* GetCharacter(int) const;
    void LoadPrefabPrefs();
    void SyncInterestObjects();
    void SetPlayMode(Symbol, BandCamShot*);
    void SyncVignetteInterest(int);
    void SyncEnableBlinks(int);
    void ForceBlink(int);
    class BandCharacter* FindTarget(Symbol, const TargetNames&);

    DataNode OnFindTarget(DataArray*);
    DataNode OnEnterVenue(DataArray*);
    DataNode OnUnloadVenue(DataArray*);
    DataNode OnEnterCloset(DataArray*);
    DataNode OnEnterVignette(DataArray*);
    DataNode OnSelectExtras(DataArray*);
    DataNode OnExtraLoaded(DataArray*);
    DataNode OnListVenueAnimGroups(DataArray*);
    DataNode OnSortTargets(DataArray*);
    DataNode OnGetMatchingDude(DataArray*);
    DataNode OnGetCurrentInterests(DataArray*);
    DataNode OnEnableDebugInterests(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjDirPtr<ObjectDir> unk8; // 0x8
    ObjDirPtr<ObjectDir> unk14; // 0x14
    ObjPtr<FileMerger, ObjectDir> unk20; // 0x20
    std::list<Symbol> unk2c; // 0x2c
    TargetNames unk34; // 0x34
    TargetNames unk44; // 0x44
    TargetNames unk54; // 0x54
    TargetNames* unk64; // 0x64
    int unk68; // 0x68
    int unk6c; // 0x6c
    int unk70; // 0x70
    int unk74; // 0x74
    Symbol unk78; // 0x78
    int unk7c; // 0x7c
    ObjectDir* mVenueDir; // 0x80 - dir
    Symbol mGenre; // 0x84
    Symbol mTempo; // 0x88
    Symbol mVocalGender; // 0x8c
    ObjPtr<Hmx::Object, ObjectDir> unk90; // 0x90
    bool mShotSetPlayMode; // 0x9c
    bool mPlayShot5; // 0x9d
    Symbol mDemandLoad; // 0xa0
    Symbol mPlayerForcedFocuses[4]; // 0xa4
    bool mPlayerEnableBlinks[4]; // 0xb4
};

extern BandWardrobe* TheBandWardrobe;