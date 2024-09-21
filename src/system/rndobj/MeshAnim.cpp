#include "rndobj/MeshAnim.h"
#include "utl/Symbols.h"

INIT_REVS(RndMeshAnim);

DECOMP_FORCEACTIVE(MeshAnim, __FILE__, "o")

RndMeshAnim::RndMeshAnim() : mMesh(this, 0), mKeysOwner(this, this) {

}

void RndMeshAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndMeshAnim*>(to)->mKeysOwner;
    }
}

SAVE_OBJ(RndMeshAnim, 0xB0)

BEGIN_LOADS(RndMeshAnim)
    LOAD_REVS(bs)
    ASSERT_REVS(2, 0)
    if(gRev != 0) LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    bs >> mMesh;
    bs >> mVertPointsKeys;
    if(gRev > 1) bs >> mVertNormalsKeys;
    bs >> mVertTexsKeys;
    bs >> mVertColorsKeys;
    bs >> mKeysOwner;
    if(!mKeysOwner) mKeysOwner = this;
END_LOADS

BEGIN_COPYS(RndMeshAnim)
    CREATE_COPY_AS(RndMeshAnim, m)
    MILO_ASSERT(m, 0xD6);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_MEMBER_FROM(m, mMesh)
    if(ty == kCopyShallow || (ty == kCopyFromMax && m->mKeysOwner != m)){
        COPY_MEMBER_FROM(m, mKeysOwner)
    }
    else {
        MILO_ASSERT(m->mKeysOwner != this, 0xE3);
        mKeysOwner = this;
        mVertPointsKeys = m->mKeysOwner->mVertPointsKeys;
        mVertNormalsKeys = m->mKeysOwner->mVertNormalsKeys;
        mVertTexsKeys = m->mKeysOwner->mVertTexsKeys;
        mVertColorsKeys = m->mKeysOwner->mVertColorsKeys;
    }
END_COPYS

void RndMeshAnim::Print(){
    TextStream& t = TheDebug;
    t << "   mesh: " << mMesh << "\n";
    t << "   keysOwner: " << mKeysOwner << "\n";
    t << "   vertPointsKeys: " << mVertPointsKeys << "\n";
    t << "   vertNormalsKeys: " << mVertNormalsKeys << "\n";
    t << "   vertTexsKeys: " << mVertTexsKeys << "\n";
    t << "   vertColorsKeys: " << mVertColorsKeys << "\n";
}

#pragma push
#pragma dont_inline on
void RndMeshAnim::ShrinkKeys(int num){
    if(VertPointsKeys().size() != 0){
        VertPointsKeys().resize(num);
    }
    if(VertNormalsKeys().size() != 0){
        VertNormalsKeys().resize(num);
    }
    if(VertTexsKeys().size() != 0){
        VertTexsKeys().resize(num);
    }
    if(VertColorsKeys().size() != 0){
        VertColorsKeys().resize(num);
    }
}
#pragma pop

BEGIN_HANDLERS(RndMeshAnim)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_EXPR(num_verts, NumVerts())
    HANDLE_ACTION(shrink_verts, ShrinkVerts(_msg->Int(2)))
    HANDLE_ACTION(shrink_keys, ShrinkKeys(_msg->Int(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x207)
END_HANDLERS

BEGIN_PROPSYNCS(RndMeshAnim)
    SYNC_PROP(mesh, mMesh)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS