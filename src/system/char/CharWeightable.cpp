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
            mWeightOwner = c->mWeightOwner;
        }
        else {
            mWeightOwner = mWeightOwner.operator->();
        }
        COPY_MEMBER(mWeight)
    END_COPY_CHECKED
END_COPYS

// void fn_804FC848(int param_1,undefined4 param_2,int param_3)

// {
//   int iVar1;
//   undefined4 uVar2;
  
//   iVar1 = __dynamic_cast(param_2,0,&CharWeightable::__RTTI,&Hmx::Object::__RTTI,0);
//   if (iVar1 != 0) {
//     if (param_3 == 1) {
//       uVar2 = String::c_str((String *)(iVar1 + 0xc));
//       fn_804FC8E4(param_1,uVar2);
//     }
//     else {
//       fn_804FC8E4(param_1,param_1);
//       iVar1 = String::c_str((String *)(iVar1 + 0xc));
//       *(undefined4 *)(param_1 + 8) = *(undefined4 *)(iVar1 + 8);
//     }
//   }
//   return;
// }

// void fn_804FC8E4(int param_1,int param_2)

// {
//   int iVar1;
  
//   iVar1 = param_1 + 0xc;
//   if (param_2 != 0) {
//     param_1 = param_2;
//   }
//   fn_804C9EEC(iVar1,param_1);
//   return;
// }

// void fn_804C9EEC(int param_1,Object **param_2)

// {
//   Object **ppOVar1;
  
//   ppOVar1 = *(Object ***)(param_1 + 8);
//   if (param_2 != ppOVar1) {
//     if (ppOVar1 != (Object **)0x0) {
//       Hmx::Object::Release(*ppOVar1,*(ObjRef **)(param_1 + 4));
//     }
//     *(Object ***)(param_1 + 8) = param_2;
//     if (param_2 != (Object **)0x0) {
//       Hmx::Object::AddRef(*param_2,*(ObjRef **)(param_1 + 4));
//     }
//   }
//   return;
// }

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
            CharWeightable* w = _val.Obj<CharWeightable>(0);;
            if(w) mWeightOwner = w;
        }
        else {
            if((int)_op == 0x40) return false;
            _val = DataNode(mWeightOwner);
        }
        return true;
    }
END_PROPSYNCS
