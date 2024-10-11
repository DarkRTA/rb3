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
    CREATE_COPY(CharWeightable)
    BEGIN_COPYING_MEMBERS
        if(ty == kCopyShallow){
            SetWeightOwner(c->mWeightOwner.Ptr());
        }
        else {
            SetWeightOwner(this);
            mWeight = c->mWeightOwner->mWeight;
        }
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x43)
END_HANDLERS

BEGIN_PROPSYNCS(CharWeightable)
    if(sym == weight){
        if(_op == kPropSet){
            SetWeight(_val.Float());
        }
        else {
            if((int)_op == 0x40) return false;
            _val = DataNode(mWeight);
        }
        return true;
    }
    if(sym == weight_owner){
        if(_op == kPropSet){
            SetWeightOwner(_val.Obj<CharWeightable>());
        }
        else {
            if((int)_op == 0x40) return false;
            _val = DataNode(mWeightOwner);
        }
        return true;
    }
END_PROPSYNCS
