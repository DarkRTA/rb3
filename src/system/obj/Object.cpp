#include "obj/Object.h"

#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Utl.h"

#include "common.hpp"
#include "msgsource.hpp"

extern const char* gNullStr;
extern void PropertyNOP(const char*, char*, String&);

ObjectDir* Hmx::Object::DataDir(){
    if(mDir != nullptr) return mDir;
    else return ObjectDir::sMainDir;
}

Hmx::Object::Object() : mTypeDef(0), mName(gNullStr), mDir(0) { }

void Hmx::Object::SetTypeDef(DataArray* da){
    if(mTypeDef != da){
        if(mTypeDef != nullptr){
            mTypeDef->Release();
            mTypeDef = 0;
        }
        mTypeProps.ClearAll(this);
        mTypeDef = da;
        if(da != nullptr) da->AddRef();
    }
}

DataNode* Hmx::Object::Property(DataArray* prop, bool fail){
    static DataNode n;
    if(SyncProperty(n, prop, 0, kPropGet)) return &n;
    Symbol name = prop->Sym(0);
    DataNode* kv = mTypeProps.KeyValue(name, false);
    if(kv == nullptr){
        if(mTypeDef != nullptr){
            DataArray* found = mTypeDef->FindArray(name, fail);
            if(found != nullptr){
                kv = &found->Evaluate(1);
            }
        }
    }
    if(kv != nullptr){
        int cnt = prop->Size();
        if(cnt == 1) return kv;
        else if(cnt == 2){
            if(kv->Type() == kDataArray){
                DataArray* ret = kv->mValue.array;
                return &ret->Node(prop->Int(1));
            }
        }
    }
    if(fail){
        String str;
        str << prop;
        String str2(str);
        PropertyNOP("%s: property %s not found", PathName(this), str2);
    }
    return nullptr;
}

DataNode* Hmx::Object::Property(Symbol prop, bool fail){
    static DataArrayPtr d(DataNode(1));
    d.Node(0) = DataNode(prop);
    return Property(d.mData, fail);
}

DataNode Hmx::Object::HandleProperty(DataArray* prop, DataArray* a2, bool fail){
    static DataNode n(a2, kDataArray);
    if(SyncProperty(n, prop, 0, kPropHandle)){
        return DataNode(n);
    }
    if(fail){
        if(prop != nullptr) prop->Sym(0);
        else Symbol("<none>");
        PathName(this);
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
            prop->Size();
            mTypeProps.SetArrayValue(name, prop->Int(1), val, mTypeDef, this);
        }
    }
}

void Hmx::Object::SetProperty(Symbol prop, const DataNode& val){
    static DataArrayPtr d(DataNode(1));
    d.Node(0) = DataNode(prop);
    SetProperty(d.mData, val);
}

int Hmx::Object::PropertySize(DataArray* prop){
    static DataNode n;
    if(SyncProperty(n, prop, 0, kPropSize)){
        return n.Int(nullptr);
    }
    else {
        prop->Size();
        Symbol name = prop->Sym(0);
        DataNode* kv = mTypeProps.KeyValue(name, false);
        if(kv == nullptr){
            if(mTypeDef != nullptr){
                kv = &mTypeDef->FindArray(name, true)->Evaluate(1);
            }
            else PathName(this);
        }
        kv->Type();
        return kv->mValue.array->Size();
    }
}

void Hmx::Object::ClearProperties(DataArray* propArr){
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
        prop->Size();
        mTypeProps.RemoveArrayValue(prop->Sym(0), prop->Int(1), mTypeDef, this);
    }
}

void Hmx::Object::InsertProperty(DataArray* prop, const DataNode& val){
    if(!SyncProperty((DataNode&)val, prop, 0, kPropInsert)){
        prop->Size();
        mTypeProps.InsertArrayValue(prop->Sym(0), prop->Int(1), val, mTypeDef, this);
    }
}

void Hmx::Object::Replace(Hmx::Object* obj1, Hmx::Object* obj2){
    mTypeProps.Replace(obj1, obj2, this);
}

