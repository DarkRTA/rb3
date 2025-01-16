#pragma once
#include "obj/ObjMacros.h"
#include "rndobj/Highlightable.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "char/CharBones.h"
#include "char/CharClipDriver.h"

// forward decs
class CharClip;

/** "Class to Drive, Schedule and Blend CharClips.
 *  Basically a stack, new ones are pushed onto the bottom, start playing at some point,
 *  and then pop off the ones above it once they are fully blended in." */
class CharDriver : public RndHighlightable, public CharWeightable, public CharPollable {
public:
    enum ApplyMode {
        kApplyBlend,
        kApplyAdd,
        kApplyRotateTo,
        kApplyBlendWeights
    };

    CharDriver();
    virtual ~CharDriver();
    virtual void Highlight();
    OBJ_CLASSNAME(CharDriver);
    OBJ_SET_TYPE(CharDriver);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Poll();    
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void Enter();
    virtual void Exit();
    virtual void Replace(Hmx::Object*, Hmx::Object*);

    float EvaluateFlags(int);
    float Display(float);
    void Clear();
    CharClip* FindClip(const DataNode&, bool);
    CharClip* FirstClip();
    CharClipDriver* FirstPlaying();
    CharClipDriver* Last();
    CharClipDriver* Before(CharClipDriver*);
    CharClip* FirstPlayingClip();
    CharClipDriver* Play(CharClip*, int, float, float, float);
    CharClipDriver* Play(const DataNode&, int, float, float, float);
    CharClipDriver* PlayGroup(const char*, int, float, float, float);
    void Transfer(const CharDriver&);
    void SetClips(ObjectDir*);
    void SetBones(CharBonesObject*);
    void SetApply(ApplyMode);
    void SyncInternalBones();
    void SetClipType(Symbol);
    bool Starved();
    void SetStarved(Symbol);
    void SetBeatScale(float, bool);
    void Offset(float, float);
    float TopClipFrame();
    Symbol ClipType() const { return mClipType; }
    ObjectDir* ClipDir() const { return mClips; }
    void SetBlendWidth(float w){ mBlendWidth = w; }
    CharBonesObject* GetBones() const { return mBones; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharDriver)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharDriver)
    }

    /** "The CharBones object to add or blend into." */
    ObjPtr<CharBonesObject> mBones; // 0x28
    /** "pointer to clips object" */
    ObjPtr<ObjectDir> mClips; // 0x34
    CharClipDriver* mFirst; // 0x40
    /** "Pick a clip to play" */
    ObjPtr<CharClip> mTestClip; // 0x44
    /** "Clip or Group played on enter by default" */
    ObjPtr<Hmx::Object> mDefaultClip; // 0x50
    /** "If true, plays the default_clip_or_group whenever starved" */
    bool mDefaultPlayStarved; // 0x5c
    Symbol mStarvedHandler; // 0x60
    DataNode mLastNode; // 0x64
    float mOldBeat; // 0x6c
    /** "Realigns the clips to always be aligned with the beat in the measure" */
    bool mRealign; // 0x70
    /** "Scale factor applied to incoming beat" */
    float mBeatScale; // 0x74
    /** "Width in beats to blend to the next clip" */
    float mBlendWidth; // 0x78
    /** "What type of clip we can blend" */
    Symbol mClipType; // 0x7c
    /** "How to apply the driver to its bones" */
    ApplyMode mApply; // 0x80
    CharBonesAlloc* mInternalBones; // 0x84
    /** "Turn on to set this driver to play multiple clips" */
    bool mPlayMultipleClips; // 0x88
    bool unk89; // 0x89
};
