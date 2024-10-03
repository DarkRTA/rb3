#include "bandobj/BandFaceDeform.h"
#include "utl/Symbols.h"

INIT_REVS(BandFaceDeform);

BandFaceDeform::DeltaArray::DeltaArray() : mSize(0), mData(0) {}
BandFaceDeform::DeltaArray::DeltaArray(const BandFaceDeform::DeltaArray& da) : mSize(0), mData(0) { *this = da; }

BandFaceDeform::DeltaArray& BandFaceDeform::DeltaArray::operator=(const BandFaceDeform::DeltaArray& da){
    SetSize(da.mSize);
    memcpy(mData, da.mData, mSize);
    return *this;
}

BandFaceDeform::DeltaArray::~DeltaArray(){ _MemFree(mData); }
void BandFaceDeform::DeltaArray::Clear(){ SetSize(0); }

int BandFaceDeform::DeltaArray::NumVerts(){
    int num = 0;
    void* itend = end();
    for(void* p = begin(); p < itend; p){
        Delta* d = (Delta*)p;
        num += d->num;
        p = d->next();
    }
    return num;
}

void BandFaceDeform::DeltaArray::AppendDeltas(const std::vector<Vector3>& pos, const std::vector<Vector3>& base){
    if(pos.size() != base.size()){
        MILO_FAIL("AppendDeltas pos has %d points, base has %d", pos.size(), base.size());
    }
}

void BandFaceDeform::DeltaArray::SetSize(int i){
    if(mSize != i){
        mSize = i;
        _MemFree(mData);
        mData = _MemAlloc(mSize, 0);
    }
}

BandFaceDeform::BandFaceDeform(){

}

BandFaceDeform::~BandFaceDeform(){
    
}

void BandFaceDeform::SetFromMeshAnim(RndMeshAnim* a1, RndMeshAnim* a2, int i1, int i2){
    if(i2 == -1){
        i2 = a1->VertPointsKeys().size();
    }
    mFrames.resize(i2);
    for(int i = 0; i < i2; i++){
        mFrames[i].Clear();
        mFrames[i].AppendDeltas(a1->VertPointsKeys()[i + i1].value, a2->VertPointsKeys()[0].value);
    }
}

int BandFaceDeform::TotalSize(){
    int size = 0;
    for(int i = 0; i < mFrames.size(); i++){
        size += mFrames[i].mSize;
    }
    return size;
}

BEGIN_COPYS(BandFaceDeform)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(BandFaceDeform)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mFrames)
    END_COPYING_MEMBERS
END_COPYS

BinStream& operator>>(BinStream& bs, BandFaceDeform::DeltaArray& da){
    da.Load(bs);
    return bs;
}

void BandFaceDeform::DeltaArray::Load(BinStream& bs){
    int size;
    bs >> size;
    SetSize(size);
    Delta* d = (Delta*)mData;
    short* sptr = (short*)mData;
    while(size > 0){
        bs >> (short&)d->unk0;
        bs >> d->num;
        bs.Read(d + 1, d->thisoffset() - 4);
        size -= d->thisoffset();
        d = (Delta*)d->next();
    }
}

SAVE_OBJ(BandFaceDeform, 0x129)

BEGIN_LOADS(BandFaceDeform)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mFrames;
END_LOADS

BEGIN_HANDLERS(BandFaceDeform)
    HANDLE_ACTION(set_from_meshanim, SetFromMeshAnim(_msg->Obj<RndMeshAnim>(2), _msg->Obj<RndMeshAnim>(3), 0, -1))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x145)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(BandFaceDeform::DeltaArray)
    SYNC_PROP_SET(verts, o.NumVerts(), )
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(BandFaceDeform)
    SYNC_PROP(frames, mFrames)
    SYNC_PROP_SET(size, TotalSize(), )
END_PROPSYNCS