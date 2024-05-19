#include "char/CharWeightable.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(CharWeightable)

CharWeightable::CharWeightable() : mWeight(1.0f), mWeightOwner(this, this) {

}

void CharWeightable::Replace(Hmx::Object* o1, Hmx::Object* o2){
    Hmx::Object::Replace(o1, o2);
    if(mWeightOwner == o1){
        mWeightOwner = dynamic_cast<CharWeightable*>(o2);
    }
    if(mWeightOwner == 0){
        mWeightOwner = this;
    }
}

SAVE_OBJ(CharWeightable, 0x21)

void CharWeightable::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    bs >> mWeight;
    if(gRev > 1) bs >> mWeightOwner;
}

BEGIN_COPYS(CharWeightable)
    GET_COPY(CharWeightable)
    BEGIN_COPY_CHECKED
        if(ty == kCopyShallow){
            mWeightOwner = c->mWeightOwner.mPtr;
        }
        else {
            mWeightOwner = this;
            mWeight = c->mWeightOwner->mWeight;
        }
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x43)
END_HANDLERS

BEGIN_PROPSYNCS(CharWeightable)
    if(sym == weight){
        if(_op == kPropSet){
            SetWeight(_val.Float(0));
        }
        else {
            if((int)_op == 0x40) return false;
            _val = DataNode(mWeight);
        }
        return true;
    }
    if(sym == weight_owner){
        if(_op == kPropSet){
            CharWeightable* w = _val.Obj<CharWeightable>(0);
            if(w) mWeightOwner = w;
        }
        else {
            if((int)_op == 0x40) return false;
            _val = DataNode(mWeightOwner);
        }
        return true;
    }
END_PROPSYNCS
