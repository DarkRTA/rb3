#ifndef CHAR_CHARLIPSYNCDRIVER_H
#define CHAR_CHARLIPSYNCDRIVER_H
#include "rndobj/Highlightable.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "char/CharClip.h"
#include "char/CharLipSync.h"
#include "char/CharDriver.h"

class CharLipSyncDriver : public RndHighlightable, public CharWeightable, public CharPollable {
public:
    CharLipSyncDriver();
    virtual ~CharLipSyncDriver();
    virtual void Highlight();
    OBJ_CLASSNAME(CharLipSyncDriver);
    OBJ_SET_TYPE(CharLipSyncDriver);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Poll();    
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void Enter();

    void SetClips(ObjectDir*);
    void SetLipSync(CharLipSync*);
    ObjectDir* ClipDir() const { return mClips; }
    ObjectDir* OverrideDir() const {
        if(mOverrideOptions) return mOverrideOptions;
        else return ClipDir();
    }

    ObjPtr<CharLipSync, ObjectDir> mLipSync; // 0x28
    ObjPtr<ObjectDir, ObjectDir> mClips; // 0x34
    ObjPtr<CharClip, ObjectDir> mBlinkClip; // 0x40
    ObjPtr<CharLipSyncDriver, ObjectDir> mSongOwner; // 0x4c
    float mSongOffset; // 0x58
    bool mLoop; // 0x5c
    int mSongPlayer; // 0x60 - PlayBack*
    ObjPtr<CharBonesObject, ObjectDir> mBones; // 0x64
    ObjPtr<CharClip, ObjectDir> mTestClip; // 0x70
    float mTestWeight; // 0x7c
    ObjPtr<CharClip, ObjectDir> mOverrideClip; // 0x80
    float mOverrideWeight; // 0x8c
    ObjPtr<ObjectDir, ObjectDir> mOverrideOptions; // 0x90
    bool mApplyOverrideAdditively; // 0x9c
    ObjPtr<CharDriver, ObjectDir> mAlternateDriver; // 0xa0
};

#endif
