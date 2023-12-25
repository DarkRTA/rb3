#include "hmx/object.hpp"
#include "data.hpp"
#include "common.hpp"

DataNode Hmx::Object::OnGetArray(const DataArray* da){
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
        props.ClearAll();
        arr = da;
        if(da != nullptr) da->IncRefCount();
    }
}

extern const char* gNullStr;

Hmx::Object::Object(){
    arr = 0;
    name = gNullStr;
    unk10 = 0;
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
    else {
        return nullptr;
    }
}
