#include "rndobj/Set.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "utl/Symbols.h"

INIT_REVS(RndSet)

RndSet::RndSet() : mObjects(this, kObjListNoNull) {}

bool RndSet::AllowedObject(Hmx::Object *o) {
    if (!o || o == this)
        return false;
    else {
        for (int i = 0; i < mProps.size(); i++) {
            if (o->Property(mProps[i], false) == nullptr) {
                return false;
            }
        }
        return true;
    }
}

void RndSet::SetTypeDef(DataArray *arr) {
    if (TypeDef() != arr) {
        Hmx::Object::SetTypeDef(arr);
        if (arr) {
            DataArray *cfg = TypeDef()->FindArray("editor");
            mProps.resize(cfg->Size() - 1);
            for (int i = 1; i < cfg->Size(); i++) {
                const DataArray *thisArr = cfg->Array(i);
                DataNode &thisNode = thisArr->Node(1);
                if (thisNode.Type() != kDataSymbol) {
                    MILO_WARN("%s not top-level property in %s", thisArr->Sym(0), Name());
                }
                mProps[i - 1] = thisArr->Sym(0);
            }
            ObjPtrList<Hmx::Object>::iterator it = mObjects.begin();
            while (it != mObjects.end()) {
                if (!AllowedObject(*it)) {
                    MILO_WARN("%s not allowed in set", (*it)->Name());
                    it = mObjects.erase(it);
                } else
                    ++it;
            }
        } else
            mProps.clear();
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
    CREATE_COPY(RndSet)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mObjects)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(RndSet)
    HANDLE(allowed_objects, OnAllowedObjects)
    HANDLE_SUPERCLASS(Hmx::Object)
    for (ObjPtrList<Hmx::Object>::iterator it = mObjects.begin(); it != mObjects.end();
         ++it) {
        (*it)->Handle(_msg, true);
    }
    HANDLE_CHECK(0x8C)
END_HANDLERS

DataNode RndSet::OnAllowedObjects(DataArray *) {
    std::list<Hmx::Object *> objList;
    for (ObjDirItr<Hmx::Object> it(Dir(), true); it != 0; ++it) {
        if (AllowedObject(it))
            objList.push_back(it);
    }
    DataArrayPtr ptr(new DataArray(objList.size()));
    int count = 0;
    for (std::list<Hmx::Object *>::iterator it = objList.begin(); it != objList.end();
         it++) {
        ptr.Node(count++) = *it;
    }
    return ptr;
}

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(RndSet)
    SYNC_PROP(objects, mObjects)
    else if (_op == kPropSet) {
        static Hmx::Object *milo = ObjectDir::Main()->FindObject("milo", false);
        for (ObjPtrList<Hmx::Object>::iterator it = mObjects.begin();
             it != mObjects.end();
             ++it) {
            if (milo) {
                static Message msg("record", 0, Symbol("Change from set"));
                msg[0] = *it;
                milo->Handle(msg, true);
            }
            (*it)->SetProperty(_prop, _val);
        }
    }
END_PROPSYNCS
#pragma pop