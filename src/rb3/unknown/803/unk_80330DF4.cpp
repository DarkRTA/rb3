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