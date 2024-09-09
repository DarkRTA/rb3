#pragma once
#include "rndobj/Poll.h"
#include "rndobj/Draw.h"
#include "rndobj/Dir.h"
#include "rndobj/PropAnim.h"
#include "rndobj/PostProc.h"
#include "char/FileMerger.h"
#include "world/Dir.h"
#include "bandobj/BandCamShot.h"
#include "utl/Loader.h"

class BandDirector : public RndPollable, public RndDrawable {
public:
    class VenueLoader : public Loader::Callback {
    public:
        VenueLoader();
        virtual ~VenueLoader();
        virtual void FinishLoading(Loader*);
        virtual const char* StateName() const { return "VenueLoader"; }

        void Unload(bool);
        void Load(const FilePath&, LoaderPos, bool);
        WorldDir* Dir() const;

        WorldDir* mDir; // 0x4
        DirLoader* mLoader; // 0x8
        Symbol mName; // 0xc
    };
    BandDirector();
    OBJ_CLASSNAME(BandDirector);
    OBJ_SET_TYPE(BandDirector);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual void ListPollChildren(std::list<RndPollable*>&) const;
    virtual ~BandDirector();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void CollideList(const Segment&, std::list<Collision>&);

    LightPresetManager* LightPresetMgr();
    void VenueLoaded(WorldDir*);
    void OnMidiAddPostProc(Symbol, float, float);
    bool IsMusicVideo();
    bool FacingCamera(Symbol) const;
    void LoadVenue(Symbol, LoaderPos);
    void SetCharacterHideHackEnabled(bool);
    void OnMidiPresetCleanup();
    void AddSymbolKey(Symbol, Symbol, float);
    void ClearSymbolKeys(Symbol);
    void ClearSymbolKeysFrameRange(Symbol, float, float);
    void HarvestDircuts();
    void SetSongEnd(float);
    void SetShot(Symbol, Symbol);
    void ExportWorldEvent(Symbol);
    void SendMessage(Symbol, Symbol);
    void SetCrowd(Symbol);
    void SetCharSpot(Symbol, Symbol);
    void SetFog(Symbol);
    WorldDir* GetWorld();

    DataNode OnFirstShotOK(DataArray*);
    DataNode OnShotOver(DataArray*);
    DataNode OnPostProcInterp(DataArray*);
    DataNode OnSaveSong(DataArray*);
    DataNode OnFileLoaded(DataArray*);
    DataNode OnSelectCamera(DataArray*);
    DataNode OnLightPresetInterp(DataArray*);
    DataNode OnLightPresetKeyframeInterp(DataArray*);
    DataNode OnCycleShot(DataArray*);
    DataNode OnForceShot(DataArray*);
    DataNode OnGetFaceOverrideClips(DataArray*);
    DataNode OnDebugInterestsForNextCharacter(DataArray*);
    DataNode OnToggleInterestDebugOverlay(DataArray*);
    DataNode OnShotAnnotate(DataArray*);
    DataNode OnPostProcs(DataArray*);
    DataNode OnSetDircut(DataArray*);
    DataNode OnForcePreset(DataArray*);
    DataNode OnStompPresets(DataArray*);
    DataNode OnMidiAddPreset(DataArray*);
    DataNode OnGetCatList(DataArray*);
    DataNode OnCopyCats(DataArray*);
    DataNode OnLoadSong(DataArray*);
    DataNode OnMidiShotCategory(DataArray*);

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(BandDirector);
    }
    static void Terminate();
    NEW_OBJ(BandDirector);
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    static DataArray* sPropArr;

    ObjDirPtr<RndDir> mChars; // 0x28
    ObjPtr<RndPropAnim, ObjectDir> mPropAnim; // 0x34
    ObjPtr<FileMerger, ObjectDir> mMerger; // 0x40
    ObjPtr<WorldDir, ObjectDir> mCurWorld; // 0x4c
    bool unk58; // 0x58
    int unk5c; // 0x5c
    int unk60; // 0x60
    Symbol unk64[4]; // 0x64
    ObjPtr<RndPostProc, ObjectDir> unk74; // 0x74
    ObjPtr<RndPostProc, ObjectDir> unk80; // 0x80
    ObjPtr<RndPostProc, ObjectDir> unk8c; // 0x8c
    ObjPtr<RndPostProc, ObjectDir> unk98; // 0x98
    float unka4; // 0xa4
    Symbol unka8; // 0xa8
    Symbol unkac; // 0xac
    float unkb0; // 0xb0
    bool unkb4; // 0xb4
    bool unkb5; // 0xb5
    bool unkb6; // 0xb6
    ObjPtr<BandCamShot, ObjectDir> unkb8; // 0xb8
    ObjPtr<BandCamShot, ObjectDir> unkc4; // 0xc4
    ObjPtr<BandCamShot, ObjectDir> unkd0; // 0xd0
    Symbol unkdc; // 0xdc
    float unke0; // 0xe0
    bool unke4; // 0xe4
    bool unke5; // 0xe5
    Keys<BandCamShot*, BandCamShot*> mDircuts; // 0xe8 - Keys<BandCamShot*>
    VenueLoader mVenue; // 0xf0
    Keys<Symbol, Symbol> unk100; // 0x100
    float unk108; // 0x108
    float unk10c; // 0x10c
    bool unk110; // 0x110
    int unk114; // 0x114
};

extern BandDirector* TheBandDirector;