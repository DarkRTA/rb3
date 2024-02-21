#include "obj/Object.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
// #include <new>
// #include "symbols.hpp"

DataArray* TypeProps::GetArray(Symbol prop, DataArray* typeDef, Hmx::Object* ref){
    DataNode* n = KeyValue(prop, false);
    DataArray* ret;
    if(n == 0){
        MILO_ASSERT(typeDef, 0x16);
        DataArray* yuh = typeDef->FindArray(prop, true)->Array(1)->Clone(true, false, 0);
        SetKeyValue(prop, DataNode(yuh, kDataArray), true, ref);
        yuh->Release();
        ret = yuh;
    }
    else {
        MILO_ASSERT(n->Type() == kDataArray, 0x1D);
        ret = n->mValue.array;
    }
    return ret;
}

void TypeProps::SetArrayValue(Symbol prop, int i, const DataNode& val, DataArray* da, Hmx::Object* ref){
    DataNode* node = &(GetArray(prop, da, ref)->Node(i));
    if(node->Type() == kDataObject){
        Hmx::Object* obj = node->mValue.object;
        if(obj != 0){
            obj->Release(ref);
        }
    }
    *node = val;
    if(node->Type() == kDataObject){
        Hmx::Object* obj = node->mValue.object;
        if(obj != 0){
            obj->AddRef(ref);
        }
    }
}

void TypeProps::RemoveArrayValue(Symbol prop, int i, DataArray* da, Hmx::Object* ref){
    DataArray* arr = GetArray(prop, da, ref);
    DataNode* node = &(arr->Node(i));
    if(node->Type() == kDataObject){
        Hmx::Object* obj = node->mValue.object;
        if(obj != 0){
            obj->Release(ref);
        }
    }
    arr->Remove(i);
}

void TypeProps::InsertArrayValue(Symbol prop, int i, const DataNode& val, DataArray* arr, Hmx::Object* ref){
    DataArray* asdf = GetArray(prop, arr, ref);
    asdf->Insert(i, val);
    if(val.Type() == kDataObject){
        Hmx::Object* obj = val.mValue.object;
        if(obj != 0){
            obj->AddRef(ref);
        }
    }
}

// void TypeProps::SetKeyValue(Symbol key, const DataNode& value, bool b, ObjRef* ref){
//     if(b && value.Type() == kDataObject){
//         Hmx::Object* o = value.mValue.object;
//         if(o != nullptr) o->AddRef(ref);
//     }
//     if(mDataDict == nullptr){
//         mDataDict = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(2);
//         mDataDict->Node(0) = key;
//         mDataDict->Node(1) = value;
//     }
//     else {
//         int nodeCnt = mDataDict->Size();
//         for(int cnt = nodeCnt - 2; cnt >= 0; cnt -= 2){
//             const char* str = key.Str();
//             if(mDataDict->Union(cnt).symbol == str){
//                 DataNode* n = &mDataDict->Node(cnt + 1);
//                 if(n->Type() == kDataObject){
//                     Hmx::Object* o = n->mValue.object;
//                     if(o != nullptr) o->Release(ref);
//                 }
//                 *n = value;
//                 return;
//             }
//         }

//         mDataDict->Resize(nodeCnt + 2);
//         mDataDict->Node(nodeCnt) = DataNode(key);
//         mDataDict->Node(nodeCnt + 1) = value;
//     }
// }

DataNode* TypeProps::KeyValue(Symbol key, bool fail) const {
    if(mMap != 0){
        for(int i = mMap->Size() - 2; i >= 0; i -= 2){
            if(mMap->Node(i).mValue.symbol == key.Str()){
                return &mMap->Node(i + 1);
            }
        }
    }
    if(fail) FAIL("Key %s not found", key);
    return 0;
}

void GetSaveFlags(DataArray* arr, bool& proxy, bool& none){
    if(arr != 0){
        for(int i = 2; i < arr->Size(); i++){
            if(arr->Sym(i) == proxy_save) proxy = true;
            else if(arr->Sym(i) == no_save) none = true;
            else WARN("Unknown type def attribute %s", arr->Sym(i));
        }
    }
}

void TypeProps::ReplaceObject(DataNode& n, Hmx::Object* from, Hmx::Object* to, Hmx::Object* ref){
    Hmx::Object* o = n.mValue.object;
    if(o == from){
        o->Release(ref);
        n = DataNode(to);
        if(to != 0) to->AddRef(ref);
    }
}

void TypeProps::Replace(Hmx::Object* from, Hmx::Object* to, Hmx::Object* ref){
    if(mMap != 0){
        for(int cnt = mMap->Size() - 1; cnt > 0; cnt -= 2){
            DataNode* node = &mMap->Node(cnt);
            if(node->Type() == kDataObject){
                ReplaceObject(*node, from, to, ref);
            }
            else if(node->Type() == kDataArray){
                DataArray* innerArr = node->mValue.array;
                for(int cnt2 = innerArr->Size() - 1; cnt2 >= 0; cnt2--){
                    DataNode* innerNode = &innerArr->Node(cnt2);
                    if(innerNode->Type() == kDataObject){
                        ReplaceObject(*innerNode, from, to, ref);
                    }
                }
            }
        }
    }
}

