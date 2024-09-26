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

    ObjPtr<CharLipSync, ObjectDir> mLipSync;
    ObjPtr<ObjectDir, ObjectDir> mClips;
    ObjPtr<CharClip, ObjectDir> mBlinkClip;
    ObjPtr<CharLipSyncDriver, ObjectDir> mSongOwner;
    float mSongOffset;
    bool mLoop;
    int mSongPlayer; // PlayBack*
    ObjPtr<CharBonesObject, ObjectDir> mBones;
    ObjPtr<CharClip, ObjectDir> mTestClip;
    float mTestWeight;
    ObjPtr<CharClip, ObjectDir> mOverrideClip;
    float mOverrideWeight;
    ObjPtr<ObjectDir, ObjectDir> mOverrideOptions;
    bool mApplyOverrideAdditively;
    ObjPtr<CharDriver, ObjectDir> mAlternateDriver;
};

#endif
