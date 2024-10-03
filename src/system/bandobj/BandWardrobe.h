#pragma once
#include "obj/Object.h"
#include "obj/Dir.h"
#include "char/FileMerger.h"
#include "bandobj/BandCamShot.h"
#include "bandobj/BandCharacter.h"
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandDirector.h"

class BandWardrobe : public virtual Hmx::Object {
public:
    class TargetNames {
    public:
        int FindTarget(Symbol) const;

        Symbol names[4];
    };

    class SlotInfo {
    public:
        bool human; // 0x0
        float score; // 0x4
        Symbol inst; // 0x8
        int hint; // 0xc
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

    int GetShotFlags(CamShot*);
    Symbol GetCoopMode(BandCamShot*);
    Symbol GetPlayMode();
    void SetVenueDir(ObjectDir*);
    void StartVenueShot(BandCamShot*);
    BandCharacter* GetCharacter(int) const;
    void LoadPrefabPrefs();
    void SyncInterestObjects();
    void SetPlayMode(Symbol, BandCamShot*);
    void SyncVignetteInterest(int);
    void SyncEnableBlinks(int);
    void ForceBlink(int);
    void SetDir(ObjectDir*);
    void SyncTransProxies();
    void SyncPlayMode();
    void SetContexts(Symbol);
    void SetSongAnimGenre(Symbol);
    void SetSongInfo(Symbol, Symbol);
    void LoadMainCharacters(BandCamShot*);
    BandCharacter* FindTarget(Symbol, const TargetNames&);
    BandCharacter* FindTarget(Symbol);
    bool AllCharsLoaded();
    bool DircutRecurse(BandCamShot*, int);
    bool AddDircut(BandCharacter*, BandCamShot*, Symbol, int);
    bool AddDircut(BandCamShot*);
    void ClearDircuts();
    int GetInstrumentForTarget(Symbol, int);
    void SendMessage(Symbol, Symbol, bool);
    bool ValidGenreGender(CamShot*);
    void LoadCharacters(Symbol, bool);
    void StartClipLoads(bool, BandCamShot*);
    void SelectExtra(FileMerger::Merger&);
    BandCharDesc* GetPrefab(int, int);
    bool DemandLoad() const {
        return TheLoadMgr.EditMode() || !TheBandDirector || !mDemandLoad.Null();
    }
    bool DemandLoadSym() const { return !mDemandLoad.Null(); }
    bool PlayShot5() const { return mPlayShot5; }
    TargetNames& VenueNames(){ return mVenueNames; }
    void SetModeSink(Hmx::Object* o){ mModeSink = o; }

    DataNode GetUserTrack(int);
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

    static DataArray* GetRemap(Symbol);
    static DataArray* GetGroupArray(BandCharDesc::CharInstrumentType);
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(BandWardrobe);
    }
    NEW_OBJ(BandWardrobe);
    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjDirPtr<ObjectDir> unk8; // 0x8
    ObjDirPtr<ObjectDir> unk14; // 0x14
    ObjPtr<FileMerger, ObjectDir> unk20; // 0x20
    std::list<Symbol> unk2c; // 0x2c
    TargetNames mVignetteNames; // 0x34
    TargetNames mClosetNames; // 0x44
    TargetNames mVenueNames; // 0x54
    TargetNames* mCurNames; // 0x64
    BandCharacter* mTargets[4]; // 0x68
    Symbol unk78; // 0x78
    bool unk7c; // 0x7c
    ObjectDir* mVenueDir; // 0x80 - dir
    Symbol mGenre; // 0x84
    Symbol mTempo; // 0x88
    Symbol mVocalGender; // 0x8c
    ObjPtr<Hmx::Object, ObjectDir> mModeSink; // 0x90
    bool mShotSetPlayMode; // 0x9c
    bool mPlayShot5; // 0x9d
    Symbol mDemandLoad; // 0xa0
    Symbol mPlayerForcedFocuses[4]; // 0xa4
    bool mPlayerEnableBlinks[4]; // 0xb4
};

extern BandWardrobe* TheBandWardrobe;