int TypeProps::Size() const {
    if(mMap != 0) return mMap->Size() / 2;
    else return 0;
}

void TypeProps::ReleaseObjects(Hmx::Object* ref){
    if(mMap != 0){
        for(int cnt = mMap->Size() - 1; cnt > 0; cnt -= 2){
            DataNode* node = &mMap->Node(cnt);
            if(node->Type() == kDataObject){
                Hmx::Object* obj = node->mValue.object;
                if(obj != 0) obj->Release(ref);
            }
            else if(node->Type() == kDataArray){
                DataArray* innerArr = node->mValue.array;
                for(int cnt2 = innerArr->Size() - 1; cnt2 >= 0; cnt2--){
                    DataNode* innerNode = &innerArr->Node(cnt2);
                    if(innerNode->Type() == kDataObject){
                        Hmx::Object* obj = innerNode->mValue.object;
                        if(obj != 0) obj->Release(ref);
                    }
                }
            }
        }
    }
}


void TypeProps::AddRefObjects(Hmx::Object* ref){
    if(mMap != 0){
        for(int cnt = mMap->Size() - 1; cnt > 0; cnt -= 2){
            DataNode* node = &mMap->Node(cnt);
            if(node->Type() == kDataObject){
                Hmx::Object* obj = node->mValue.object;
                if(obj != 0) obj->AddRef(ref);
            }
            else if(node->Type() == kDataArray){
                DataArray* innerArr = node->mValue.array;
                for(int cnt2 = innerArr->Size() - 1; cnt2 >= 0; cnt2--){
                    DataNode* innerNode = &innerArr->Node(cnt2);
                    if(innerNode->Type() == kDataObject){
                        Hmx::Object* obj = innerNode->mValue.object;
                        if(obj != 0) obj->AddRef(ref);
                    }
                }
            }
        }
    }
}

TypeProps& TypeProps::Copy(const TypeProps& prop, Hmx::Object* ref){
    ClearAll(ref);
    if(prop.mMap != 0){
        mMap = prop.mMap->Clone(true, false, 0);
    }
    AddRefObjects(ref);
}

// return type might be a Symbol? not sure
DataNode* TypeProps::Key(int i) const {
    MILO_ASSERT(mMap, 0x1CC);
    return &mMap->Node(i * 2);
}

DataNode& TypeProps::Value(int i) const {
    MILO_ASSERT(mMap, 0x1D2);
    return mMap->Node(i * 2 + 1);
}

void TypeProps::ClearKeyValue(Symbol key, Hmx::Object* ref){
    if(mMap != 0){
        for(int cnt = mMap->Size() - 1; cnt > 0; cnt -= 2){

        }
    }
}

// void __thiscall TypeProps::ClearKeyValue(TypeProps *this,Symbol param_1,Object *param_2)

// {
//   short sVar1;
//   int iVar2;
//   int *piVar3;
//   Object **ppOVar4;
//   DataArray *this_00;
//   undefined3 in_register_00000010;
//   int iVar5;
  
//   if (*(int *)this != 0) {
//     iVar5 = (int)*(short *)(*(int *)this + 8);
//     do {
//       iVar2 = iVar5;
//       iVar5 = iVar2 + -2;
//       if (iVar5 < 0) {
//         return;
//       }
//       piVar3 = (int *)DataArray::Node(*(DataArray **)this,iVar5);
//     } while (*piVar3 != *(int *)CONCAT31(in_register_00000010,param_1));

//     ppOVar4 = (Object **)DataArray::Node(*(DataArray **)this,iVar2 + -1);
//     if ((ppOVar4[1] == (Object *)0x4) && (*ppOVar4 != (Object *)0x0)) {
//       Hmx::Object::Release(*ppOVar4,(ObjRef *)param_2);
//     }
//     DataArray::Remove(*(DataArray **)this,iVar5);
//     DataArray::Remove(*(DataArray **)this,iVar5);
//     this_00 = *(DataArray **)this;
//     if ((*(short *)(this_00 + 8) == 0) && (this_00 != (DataArray *)0x0)) {
//       sVar1 = *(short *)(this_00 + 10);
//       *(short *)(this_00 + 10) = sVar1 + -1;
//       if ((short)(sVar1 + -1) == 0) {
//         DataArray::~DataArray(this_00);
//       }
//       *(undefined4 *)this = 0;
//     }
//   }
//   return;
// }

void TypeProps::ClearAll(Hmx::Object* ref){
    ReleaseObjects(ref);
    if(mMap != 0){
        mMap->Release();
        mMap = 0;
    }
}
