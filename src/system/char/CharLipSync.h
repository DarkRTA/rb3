#ifndef CHAR_CHARLIPSYNC_H
#define CHAR_CHARLIPSYNC_H
#include "obj/Object.h"
#include "rndobj/PropAnim.h"
#include "obj/ObjPtr_p.h"

class CharLipSync : public Hmx::Object {
public:

    class Generator {
    public:
        Generator();

        CharLipSync* mLipSync;
        int mLastCount;
        std::vector<int> mWeights;
    };

    class PlayBack {
    public:
        std::vector<int> mWeights;
        CharLipSync* mLipSync;
        RndPropAnim* mPropAnim;
        ObjectDir* mClips;
        int mIndex;
        int mOldIndex;
        int mFrame;
    };

    CharLipSync();
    virtual ~CharLipSync();
    OBJ_CLASSNAME(CharLipSync);
    OBJ_SET_TYPE(CharLipSync);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    ObjPtr<RndPropAnim, ObjectDir> mPropAnim;
    std::vector<String> mVisemes;
    int mFrames;
    std::vector<unsigned char, unsigned int> mData;
};

#endif
