#include "rndobj/LitAnim.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

int LIGHTANIM_REV = 2;

RndLightAnim::RndLightAnim() : mLight(this, 0), mKeysOwner(this, this) {

}

void RndLightAnim::SetKeysOwner(RndLightAnim* o){
    MILO_ASSERT(o, 0x27);
    mKeysOwner = o;
}

void RndLightAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner.Ptr() == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndLightAnim*>(to)->mKeysOwner;
    }
}

SAVE_OBJ(RndLightAnim, 0x46);

void RndLightAnim::Load(BinStream& bs){
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, LIGHTANIM_REV);
    if(rev > 1) Hmx::Object::Load(bs);
    RndAnimatable::Load(bs);
    bs >> mLight;
    if(rev < 1){
        Keys<Hmx::Color, Hmx::Color> keys;
        bs >> keys;
    }
    bs >> mColorKeys;
    if(rev < 1){
        Keys<Hmx::Color, Hmx::Color> keys;
        bs >> keys;
    }
    bs >> mKeysOwner;
    if(!mKeysOwner.Ptr()){
        mKeysOwner = this;
    }
}

BEGIN_COPYS(RndLightAnim)
    CREATE_COPY_AS(RndLightAnim, l)
    MILO_ASSERT(l, 116);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_MEMBER_FROM(l, mLight)
    if(ty == kCopyShallow || (ty == kCopyFromMax && l->mKeysOwner != l)){
        COPY_MEMBER_FROM(l, mKeysOwner)
    }
    else {
        mKeysOwner = this;
        mColorKeys = l->mKeysOwner->mColorKeys;
    }
END_COPYS

void RndLightAnim::Print(){
    TextStream& ts = TheDebug;
    ts << "   light: " << mLight.Ptr() << "\n";
    ts << "   keysOwner: " << mKeysOwner.Ptr() << "\n";
    ts << "   colorKeys: " << mColorKeys << "\n";
}

float RndLightAnim::EndFrame(){
    return ColorKeys().LastFrame();
}

// fn_805F7188
void RndLightAnim::SetFrame(float frame, float blend){
    RndAnimatable::SetFrame(frame, blend);
    if(mLight){
        if(!ColorKeys().empty()){
            Hmx::Color ref;
            ColorKeys().AtFrame(frame, ref);
            if(blend != 1.0f){
                Interp(mLight->GetColor(), ref, blend, ref);
            }
            mLight->SetColor(ref);
        }
    }
}

// fn_805F7264
void RndLightAnim::SetKey(float frame){
    if(mLight){
        ColorKeys().Add(mLight->GetColor(), frame, true);
    }
}

BEGIN_HANDLERS(RndLightAnim)
    HANDLE(copy_keys, OnCopyKeys)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xBF)
END_HANDLERS

DataNode RndLightAnim::OnCopyKeys(DataArray* da) {
    SetKeysOwner(this);
    mColorKeys = da->Obj<RndLightAnim>(2)->ColorKeys();
    float f = da->Float(3);
    for (Keys<Hmx::Color, Hmx::Color>::iterator it = mColorKeys.begin(); it != mColorKeys.end(); it++) {
        it->value *= f;
    }
    return DataNode();
}

BEGIN_PROPSYNCS(RndLightAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
