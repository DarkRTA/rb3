#ifndef CHAR_CHARDRIVER_H
#define CHAR_CHARDRIVER_H
#include "rndobj/Highlightable.h"
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "char/CharBones.h"

// forward decs
class CharClip;
class CharClipDriver;

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
    ObjectDir* ClipDir() const { return mClips; }
    float SetBlendWidth(float w){ mBlendWidth = w; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<CharBonesObject, ObjectDir> mBones; // 0x28
    ObjPtr<ObjectDir, ObjectDir> mClips; // 0x34
    CharClipDriver* mFirst; // 0x40
    ObjPtr<CharClip, ObjectDir> mTestClip; // 0x44
    ObjPtr<Hmx::Object, ObjectDir> mDefaultClip; // 0x50
    bool mDefaultPlayStarved; // 0x5c
    Symbol mStarvedHandler; // 0x60
    DataNode mLastNode; // 0x64
    float mOldBeat; // 0x6c
    bool mRealign; // 0x70
    float mBeatScale; // 0x74
    float mBlendWidth; // 0x78
    Symbol mClipType; // 0x7c
    ApplyMode mApply; // 0x80
    CharBonesAlloc* mInternalBones; // 0x84
    bool mPlayMultipleClips; // 0x88
    bool unk89; // 0x89
};

#endif
