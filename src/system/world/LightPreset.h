#ifndef WORLD_LIGHTPRESET_H
#define WORLD_LIGHTPRESET_H
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/PostProc.h"
#include "obj/ObjVector.h"

class LightHue;
class RndEnviron;
class RndLight;
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

    class EnvironmentEntry {
    public:
        EnvironmentEntry();
        EnvironmentEntry(Hmx::Object*);
    };

    class EnvLightEntry {
    public:
        EnvLightEntry();
        EnvLightEntry(Hmx::Object*);
    };

    class SpotlightEntry {
    public:
        SpotlightEntry(Hmx::Object*);

        float mIntensity; // 0x0
        int mColor; // 0x4 - could be a Color32?
        unsigned char unk8p7 : 1;
        unsigned char unk8p6 : 1;
        unsigned char unk8p5 : 1;
        unsigned char unk8p4 : 1;
        unsigned char unk8p3 : 1;
        unsigned char unk8p2 : 1;
        unsigned char unk8p1 : 1;
        unsigned char mFlareEnabled : 1; // 0x8 & 1
        RndTransformable* mTarget; // 0xc
        Hmx::Quat unk10;
    };

    class SpotlightDrawerEntry {
    public:
        SpotlightDrawerEntry();
    };

    class Keyframe {
    public:
        Keyframe(Hmx::Object*);
        ~Keyframe();

        void Load(BinStream&);
        void LoadP9(BinStream&);

        ObjVector<SpotlightEntry> mSpotlightEntries; // 0x0
        ObjVector<EnvironmentEntry> mEnvironmentEntries; // 0xc
        ObjVector<EnvLightEntry> mLightEntries; // 0x14
        std::vector<SpotlightDrawerEntry> mSpotlightDrawerEntries; // 0x1c
        ObjPtr<RndPostProc, ObjectDir> mVideoVenuePostProc; // 0x24
        ObjPtrList<EventTrigger,ObjectDir> mTriggers; // 0x30
        std::vector<int> mSpotlightChanges; // 0x40
        std::vector<int> mEnvironmentChanges; // 0x48
        std::vector<int> mLightChanges; // 0x50
        std::vector<int> mSpotlightDrawerChanges; // 0x58
        float mDuration; // 0x60
        float mFadeOutTime; // 0x64
        float mFrame; // 0x68

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
    virtual float EndFrame();
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
    ObjVector<SpotlightEntry> unk5c;
    std::vector<EnvironmentEntry> unk68;
    std::vector<EnvLightEntry> unk70;
    std::vector<SpotlightDrawerEntry> unk78;
    int unk80;
    float unk84;
    float unk88;
    float unk8c;
    int unk90;
    int unk94;
    float unk98;
    float unk9c;
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
}

#endif
