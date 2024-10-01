#ifndef WORLD_LIGHTPRESET_H
#define WORLD_LIGHTPRESET_H
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/PostProc.h"
#include "rndobj/Lit.h"
#include "obj/ObjVector.h"
#include <deque>

class LightHue;
class RndEnviron;
class Spotlight;
class SpotlightDrawer;

static bool sLoading;
class AutoLoading {
public:
    AutoLoading(){ sLoading = true; }
    ~AutoLoading(){ sLoading = false; }

};

class LightPreset : public RndAnimatable {
public:
    // size 0x14
    class EnvironmentEntry {
    public:
        EnvironmentEntry();
        void Load(BinStream&);
        bool operator!=(const EnvironmentEntry&) const;

        int mColor; // 0x0 - ambient color
        int mFogColor; // 0x4 - fog color
        bool mFogEnable; // 0x8
        float mFogStart; // 0xc
        float mFogEnd; // 0x10
    };

    // size 0x28
    class EnvLightEntry {
    public:
        EnvLightEntry();
        void Load(BinStream&);
        void Animate(const EnvLightEntry&, float);
        bool operator!=(const EnvLightEntry&) const;

        Hmx::Quat unk0; // 0x0
        Vector3 mPosition; // 0x10
        int mColor; // 0x1c
        float mRange; // 0x20
        RndLight::Type mLightType; // 0x24
    };

    // size 0x20
    class SpotlightEntry {
    public:
        SpotlightEntry(Hmx::Object*);
        void Load(BinStream&);
        void CalculateDirection(Spotlight*, Hmx::Quat&) const;
        void Animate(Spotlight*, const SpotlightEntry&, float);

        float mIntensity; // 0x0
        int mColor; // 0x4 - packed color
        bool unk8p7 : 1;
        bool unk8p6 : 1;
        bool unk8p5 : 1;
        bool unk8p4 : 1;
        bool unk8p3 : 1;
        bool unk8p2 : 1;
        bool unk8p1 : 1;
        bool mFlareEnabled : 1; // 0x8 & 1
        RndTransformable* mTarget; // 0xc
        Hmx::Quat unk10;
    };

    // 0x10
    class SpotlightDrawerEntry {
    public:
        SpotlightDrawerEntry();
        void Load(BinStream&);
        void Animate(const SpotlightDrawerEntry&, float);
        bool operator!=(const SpotlightDrawerEntry&) const;
    
        float mTotalIntensity; // 0x0
        float mBaseIntensity; // 0x4
        float mSmokeIntensity; // 0x8
        float mLightInfluence; // 0xc
    };

    class Keyframe {
    public:
        Keyframe(Hmx::Object*);
        ~Keyframe(){}

        void Load(BinStream&);
        void LoadP9(BinStream&);
        void LoadStageKit(BinStream&);

        ObjVector<SpotlightEntry> mSpotlightEntries; // 0x0
        std::vector<EnvironmentEntry> mEnvironmentEntries; // 0xc
        std::vector<EnvLightEntry> mLightEntries; // 0x14
        std::vector<SpotlightDrawerEntry> mSpotlightDrawerEntries; // 0x1c
        ObjPtr<RndPostProc, ObjectDir> mVideoVenuePostProc; // 0x24
        ObjPtrList<EventTrigger,ObjectDir> mTriggers; // 0x30
        // FIXME: the vector types need to be bools
        std::vector<unsigned char> mSpotlightChanges; // 0x40
        std::vector<unsigned char> mEnvironmentChanges; // 0x48
        std::vector<unsigned char> mLightChanges; // 0x50
        std::vector<unsigned char> mSpotlightDrawerChanges; // 0x58
        float mDuration; // 0x60
        float mFadeOutTime; // 0x64
        float mFrame; // 0x68
    };

    enum KeyframeCmd {
        kPresetKeyframeFirst,
        kPresetKeyframeNext,
        kPresetKeyframePrev,
        kPresetKeyframeNum
    };

    enum PresetObject {
        kPresetSpotlight,
        kPresetSpotlightDrawer,
        kPresetEnv,
        kPresetLight
    };

    LightPreset();
    OBJ_CLASSNAME(LightPreset);
    OBJ_SET_TYPE(LightPreset);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~LightPreset();
    virtual void StartAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame(){ return mCachedDuration; }
    virtual void Replace(Hmx::Object*, Hmx::Object*);

