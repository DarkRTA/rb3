#include "obj/Object.h"
#include "os/Debug.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Utl.h"
#include "obj/MessageTimer.h"

ObjectDir* Hmx::Object::DataDir(){
    if(mDir != 0) return mDir;
    else return ObjectDir::sMainDir;
}

Hmx::Object::Object() : mTypeDef(0), mName(gNullStr), mDir(0) { }

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
        MILO_FAIL("%s: property %s not found", PathName(this), (prop != 0) ? prop->Sym(0) : "none");
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

void Hmx::Object::Replace(Hmx::Object* obj1, Hmx::Object* obj2){
    mTypeProps.Replace(obj1, obj2, this);
}

// see scratch: https://decomp.me/scratch/9abtP
DataNode Hmx::Object::Handle(DataArray* _msg, bool _warn){
    Symbol sym = _msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? this : 0, sym);
    {
        static Symbol _s("get");
        if(sym == _s){
            DataNode got = OnGet(_msg);
            if(got.Type() != kDataUnhandled) return DataNode(got);
        }
    }
    {
        static Symbol _s("get_array");
        if(sym == _s){
            return PropertyArray(_msg->Sym(2));
        }
    }
    {
        static Symbol _s("size");
        if(sym == _s){
            return DataNode(PropertySize(_msg->Array(2)));
        }
    }
    {
        static Symbol _s("set");
        if(sym == _s){
            DataNode set = OnSet(_msg);
            if(set.Type() != kDataUnhandled) return DataNode(set);
        }
    }
    {
        static Symbol _s("insert");
        if(sym == _s){
            InsertProperty(_msg->Array(2), _msg->Evaluate(3));
            return DataNode(0);
        }
    }
    {
        static Symbol _s("remove");
        if(sym == _s){
            RemoveProperty(_msg->Array(2));
            return DataNode(0);
        }
    }
    {
        static Symbol _s("clear");
        if(sym == _s){
            PropertyClear(_msg->Array(2));
            return DataNode(0);
        }
    }
    {
        static Symbol _s("append");
        if(sym == _s){
            DataNode app = OnPropertyAppend(_msg);
            if(app.Type() != kDataUnhandled) return DataNode(app);
        }
    }
    {
        static Symbol _s("has");
        if(sym == _s){
            return DataNode(Property(_msg->Array(2), false) != 0);
        }
    }
    {
        static Symbol _s("prop_handle");
        if(sym == _s){
            return HandleProperty(_msg, _msg->Array(2), true);
        }
    }
    {
        static Symbol _s("copy");
        if(sym == _s){
            Copy(_msg->GetObj(2), (CopyType)_msg->Int(3));
            return DataNode(0);
        }
    }
    {
        static Symbol _s("replace");
        if(sym == _s){
            Replace(_msg->GetObj(2), _msg->GetObj(3));
            return DataNode(0);
        }
    }
    {
        static Symbol _s("class_name");
        if(sym == _s){
            return DataNode(ClassName());
        }
    }
    {
        static Symbol _s("name");
        if(sym == _s){
            return DataNode(mName);
        }
    }
    {
        static Symbol _s("iterate_refs");
        if(sym == _s){
            DataNode refs = OnIterateRefs(_msg);
            if(refs.Type() != kDataUnhandled) return DataNode(refs);
        }
    }
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
    {
        static Symbol _s("set_type");
        if(sym == _s){
            SetType(_msg->Sym(2));
            return DataNode(0);
        }
    }
    {
        static Symbol _s("is_a");
        if(sym == _s){
            return DataNode(IsASubclass(ClassName(), _msg->Sym(2)));
        }
    }
    {
        static Symbol _s("get_type");
        if(sym == _s){
            return DataNode(Type());
        }
    }
    {
        static Symbol _s("get_heap");
        if(sym == _s){
            return DataNode(GetHeap());
        }
    }
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

// DataNode Hmx::Object::HandleType(DataArray* msg){
//     Symbol t = msg->Sym(1);
//     bool found = false;
//     DataArray* handler;
//     if(mTypeDef != nullptr){
//         handler = mTypeDef->FindArray(t, false);
//         if(handler != nullptr) found = true;
//     }
//     if(found){
//         return handler->ExecuteScript(1, this, (const DataArray*)msg, 2);
//     }
//     else return DataNode(kDataUnhandled, 0);
// }

DataNode Hmx::Object::OnPropertyAppend(const DataArray* da){
    DataArray* arr = da->Array(2);
    int size = PropertySize(arr);
    DataArray* cloned = arr->Clone(true, false, 1);
    cloned->Node(cloned->Size() - 1) = DataNode(size);
    InsertProperty(cloned, da->Evaluate(3));
    cloned->Release();
    return DataNode(size);
}

bool Hmx::Object::SyncProperty(DataNode& _val, DataArray* _prop, int _i, PropOp _op){
    if(_prop->Size() == _i){
        return true;
    }
    else {
        Symbol b = _prop->Sym(_i);
        return false;
    }
}
