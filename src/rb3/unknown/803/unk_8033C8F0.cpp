#include "hmx/object.hpp"
#include "data.hpp"

DataArray* TypeProps::GetArray(Symbol s, DataArray* da, ObjRef* ref){
    DataNode* kv = KeyValue(s, false);
    DataArray* ret;
    if(kv == nullptr){
        DataArray* yuh = da->FindArray(s, true)->GetArrayAtIndex(1)->Clone(true, false, 0);
        {
        const DataNode turnt(yuh, kDataArray);
        SetKeyValue(s, turnt, true, ref);
        }
        yuh->DecRefCount();
        ret = yuh;
    }
    else {
        kv->GetType();
        ret = kv->value.dataArray;
    }
    return ret;
}

void TypeProps::SetArrayValue(Symbol s, int i, const DataNode& dn, DataArray* da, ObjRef* ref){
    DataNode* node = GetArray(s, da, ref)->GetNodeAtIndex(i);
    if(node->GetType() == kDataObject){
        Hmx::Object* obj = node->value.objVal;
        if(obj != nullptr){
            obj->Release(ref);
        }
    }
    *node = dn;
    if(node->GetType() == kDataObject){
        Hmx::Object* obj = node->value.objVal;
        if(obj != nullptr){
            obj->AddRef(ref);
        }
    }
}

void TypeProps::RemoveArrayValue(Symbol s, int i, DataArray* da, ObjRef* ref){
    DataArray* arr = GetArray(s, da, ref);
    DataNode* node = arr->GetNodeAtIndex(i);
    if(node->GetType() == kDataObject){
        Hmx::Object* obj = node->value.objVal;
        if(obj != nullptr){
            obj->Release(ref);
        }
    }
    arr->Remove(i);
}

void TypeProps::InsertArrayValue(Symbol s, int i, const DataNode& node, DataArray* arr, ObjRef* ref){
    DataArray* asdf = GetArray(s, arr, ref);
    asdf->Insert(i, node);
    if(node.GetType() == kDataObject){
        Hmx::Object* obj = node.value.objVal;
        if(obj != nullptr){
            obj->AddRef(ref);
        }
    }
}

void TypeProps::ReplaceObject(DataNode& dn, Hmx::Object* obj1, Hmx::Object* obj2, ObjRef* ref){
    Hmx::Object* obj_loc = dn.value.objVal;
    if(obj_loc == obj1){
        obj_loc->Release(ref);
        dn = DataNode(obj2);
        if(obj2 != nullptr) obj2->AddRef(ref);
    } 
}

void TypeProps::ClearAll(ObjRef* ref){
    ReleaseObjects(ref);
    if(data != nullptr){
        data->DecRefCount();
        data = 0;
    }
}