#include "obj/Object.h"
#include "os/Debug.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Utl.h"
#include "obj/MessageTimer.h"
#include "os/OSFuncs.h"

const char* blank = "";
const char* unk = "unknown";

std::map<Symbol, ObjectFunc*> Hmx::Object::sFactories;

ObjectDir* Hmx::Object::DataDir(){
    if(mDir != 0) return mDir;
    else return ObjectDir::Main();
}

Hmx::Object* Hmx::Object::NewObject(Symbol s) {
    ObjectFunc* f = sFactories[s];
    if (f) return (*f)();
    else {
        MILO_FAIL("nop %s", s);
        return NULL;
    }
}

const char* newobjectstr = "Unknown class %s";

void Hmx::Object::RegisterFactory(Symbol s, ObjectFunc* func){
    sFactories[s] = func;
}

bool Hmx::Object::RegisteredFactory(Symbol s){
    const std::map<Symbol, ObjectFunc*>::iterator it = sFactories.find(s);
    return it != sFactories.end();
}

Hmx::Object::Object() : mTypeDef(0), mName(gNullStr), mDir(0) { }

Hmx::Object& Hmx::Object::operator=(const Hmx::Object& obj){
    mName = obj.mName;
    mTypeDef = obj.mTypeDef;
    mTypeProps.Copy(obj.mTypeProps, this);
    mDir = obj.mDir;
    mRefs = obj.mRefs;
    return *this;
}

Hmx::Object::~Object(){
    mTypeProps.ClearAll(this);
    MILO_ASSERT(MainThread(), 0xA7);
    if(mTypeDef) mTypeDef->Release();
    mTypeDef = 0;
    RemoveFromDir();
}

const char* setnamedirstr = "dir";
const char* existssttr = "%s already exists";
const char* removefromdirstr = "No entry for %s in %s";

void Hmx::Object::SetTypeDef(DataArray* da){
    if(mTypeDef != da){
        if(mTypeDef != 0){
            mTypeDef->Release();
            mTypeDef = 0;
        }
        mTypeProps.ClearAll(this);
        mTypeDef = da;
        if(da != 0) da->AddRef();
    }
}

// DataNode* Hmx::Object::Property(DataArray* prop, bool fail){
//     static DataNode n;
//     if(SyncProperty(n, prop, 0, kPropGet)) return &n;
//     Symbol name = prop->Sym(0);
//     DataNode* kv = mTypeProps.KeyValue(name, false);
//     if(kv == nullptr){
//         if(mTypeDef != nullptr){
//             DataArray* found = mTypeDef->FindArray(name, fail);
//             if(found != nullptr){
//                 kv = &found->Evaluate(1);
//             }
//         }
//     }
//     if(kv != nullptr){
//         int cnt = prop->Size();
//         if(cnt == 1) return kv;
//         else if(cnt == 2){
//             if(kv->Type() == kDataArray){
//                 DataArray* ret = kv->mValue.array;
//                 return &ret->Node(prop->Int(1));
//             }
//         }
//     }
//     if(fail){
//         String str;
//         str << prop;
//         String str2(str);
//         PropertyNOP("%s: property %s not found", PathName(this), str2);
//     }
//     return nullptr;
// }

// DataNode* Hmx::Object::Property(Symbol prop, bool fail){
//     static DataArrayPtr d(DataNode(1));
//     d.Node(0) = DataNode(prop);
//     return Property(d.mData, fail);
// }

DataNode Hmx::Object::HandleProperty(DataArray* prop, DataArray* a2, bool fail){
    static DataNode n(a2, kDataArray);
    if(SyncProperty(n, prop, 0, kPropHandle)){
        return DataNode(n);
    }
    if(fail){
        MILO_FAIL("%s: property %s not found", PathName(this), (prop != 0) ? prop->Sym(0) : "<none>");
    }
    return DataNode(0);
}

void Hmx::Object::SetProperty(DataArray* prop, const DataNode& val){
    if(!SyncProperty((DataNode&)val, prop, 0, kPropSet)){
        Symbol name = prop->Sym(0);
        if(prop->Size() == 1){
            mTypeProps.SetKeyValue(name, val, true, this);
        }
        else {
            MILO_ASSERT(prop->Size() == 2, 0x17D);
            mTypeProps.SetArrayValue(name, prop->Int(1), val, mTypeDef, this);
        }
    }
}

// void Hmx::Object::SetProperty(Symbol prop, const DataNode& val){
//     static DataArrayPtr d(DataNode(1));
//     d.Node(0) = DataNode(prop);
//     SetProperty(d.mData, val);
// }

// int Hmx::Object::PropertySize(DataArray* prop){
//     static DataNode n;
//     if(SyncProperty(n, prop, 0, kPropSize)){
//         return n.Int(nullptr);
//     }
//     else {
//         prop->Size();
//         Symbol name = prop->Sym(0);
//         DataNode* kv = mTypeProps.KeyValue(name, false);
//         if(kv == nullptr){
//             if(mTypeDef != nullptr){
//                 kv = &mTypeDef->FindArray(name, true)->Evaluate(1);
//             }
//             else PathName(this);
//         }
//         kv->Type();
//         return kv->mValue.array->Size();
//     }
// }

void Hmx::Object::PropertyClear(DataArray* propArr){
    int size = PropertySize(propArr);
    DataArray* cloned = propArr->Clone(true, false, 1);
    while(size-- != 0){
        cloned->Node(cloned->Size() - 1) = DataNode(size);
        RemoveProperty(cloned);
    }
    cloned->Release();
}

