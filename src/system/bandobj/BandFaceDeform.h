#pragma once
#include "obj/Object.h"
#include "rndobj/MeshAnim.h"

// naming stuff is hard
// if you have any better names please by all means
struct Delta {
    char unk0; // 0x0
    unsigned short num; // 0x1

    static unsigned int offset(unsigned short us){
        return us * 3 + 4;
    }

    unsigned int thisoffset(){
        return offset(num);
    }
    void* next(){
        char* p = (char*)this;
        return &p[thisoffset()];
    }
};

class BandFaceDeform : public Hmx::Object {
public:
    class DeltaArray {
    public:
        DeltaArray();
        DeltaArray(const DeltaArray&);
        ~DeltaArray();

        DeltaArray& operator=(const DeltaArray&);

        int NumVerts();
        void SetSize(int);
        void Clear();
        void Load(BinStream&);
        void AppendDeltas(const std::vector<Vector3>&, const std::vector<Vector3>&);
        void* end(){ return &((char*)mData)[mSize]; }
        void* begin(){ return mData; }

        int mSize; // 0x0
        void* mData; // 0x4
    };

    BandFaceDeform();
    virtual ~BandFaceDeform();
    OBJ_CLASSNAME(BandFaceDeform);
    OBJ_SET_TYPE(BandFaceDeform);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    int TotalSize();
    void SetFromMeshAnim(RndMeshAnim*, RndMeshAnim*, int, int);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    std::vector<DeltaArray> mFrames; // 0x1c
};