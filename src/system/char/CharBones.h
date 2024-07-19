#ifndef CHAR_CHARBONES_H
#define CHAR_CHARBONES_H
#include "obj/Object.h"
#include <vector>

class CharClip;

class CharBones {
public:
    enum Type {
        TYPE_POS = 0,
        TYPE_SCALE = 1,
        TYPE_QUAT = 2,
        TYPE_ROTX = 3,
        TYPE_ROTY = 4,
        TYPE_ROTZ = 5,
        TYPE_END = 6,
        NUM_TYPES = 7,
    };

    enum CompressionType {
        kCompressNone,
        kCompressRots,
        kCompressVects,
        kCompressQuats,
        kCompressAll
    };

    struct Bone {
        Symbol name;
        float weight;
    };

    CharBones();
    virtual ~CharBones(){}
    virtual void ScaleAdd(CharClip*, float, float, float);
    virtual void Print();
    virtual void ReallocateInternal();

    void ClearBones();
    void Zero();
    void SetWeights(float);
    void AddBoneInternal(const Bone&);
    void AddBones(const std::vector<Bone>&);
    void AddBones(const std::list<Bone>&);
    void ListBones(std::list<Bone>&) const;
    int TypeSize(int) const;
    int FindOffset(Symbol) const;
    void* FindPtr(Symbol) const;
    void RecomputeSizes();
    void SetCompression(CompressionType);
    const char* StringVal(Symbol);
    void ScaleAddIdentity();

    static Type TypeOf(Symbol);
    static const char* SuffixOf(Type);
    static Symbol ChannelName(const char*, Type);
    static void SetWeights(float, std::vector<Bone>&);

    CompressionType mCompression; // 0x4
    std::vector<Bone> mBones; // 0x8
    char* mStart; // 0x10
    union {
        struct {
            int mPosCount; // 0x14
            int mScaleCount; // 0x18
            int mQuatCount; // 0x1c
            int mRotXCount; // 0x20
            int mRotYCount; // 0x24
            int mRotZCount; // 0x28
            int mEndCount; // 0x2c
        };
        int mCounts[7]; // 0x14 - 0x2c
    };
    struct {
        union {
            struct {
                int mPosOffset; // 0x30
                int mScaleOffset; // 0x34
                int mQuatOffset; // 0x38
                int mRotXOffset; // 0x3c
                int mRotYOffset; // 0x40
                int mRotZOffset; // 0x44
                int mEndOffset; // 0x48
            };
            int mOffsets[7]; // 0x30 - 0x48
        };
        int mTotalSize; // 0x4c
    };
};

class CharBonesObject : public CharBones, public virtual Hmx::Object {
public:
    CharBonesObject(){}
    virtual ~CharBonesObject();
    OBJ_CLASSNAME(CharBonesObject);
    OBJ_SET_TYPE(CharBonesObject);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
};

class CharBonesAlloc : public CharBonesObject {
public:
    CharBonesAlloc(){}
    virtual ~CharBonesAlloc();
    virtual void ReallocateInternal();
};

#endif
