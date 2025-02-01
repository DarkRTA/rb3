#pragma once
#include "rndobj/Highlightable.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "char/CharClip.h"
#include "char/CharLipSync.h"
#include "char/CharDriver.h"

/** "Drives lip sync animation" */
class CharLipSyncDriver : public RndHighlightable,
                          public CharWeightable,
                          public CharPollable {
public:
    CharLipSyncDriver();
    virtual ~CharLipSyncDriver();
    virtual void Highlight();
    OBJ_CLASSNAME(CharLipSyncDriver);
    OBJ_SET_TYPE(CharLipSyncDriver);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    virtual void Enter();

    void SetClips(ObjectDir *);
    void SetLipSync(CharLipSync *);
    void Sync();
    ObjectDir *ClipDir() const { return mClips; }
    ObjectDir *OverrideDir() const {
        if (mOverrideOptions)
            return mOverrideOptions;
        else
            return ClipDir();
    }

    DECLARE_REVS;
    NEW_OBJ(CharLipSyncDriver)
    static void Init() { REGISTER_OBJ_FACTORY(CharLipSyncDriver) }

    /** "The lipsync file to use" */
    ObjPtr<CharLipSync> mLipSync; // 0x28
    /** "pointer to the visemes" */
    ObjPtr<ObjectDir> mClips; // 0x34
    ObjPtr<CharClip> mBlinkClip; // 0x40
    /** "Will use this song if set, except for blinks" */
    ObjPtr<CharLipSyncDriver> mSongOwner; // 0x4c
    /** "offset within song in seconds, resets on song change" */
    float mSongOffset; // 0x58
    /** "should we loop this song, resets on song change" */
    bool mLoop; // 0x5c
    CharLipSync::PlayBack *mSongPlayer; // 0x60
    /** "The CharBones object to add or blend into. */
    ObjPtr<CharBonesObject> mBones; // 0x64
    /** "Test charclip to apply, does nothing else" */
    ObjPtr<CharClip> mTestClip; // 0x70
    /** "weight to apply this clip with" */
    float mTestWeight; // 0x7c
    /** "default clip to be used as the override - maybe be overriden programatically" */
    ObjPtr<CharClip> mOverrideClip; // 0x80
    /** "weight to blend override clip. this is mostly here for testing, because its
     * likely to be set programatically." */
    float mOverrideWeight; // 0x8c
    /** "an optional clipset that provides list of clips to override face with - viseme
     * clipset is used otherwise" */
    ObjPtr<ObjectDir> mOverrideOptions; // 0x90
    /** "is the override clip applied addtively on top of face mocap?  If false, it will
     * blend." */
    bool mApplyOverrideAdditively; // 0x9c
    /** "This will be used instead of the song, if set" */
    ObjPtr<CharDriver> mAlternateDriver; // 0xa0
};
