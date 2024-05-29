#ifndef WORLD_LIGHTPRESET_H
#define WORLD_LIGHTPRESET_H
#include "rndobj/Anim.h"
#include "rndobj/EventTrigger.h"
#include "obj/ObjVector.h"

class LightHue;
class RndEnviron;
class RndLight;
class Spotlight;
class SpotlightDrawer;

class LightPreset : public RndAnimatable {
public:

    class Keyframe {
    public:
        Keyframe(Hmx::Object*);
    };

    class EnvironmentEntry {
    public:
    };

    class EnvLightEntry {
    public:
    };

    class SpotlightEntry {
    public:
    };

    class SpotlightDrawerEntry {
    public:
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
};

#endif
