#include "hmx/object.hpp"
#include "data.hpp"
#include "common.hpp"

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

Hmx::Object::Object(){
    arr = 0;
    name = gNullStr;
    dir = 0;
}

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
        Symbol asdf = da->GetSymAtIndex(i);
        return false;
    }
}

extern char* PathName(const Hmx::Object*);

DataNode* Hmx::Object::Property(DataArray* da, bool b){
    static DataNode n;
    if(SyncProperty(n, da, 0, (PropOp)1)) return &n;
    Symbol asdf = da->GetSymAtIndex(0);
    DataNode* kv = props.KeyValue(asdf, false);
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
        if(kv != &n){
            if(arr != nullptr){
                arr->FindArray(asdf, true);
            }
        }
    }
}

void Hmx::Object::Replace(Hmx::Object* obj1, Hmx::Object* obj2){
    props.Replace(obj1, obj2, this);
}