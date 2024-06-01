#include "rndobj/Set.h"
#include "utl/Symbols.h"

INIT_REVS(RndSet)

RndSet::RndSet() : mObjects(this, kObjListNoNull) {

}

bool RndSet::AllowedObject(Hmx::Object* o){
    if(!o || o == this) return false;
    else {
        for(int i = 0; i < mProps.size(); i++){
            if(o->Property(mProps[i], false) == 0) return false;
        }
        return true;
    }
}

void RndSet::SetTypeDef(DataArray* arr){
    if(mTypeDef != arr){
        Hmx::Object::SetTypeDef(arr);
        if(arr){
            DataArray* cfg = mTypeDef->FindArray("editor", true);
            mProps.resize(cfg->Size() - 1);
            for(int i = 1; i < cfg->Size(); i++){
                const DataArray* thisArr = cfg->Array(i);
                DataNode& thisNode = thisArr->Node(1);
                if(thisNode.Type() != kDataSymbol){
                    MILO_WARN("%s not top-level property in %s", thisArr->Sym(0), Name());
                }
                mProps[i - 1] = thisArr->Sym(0);
            }
            ObjPtrList<Hmx::Object, ObjectDir>::iterator it = mObjects.begin();
            while(it != mObjects.end()){
                if(!AllowedObject(*it)){
                    MILO_WARN("%s not allowed in set", (*it)->Name());
                    it = mObjects.erase(it);
                }
                else ++it;
            }
        }
        else mProps.clear();
    }
}

SAVE_OBJ(RndSet, 0x67)

BEGIN_LOADS(RndSet)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mObjects;
END_LOADS

BEGIN_COPYS(RndSet)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(RndSet)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mObjects)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(RndSet)
    HANDLE(allowed_objects, OnAllowedObjects)
    HANDLE_SUPERCLASS(Hmx::Object)
    for(ObjPtrList<Hmx::Object, ObjectDir>::iterator it = mObjects.begin(); it != mObjects.end(); ++it){
        (*it)->Handle(_msg, true);
    }
    HANDLE_CHECK(0x8C)
END_HANDLERS