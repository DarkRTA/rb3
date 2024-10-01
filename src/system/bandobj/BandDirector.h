#pragma once
#include "rndobj/Poll.h"
#include "rndobj/Draw.h"
#include "rndobj/Dir.h"
#include "rndobj/PropAnim.h"
#include "rndobj/PostProc.h"
#include "char/FileMerger.h"
#include "world/Dir.h"
#include "bandobj/BandCamShot.h"
#include "bandobj/BandSongPref.h"
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
        Symbol Name() const { return mName; }
        WorldDir* Dir() const { return mDir; }

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

    void VenueLoaded(WorldDir*);
    void OnMidiAddPostProc(Symbol, float, float);
    bool FacingCamera(Symbol) const;
    bool BehindCamera(Symbol) const;
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
    void EnterVenue();
    void PickIntroShot();
    void FindNextShot();
    void ClearLighting();
    bool PostProcsFromPresets(const RndPostProc*&, const RndPostProc*&, float&);
    void UpdatePostProcOverlay(const char*, const RndPostProc*, const RndPostProc*, float);
    bool ReadyForMidiParsers();
    class BandCharacter* GetCharacter(int) const;
    void ForceShot(BandCamShot*);
    void AddDircut(Symbol, float);
    void FilterShot(int&);
    Symbol GetModeInst(Symbol);
    void UnloadVenue(bool);
    BandCamShot* FindNextDircut();
    void FindNextPstKeyframe(float, float, Symbol);
    void SendCurWorldMsg(Symbol, bool);
    void PlayNextShot();

    bool IsMusicVideo();
    LightPresetManager* LightPresetMgr(){
        return mCurWorld ? &mCurWorld->mPresetManager : 0;
    }

    bool DirectedCut(Symbol s) const;
    bool BFTB(Symbol s) const;

    // TODO: find a better name for this
    bool NoWorlds(){
        bool b1;
        bool ret;
        bool b2;
        
        ret = true;
        b2 = true;
        b1 = false;
        if(mDisablePicking || !GetWorld()) b1 = true;
        if(!b1 && !GetWorld()->mCameraManager.HasFreeCam()){
            b2 = false;
        }
        if(!b2 && mVenue.Dir()) ret = false;
        return ret;
    }

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

    static Symbol RemapCat(Symbol, Symbol);
    static const char* PickDist(float*, char*, char*);
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(BandDirector);
    }
    static void Terminate();

    DECLARE_REVS;
    NEW_OBJ(BandDirector);
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    static DataArray* sPropArr;
    static float sMotionBlurBlendAmount;

    ObjDirPtr<RndDir> mChars; // 0x28
    ObjPtr<RndPropAnim, ObjectDir> mPropAnim; // 0x34
    ObjPtr<FileMerger, ObjectDir> mMerger; // 0x40
    ObjPtr<WorldDir, ObjectDir> mCurWorld; // 0x4c
    bool unk58; // 0x58
    int mNumPlayersFailed; // 0x5c
    int mExcitement; // 0x60 - ExcitementLevel?
    Symbol mForceAttention[4]; // 0x64
    ObjPtr<RndPostProc, ObjectDir> mWorldPostProc; // 0x74
    ObjPtr<RndPostProc, ObjectDir> mCamPostProc; // 0x80
    ObjPtr<RndPostProc, ObjectDir> mPostProcA; // 0x8c
    ObjPtr<RndPostProc, ObjectDir> mPostProcB; // 0x98
    float mPostProcBlend; // 0xa4
    Symbol mLightPresetCatA; // 0xa8
    Symbol mLightPresetCatB; // 0xac
    float mLightPresetCatBlend; // 0xb0
    bool mLightPresetInterpEnabled; // 0xb4
    bool mDisabled; // 0xb5
    bool mAsyncLoad; // 0xb6
    ObjPtr<BandCamShot, ObjectDir> mCurShot; // 0xb8
    ObjPtr<BandCamShot, ObjectDir> mNextShot; // 0xc4
    ObjPtr<BandCamShot, ObjectDir> mIntroShot; // 0xd0
    Symbol mShotCategory; // 0xdc
    float unke0; // 0xe0
    bool mDisablePicking; // 0xe4
    bool unke5; // 0xe5
    Keys<BandCamShot*, BandCamShot*> mDircuts; // 0xe8 - Keys<BandCamShot*>
    VenueLoader mVenue; // 0xf0
    Keys<Symbol, Symbol> unk100; // 0x100
    float unk108; // 0x108
    float mEndOfSongSec; // 0x10c
    bool unk110; // 0x110
    BandSongPref* mSongPref; // 0x114
};

extern BandDirector* TheBandDirector;