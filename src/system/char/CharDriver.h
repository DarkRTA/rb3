#ifndef CHAR_CHARDRIVER_H
#define CHAR_CHARDRIVER_H
#include "rndobj/Highlightable.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "char/CharBones.h"

class CharClipDriver; // forward dec

enum ApplyMode {
    kApplyBlend,
    kApplyAdd,
    kApplyRotateTo,
    kApplyBlendWeights
};

class CharDriver : public RndHighlightable, public CharWeightable, public CharPollable {
public:
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

    ObjPtr<CharBonesObject, ObjectDir> mBones;
    ObjPtr<ObjectDir, ObjectDir> mClips;
    CharClipDriver* mFirst;
    ObjPtr<CharClip, ObjectDir> mTestClip;
    ObjPtr<Hmx::Object, ObjectDir> mDefaultClip;
    bool mDefaultPlayStarved;
    Symbol mStarvedHandler;
    DataNode mLastNode;
    float mOldBeat;
    bool mRealign;
    float mBeatScale;
    float mBlendWidth;
    Symbol mClipType;
    ApplyMode mApply;
    CharBonesAlloc* mInternalBones;
    bool mPlayMultipleClips;
};

#endif
