#pragma once
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "rndobj/PropAnim.h"
#include "obj/ObjPtr_p.h"
#include "utl/Std.h"
#include "char/CharClip.h"

/** "A full lipsync animation, basically a changing set of weights for a set of named visemes.  Sampled at 30hz" */
class CharLipSync : public Hmx::Object {
public:
    class Generator {
    public:
        struct Weight {
            unsigned char unk0;
            unsigned char unk1;
        };

        Generator();
        void Init(CharLipSync*);
        void AddWeight(int, float);
        void NextFrame();
        void RemoveViseme(int);
        void Finish();

        CharLipSync* mLipSync; // 0x0
        int mLastCount; // 0x4
        std::vector<Weight> mWeights; // 0x8
    };

    class PlayBack {
    public:
        struct Weight {
            Weight() : unk0(0) {}
            ObjPtr<CharClip> unk0;
            float unkc;
            float unk10;
            float unk14;
        };

        PlayBack();
        void Set(CharLipSync*, ObjectDir*);
        void Reset();
        void Poll(float);

        std::vector<Weight> mWeights; // 0x0
        CharLipSync* mLipSync; // 0x8
        RndPropAnim* mPropAnim; // 0xc
        ObjectDir* mClips; // 0x10
        int mIndex; // 0x14
        int mOldIndex; // 0x18
        int mFrame; // 0x1c
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

    void Parse(DataArray*);
    RndPropAnim* GetPropAnim() const { return mPropAnim; }
    float Duration(){ return (float)(mFrames - 1) / 30.0f;}

    DataNode OnParse(DataArray*);
    DataNode OnParseArray(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharLipSync)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharLipSync)
    }

    /** "PropAnim to control this lipsync" */
    ObjPtr<RndPropAnim> mPropAnim; // 0x1c
    /** "viseme names" */
    std::vector<String> mVisemes; // 0x28
    /** "how many keyframes" */
    int mFrames; // 0x30
    std::vector<unsigned char VECTOR_SIZE_LARGE> mData; // 0x34

    // duration: "duration in seconds"
};
