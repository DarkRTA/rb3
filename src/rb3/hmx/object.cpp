#include "hmx/object.hpp"
#include "data.hpp"
#include "common.hpp"
#include "msgsource.hpp"

DataNode Hmx::Object::OnAppendToArray(const DataArray* da){
    DataArray* arr = da->GetArrayAtIndex(2);
    int size = PropertySize(arr);
    DataArray* cloned = arr->Clone(true, false, 1);
    {
    DataNode size_node(size);
    DataNode* node = cloned->GetNodeAtIndex(cloned->GetNodeCount() - 1);
    *node = size_node;
    }
    InsertProperty(cloned, *EvaluateNodeAtIndex((DataArray*)da, 3));
    cloned->DecRefCount();
    return DataNode(size);
}

void Hmx::Object::SetTypeDef(DataArray* da){
    if(arr != da){
        if(arr != nullptr){
            arr->DecRefCount();
            arr = 0;
        }
        props.ClearAll(this);
        arr = da;
        if(da != nullptr) da->IncRefCount();
    }
}

extern const char* gNullStr;

Hmx::Object::Object() : arr(0), name(gNullStr), dir(0) { }

DataNode* Hmx::Object::Property(Symbol s, bool b){
    static DataArrayPtr d(DataNode(1));
    {
    DataNode sym_node(s);
    DataNode* ptr_node = d.GetNodeAtIndex(0);
    *ptr_node = sym_node;
    }
    return Property(d.arr, b);
}

bool Hmx::Object::SyncProperty(DataNode& dn, DataArray* da, int i, PropOp op){
    if(da->GetNodeCount() == i){
        return true;
    }
    else {
        Symbol b = da->GetSymAtIndex(i);
        return false;
    }
}

extern char* PathName(const Hmx::Object*);
extern void PropertyNOP(const char*, char*, String&);

DataNode* Hmx::Object::Property(DataArray* da, bool b){
    static DataNode n;
    if(SyncProperty(n, da, 0, (PropOp)1)) return &n;
    Symbol asdf = da->GetSymAtIndex(0);
    DataNode* kv = props.KeyValue(asdf, false);
    if(kv == nullptr){
        if(arr != nullptr){
            DataArray* found = arr->FindArray(asdf, b);
            if(found != nullptr){
                kv = EvaluateNodeAtIndex(found, 1);
            }
        }
    }
    if(kv != nullptr){
        int cnt = da->GetNodeCount();
        if(cnt == 1) return kv;
        else if(cnt == 2){
            if(kv->GetType() == kDataArray){
                DataArray* ret = kv->value.dataArray;
                return ret->GetNodeAtIndex(da->GetIntAtIndex(1));
            }
        }
        else if(b){
            String str;
            str << da;
            String str2(str);
            PropertyNOP("%s: property %s not found", PathName(this), str2);
        }
    }
    return nullptr;
}

DataNode Hmx::Object::HandleProperty(DataArray* a1, DataArray* a2, bool b){
    static DataNode n(a2, kDataArray);
    if(SyncProperty(n, a1, 0, (PropOp)0x20)){
        return DataNode(n);
    }
    if(b){
        if(a1 != nullptr) a1->GetSymAtIndex(0);
        else Symbol("<none>");
        PathName(this);
    }
    return DataNode(0);
}

void Hmx::Object::RemoveProperty(DataArray* da){
    static DataNode n;
    if(!SyncProperty(n, da, 0, (PropOp)8)){
        da->GetNodeCount();
        props.RemoveArrayValue(da->GetSymAtIndex(0), da->GetIntAtIndex(1), arr, this);
    }
}

void Hmx::Object::InsertProperty(DataArray* da, const DataNode& dn){
    if(!SyncProperty((DataNode&)dn, da, 0, (PropOp)4)){
        da->GetNodeCount();
        props.InsertArrayValue(da->GetSymAtIndex(0), da->GetIntAtIndex(1), dn, arr, this);
    }
}

int Hmx::Object::PropertySize(DataArray* da){
    static DataNode n;
    if(SyncProperty(n, da, 0, (PropOp)0x10)){
        return n.Int(nullptr);
    }
    else {
        da->GetNodeCount();
        Symbol asdf = da->GetSymAtIndex(0);
        DataNode* kv = props.KeyValue(asdf, false);
        if(kv == nullptr){
            if(arr != nullptr){
                kv = EvaluateNodeAtIndex(arr->FindArray(asdf, true), 1);
            }
            else PathName(this);
        }
        kv->GetType();
        return kv->value.dataArray->GetNodeCount();
    }
}

void Hmx::Object::Replace(Hmx::Object* obj1, Hmx::Object* obj2){
    props.Replace(obj1, obj2, this);
}

void Hmx::Object::SetProperty(Symbol s, const DataNode& dn){
    static DataArrayPtr d(DataNode(1));
    *(d.GetNodeAtIndex(0)) = DataNode(s);
    SetProperty(d.arr, dn);
}