    bool PlatformOk() const;
    Symbol Category() const { return mCategory; }
    bool Manual() const { return mManual; }
    int GetCurrentKeyframe() const;
    void Clear();
    void RemoveSpotlight(int);
    void RemoveEnvironment(int);
    void RemoveLight(int);
    void RemoveSpotlightDrawer(int);
    void SyncNewSpotlights();
    void CacheFrames();
    void OnKeyframeCmd(KeyframeCmd);
    void SetKeyframe(Keyframe&);
    void ApplyState(const Keyframe&);
    void Animate(float);
    void SyncKeyframeTargets();
    void TranslateColor(const Hmx::Color&, Hmx::Color&);
    void GetKey(float, int&, int&, float&) const;
    RndPostProc* GetCurrentPostProc() const;
    void SetFrameEx(float, float, bool);
    int NextManualFrame(KeyframeCmd) const;
    void AdvanceManual(KeyframeCmd);
    void FillSpotPresetData(Spotlight*, SpotlightEntry&, int);
    void FillEnvPresetData(RndEnviron*, EnvironmentEntry&);
    void FillLightPresetData(RndLight*, EnvLightEntry&);
    void FillSpotlightDrawerPresetData(SpotlightDrawer*, SpotlightDrawerEntry&);
    void SetSpotlight(Spotlight*, int);
    void AddSpotlight(Spotlight*, bool);
    void AddEnvironment(RndEnviron*);
    void AddLight(RndLight*);
    void AddSpotlightDrawer(SpotlightDrawer*);
    void AnimateSpotFromPreset(Spotlight*, const SpotlightEntry&, float);
    void AnimateEnvFromPreset(RndEnviron*, const EnvironmentEntry&, float);
    void AnimateLightFromPreset(RndLight*, const EnvLightEntry&, float);
    void AnimateSpotlightDrawerFromPreset(SpotlightDrawer*, const SpotlightDrawerEntry&, float);
    void SetHue(LightHue* hue){ mHue = hue; }
    float LegacyFadeIn() const { return mLegacyFadeIn; }

    static void ResetEvents();
    static std::deque<std::pair<KeyframeCmd, float> > sManualEvents;

    DataNode OnSetKeyframe(DataArray*);
    DataNode OnViewKeyframe(DataArray*);

    ObjVector<Keyframe> mKeyframes; // 0x10
    std::vector<Spotlight*> mSpotlights; // 0x1c
    std::vector<RndEnviron*> mEnvironments; // 0x24
    std::vector<RndLight*> mLights; // 0x2c
    std::vector<SpotlightDrawer*> mSpotlightDrawers; // 0x34
    Symbol mCategory; // 0x3c
    int mPlatformOnly; // 0x40 - enum Platform?
    ObjPtrList<EventTrigger, ObjectDir> mSelectTriggers; // 0x44
    float mLegacyFadeIn; // 0x54
    bool mLooping; // 0x58
    bool mManual; // 0x59
    bool mLocked; // 0x5a
    ObjVector<SpotlightEntry> mSpotlightState; // 0x5c
    std::vector<EnvironmentEntry> mEnvironmentState; // 0x68
    std::vector<EnvLightEntry> mLightState; // 0x70
    std::vector<SpotlightDrawerEntry> mSpotlightDrawerState; // 0x78
    Keyframe* mLastKeyframe; // 0x80
    float mLastBlend; // 0x84
    float mStartBeat; // 0x88
    float mManualFrameStart; // 0x8c
    int mManualFrame; // 0x90
    int mLastManualFrame; // 0x94
    float mManualFadeTime; // 0x98
    float mCachedDuration; // 0x9c
    LightHue* mHue; // 0xa0

    DECLARE_REVS
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(LightPreset)
    static void Init(){
        REGISTER_OBJ_FACTORY(LightPreset)
    }
};

inline BinStream& operator>>(BinStream& bs, LightPreset::Keyframe& k){
    k.Load(bs);
    return bs;
}

inline BinStream& operator>>(BinStream& bs, LightPreset::EnvLightEntry& l){
    l.Load(bs);
    return bs;
}

inline BinStream& operator>>(BinStream& bs, LightPreset::EnvironmentEntry& e){
    e.Load(bs);
    return bs;
}

inline BinStream& operator>>(BinStream& bs, LightPreset::SpotlightEntry& e){
    e.Load(bs);
    return bs;
}

inline BinStream& operator>>(BinStream& bs, LightPreset::SpotlightDrawerEntry& e){
    e.Load(bs);
    return bs;
}

LightPreset::KeyframeCmd SymToPstKeyframe(Symbol s);

#endif