void Hmx::Object::RemoveProperty(DataArray* prop){
    static DataNode n;
    if(!SyncProperty(n, prop, 0, kPropRemove)){
        MILO_ASSERT(prop->Size() == 2, 0x1BB);
        mTypeProps.RemoveArrayValue(prop->Sym(0), prop->Int(1), mTypeDef, this);
    }
}

void Hmx::Object::InsertProperty(DataArray* prop, const DataNode& val){
    if(!SyncProperty((DataNode&)val, prop, 0, kPropInsert)){
        MILO_ASSERT(prop->Size() == 2, 0x1C5);
        mTypeProps.InsertArrayValue(prop->Sym(0), prop->Int(1), val, mTypeDef, this);
    }
}

void Hmx::Object::AddRef(ObjRef* ref){
    if(ref->RefOwner())
        mRefs.push_back(ref);
}

void Hmx::Object::Save(BinStream& bs){
    SaveType(bs);
    SaveRest(bs);
}

void Hmx::Object::SaveType(BinStream& bs){
    bs << 2;
    bs << ((mTypeDef) ? mTypeDef->Sym(0) : Symbol());
}

void Hmx::Object::SaveRest(BinStream& bs){
    mTypeProps.Save(bs, this);
    bs << 0;
}

void Hmx::Object::Replace(Hmx::Object* obj1, Hmx::Object* obj2){
    mTypeProps.Replace(obj1, obj2, this);
}

#pragma dont_inline on
// see scratch: https://decomp.me/scratch/9abtP
DataNode Hmx::Object::Handle(DataArray* _msg, bool _warn){
    Symbol sym = _msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? this : 0, sym);
    HANDLE_STATIC(get, OnGet);
    {
        static Symbol _s("get_array");
        if(sym == _s){
            return PropertyArray(_msg->Sym(2));
        }
    }
    HANDLE_EXPR_STATIC(size, PropertySize(_msg->Array(2)));
    HANDLE_STATIC(set, OnSet);
    HANDLE_ACTION_STATIC(insert, InsertProperty(_msg->Array(2), _msg->Evaluate(3)));
    HANDLE_ACTION_STATIC(remove, RemoveProperty(_msg->Array(2)));
    HANDLE_ACTION_STATIC(clear, PropertyClear(_msg->Array(2)));
    HANDLE_STATIC(append, OnPropertyAppend);
    HANDLE_EXPR_STATIC(has, Property(_msg->Array(2), false) != 0);
    {
        static Symbol _s("prop_handle");
        if(sym == _s){
            return HandleProperty(_msg, _msg->Array(2), true);
        }
    }
    HANDLE_ACTION_STATIC(copy, Copy(_msg->GetObj(2), (CopyType)_msg->Int(3)));
    HANDLE_ACTION_STATIC(replace, Replace(_msg->GetObj(2), _msg->GetObj(3)));
    HANDLE_EXPR_STATIC(class_name, ClassName());
    HANDLE_EXPR_STATIC(name, mName);
    HANDLE_STATIC(iterate_refs, OnIterateRefs);
    {
        static Symbol _s("dir");
        if(sym == _s){
            // Hmx::Object* ret = 0;
            // if(mDir != 0) ret = (Hmx::Object*)mDir;
            // Hmx::Object* ret = mDir ? (Hmx::Object*)mDir : 0;
            return DataNode((Hmx::Object*)mDir);
        }
    }
    {
        static Symbol _s("set_name");
        if(sym == _s){

        }
    }
    HANDLE_ACTION_STATIC(set_type, SetType(_msg->Sym(2)));
    HANDLE_EXPR_STATIC(is_a, IsASubclass(ClassName(), _msg->Sym(2)));
    HANDLE_EXPR_STATIC(get_type, Type());
    HANDLE_EXPR_STATIC(get_heap, AllocHeapName());
    // if none of those symbols matched, we fall back here
    bool stank = false;
    if(mTypeDef != 0){
        DataArray* found = mTypeDef->FindArray(sym, false);
        if(found != 0) stank = true;
        if(stank){
            DataNode ran = found->ExecuteScript(1, this, _msg, 2);
            if(ran.Type() != kDataUnhandled) return DataNode(ran);
        }
        if(_warn) PathName(this);
    }

    return DataNode(kDataUnhandled, 0);
}
#pragma dont_inline reset

DataNode Hmx::Object::HandleType(DataArray* msg){
    Symbol t = msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? this : 0, t);
    bool found = false;
    DataArray* handler;
    if(mTypeDef != 0){
        handler = mTypeDef->FindArray(t, false);
        if(handler != 0) found = true;
    }
    if(found){
        return handler->ExecuteScript(1, this, (const DataArray*)msg, 2);
    }
    else return DataNode(kDataUnhandled, 0);
}

DataNode Hmx::Object::OnPropertyAppend(const DataArray* da){
    DataArray* arr = da->Array(2);
    int size = PropertySize(arr);
    DataArray* cloned = arr->Clone(true, false, 1);
    cloned->Node(cloned->Size() - 1) = DataNode(size);
    InsertProperty(cloned, da->Evaluate(3));
    cloned->Release();
    return DataNode(size);
}

BEGIN_PROPSYNCS(Hmx::Object);
END_PROPSYNCS;