void Hmx::Object::SetProperty(DataArray* da, const DataNode& dn){
    if(!SyncProperty((DataNode&)dn, da, 0, (PropOp)2)){
        Symbol asdf = asdf;
        asdf = da->GetSymAtIndex(0);
        if(da->GetNodeCount() == 1){
            props.SetKeyValue(asdf, dn, true, this);
        }
        else {
            da->GetNodeCount();
            props.SetArrayValue(asdf, da->GetIntAtIndex(1), dn, arr, this);
        }
    }
}

void Hmx::Object::ClearProperties(DataArray* da){
    int size = PropertySize(da);
    DataArray* cloned = da->Clone(true, false, 1);
    while(size-- != 0){
        *(cloned->GetNodeAtIndex(cloned->GetNodeCount() - 1)) = DataNode(size);
        RemoveProperty(cloned);
    }
    cloned->DecRefCount();
}

DataNode Hmx::Object::HandleType(DataArray* da){
    Symbol asdf = da->GetSymAtIndex(1);
    bool butt = false;
    DataArray* found;
    if(arr != nullptr){
        found = arr->FindArray(asdf, false);
        if(found != nullptr) butt = true;
    }
    if(butt){
        return found->ExecuteScript(1, this, (const DataArray*)da, 2);
    }
    else return DataNode(kDataUnhandled, 0);
}

extern bool IsASubclass(Symbol, Symbol);
extern char* PathName(const Hmx::Object*);

// see scratch: https://decomp.me/scratch/9abtP
DataNode Hmx::Object::Handle(DataArray* da, bool b){
    Symbol sym = da->GetSymAtIndex(1);
    static Symbol SymGet("get");
    if(sym == SymGet){
        DataNode got = OnGet(da);
        if(got.GetType() != kDataUnhandled) return DataNode(got);
    }
    static Symbol SymGetArray("get_array");
    if(sym == SymGetArray){
        return OnGetArray(da, da->GetSymAtIndex(2));
    }
    static Symbol SymSize("size");
    if(sym == SymSize){
        return DataNode(PropertySize(da->GetArrayAtIndex(2)));
    }
    static Symbol SymSet("set");
    if(sym == SymSet){
        DataNode set = OnSet(da);
        if(set.GetType() != kDataUnhandled) return DataNode(set);
    }
    static Symbol SymInsert("insert");
    if(sym == SymInsert){
        InsertProperty(da->GetArrayAtIndex(2), *EvaluateNodeAtIndex(da, 3));
        return DataNode(0);
    }
    static Symbol SymRemove("remove");
    if(sym == SymRemove){
        RemoveProperty(da->GetArrayAtIndex(2));
        return DataNode(0);
    }
    static Symbol SymClear("clear");
    if(sym == SymClear){
        ClearProperties(da->GetArrayAtIndex(2));
        return DataNode(0);
    }
    static Symbol SymAppend("append");
    if(sym == SymAppend){
        DataNode app = OnAppendToArray(da);
        if(app.GetType() != kDataUnhandled) return DataNode(app);
    }
    static Symbol SymHas("has");
    if(sym == SymHas){
        return DataNode(Property(da->GetArrayAtIndex(2), false) != 0);
    }
    static Symbol SymPropHandle("prop_handle");
    if(sym == SymPropHandle){
        return HandleProperty(da, da->GetArrayAtIndex(2), true);
    }
    static Symbol SymCopy("copy");
    if(sym == SymCopy){
        Copy(da->GetObjAtIndex(2), (CopyType)da->GetIntAtIndex(3));
        return DataNode(0);
    }
    static Symbol SymReplace("replace");
    if(sym == SymReplace){
        Replace(da->GetObjAtIndex(2), da->GetObjAtIndex(3));
        return DataNode(0);
    }
    static Symbol SymClassName("class_name");
    if(sym == SymClassName){
        return DataNode(ClassName());
    }
    static Symbol SymName("name");
    if(sym == SymName){
        return DataNode(name);
    }
    static Symbol SymIterateRefs("iterate_refs");
    if(sym == SymIterateRefs){
        DataNode refs = OnIterateRefs(da);
        if(refs.GetType() != kDataUnhandled) return DataNode(refs);
    }
    static Symbol SymDir("dir");
    if(sym == SymDir){

    }
    static Symbol SymSetName("set_name");
    if(sym == SymSetName){

    }
    static Symbol SymSetType("set_type");
    if(sym == SymSetType){
        SetType(da->GetSymAtIndex(2));
        return DataNode(0);
    }
    static Symbol SymIsA("is_a");
    if(sym == SymIsA){
        return DataNode(IsASubclass(ClassName(), da->GetSymAtIndex(2)));
    }
    static Symbol SymGetType("get_type");
    if(sym == SymGetType){
        return DataNode(Type());
    }
    static Symbol SymGetHeap("get_heap");
    if(sym == SymGetHeap){
        
    }
}