// see scratch: https://decomp.me/scratch/9abtP
DataNode Hmx::Object::Handle(DataArray* da, bool b){
    Symbol sym = da->Sym(1);
    static Symbol SymGet("get");
    if(sym == SymGet){
        DataNode got = OnGet(da);
        if(got.Type() != kDataUnhandled) return DataNode(got);
    }
    static Symbol SymGetArray("get_array");
    if(sym == SymGetArray){
        return OnGetArray(da, da->Sym(2));
    }
    static Symbol SymSize("size");
    if(sym == SymSize){
        return DataNode(PropertySize(da->Array(2)));
    }
    static Symbol SymSet("set");
    if(sym == SymSet){
        DataNode set = OnSet(da);
        if(set.Type() != kDataUnhandled) return DataNode(set);
    }
    static Symbol SymInsert("insert");
    if(sym == SymInsert){
        InsertProperty(da->Array(2), da->Evaluate(3));
        return DataNode(0);
    }
    static Symbol SymRemove("remove");
    if(sym == SymRemove){
        RemoveProperty(da->Array(2));
        return DataNode(0);
    }
    static Symbol SymClear("clear");
    if(sym == SymClear){
        ClearProperties(da->Array(2));
        return DataNode(0);
    }
    static Symbol SymAppend("append");
    if(sym == SymAppend){
        DataNode app = OnAppendToArray(da);
        if(app.Type() != kDataUnhandled) return DataNode(app);
    }
    static Symbol SymHas("has");
    if(sym == SymHas){
        return DataNode(Property(da->Array(2), false) != 0);
    }
    static Symbol SymPropHandle("prop_handle");
    if(sym == SymPropHandle){
        return HandleProperty(da, da->Array(2), true);
    }
    static Symbol SymCopy("copy");
    if(sym == SymCopy){
        Copy(da->GetObj(2), (CopyType)da->Int(3));
        return DataNode(0);
    }
    static Symbol SymReplace("replace");
    if(sym == SymReplace){
        Replace(da->GetObj(2), da->GetObj(3));
        return DataNode(0);
    }
    static Symbol SymClassName("class_name");
    if(sym == SymClassName){
        return DataNode(ClassName());
    }
    static Symbol SymName("name");
    if(sym == SymName){
        return DataNode(mName);
    }
    static Symbol SymIterateRefs("iterate_refs");
    if(sym == SymIterateRefs){
        DataNode refs = OnIterateRefs(da);
        if(refs.Type() != kDataUnhandled) return DataNode(refs);
    }
    static Symbol SymDir("dir");
    if(sym == SymDir){

    }
    static Symbol SymSetName("set_name");
    if(sym == SymSetName){

    }
    static Symbol SymSetType("set_type");
    if(sym == SymSetType){
        SetType(da->Sym(2));
        return DataNode(0);
    }
    static Symbol SymIsA("is_a");
    if(sym == SymIsA){
        return DataNode(IsASubclass(ClassName(), da->Sym(2)));
    }
    static Symbol SymGetType("get_type");
    if(sym == SymGetType){
        return DataNode(Type());
    }
    static Symbol SymGetHeap("get_heap");
    if(sym == SymGetHeap){
        return DataNode(GetHeap());
    }
    // if none of those symbols matched, we fall back here
    bool stank = false;
    if(mTypeDef != 0){
        DataArray* found = mTypeDef->FindArray(sym, false);
        if(found != 0) stank = true;
        if(stank){
            DataNode ran = found->ExecuteScript(1, this, da, 2);
            if(ran.Type() != kDataUnhandled) return DataNode(ran);
        }
        if(b) PathName(this);
    }
    
    return DataNode(kDataUnhandled, 0);
}

DataNode Hmx::Object::HandleType(DataArray* msg){
    Symbol t = msg->Sym(1);
    bool found = false;
    DataArray* handler;
    if(mTypeDef != nullptr){
        handler = mTypeDef->FindArray(t, false);
        if(handler != nullptr) found = true;
    }
    if(found){
        return handler->ExecuteScript(1, this, (const DataArray*)msg, 2);
    }
    else return DataNode(kDataUnhandled, 0);
}

DataNode Hmx::Object::OnAppendToArray(const DataArray* da){
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
