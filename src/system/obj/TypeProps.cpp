#include "obj/Object.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Str.h"
#include "utl/MakeString.h"
// #include <new>
// #include "symbols.hpp"
extern Debug TheDebug;
extern const char* kAssertStr;

DataArray* TypeProps::GetArray(Symbol prop, DataArray* typeDef, Hmx::Object* ref){
    DataNode* kv = KeyValue(prop, false);
    DataArray* ret;
    if(kv == 0){
        if(typeDef == 0){
            TheDebug.Fail(MakeString<const char*, int, const char*>(kAssertStr, "TypeProps.cpp", 0x16, "typeDef"));
        }
        DataArray* yuh = typeDef->FindArray(prop, true)->Array(1)->Clone(true, false, 0);
        SetKeyValue(prop, DataNode(yuh, kDataArray), true, ref);
        yuh->Release();
        ret = yuh;
    }
    else {
        if(kv->Type() != kDataArray){
            TheDebug.Fail(MakeString<const char*, int, const char*>(kAssertStr, "TypeProps.cpp", 0x1D, "n->Type() == kDataArray"));
        }
        ret = kv->mValue.array;
    }
    return ret;
}

// void TypeProps::SetArrayValue(Symbol prop, int i, const DataNode& val, DataArray* da, ObjRef* ref){
//     DataNode* node = &(GetArray(prop, da, ref)->Node(i));
//     if(node->Type() == kDataObject){
//         Hmx::Object* obj = node->mValue.object;
//         if(obj != nullptr){
//             obj->Release(ref);
//         }
//     }
//     *node = val;
//     if(node->Type() == kDataObject){
//         Hmx::Object* obj = node->mValue.object;
//         if(obj != nullptr){
//             obj->AddRef(ref);
//         }
//     }
// }

// void TypeProps::RemoveArrayValue(Symbol prop, int i, DataArray* da, ObjRef* ref){
//     DataArray* arr = GetArray(prop, da, ref);
//     DataNode* node = &(arr->Node(i));
//     if(node->Type() == kDataObject){
//         Hmx::Object* obj = node->mValue.object;
//         if(obj != nullptr){
//             obj->Release(ref);
//         }
//     }
//     arr->Remove(i);
// }

// void TypeProps::InsertArrayValue(Symbol prop, int i, const DataNode& val, DataArray* arr, ObjRef* ref){
//     DataArray* asdf = GetArray(prop, arr, ref);
//     asdf->Insert(i, val);
//     if(val.Type() == kDataObject){
//         Hmx::Object* obj = val.mValue.object;
//         if(obj != nullptr){
//             obj->AddRef(ref);
//         }
//     }
// }

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

// DataNode* TypeProps::KeyValue(Symbol key, bool fail){
//     if(mDataDict != nullptr){
//         for(int i = mDataDict->Size() - 2; i >= 0; i -= 2){
//             const char* str = key.Str();
//             if(mDataDict->Union(i).symbol == str){
//                 return &mDataDict->Node(i + 1);
//             }
//         }
//     }
//     return nullptr;
// }

// void GetSaveSymbolInfo(DataArray* arr, bool& b1, bool& b2){
//     if(arr != 0){
//         for(int i = 2; i < arr->Size(); i++){
//             if(arr->Sym(i) == SymProxySave){
//                 b1 = true;
//             }
//             else if(arr->Sym(i) == SymNoSave){
//                 b2 = true;
//             }
//             else arr->Sym(i);
//         }
//     }
// }

// void TypeProps::ReplaceObject(DataNode& n, Hmx::Object* from, Hmx::Object* to, ObjRef* ref){
//     Hmx::Object* o = n.mValue.object;
//     if(o == from){
//         o->Release(ref);
//         n = DataNode(to);
//         if(to != nullptr) to->AddRef(ref);
//     }
// }

// void TypeProps::Replace(Hmx::Object* from, Hmx::Object* to, ObjRef* ref){
//     if(mDataDict != nullptr){
//         for(int cnt = mDataDict->Size() - 1; cnt > 0; cnt -= 2){
//             DataNode* node = &mDataDict->Node(cnt);
//             if(node->Type() == kDataObject){
//                 ReplaceObject(*node, from, to, ref);
//             }
//             else if(node->Type() == kDataArray){
//                 DataArray* innerArr = node->mValue.array;
//                 for(int cnt2 = innerArr->Size() - 1; cnt2 >= 0; cnt2--){
//                     DataNode* innerNode = &innerArr->Node(cnt2);
//                     if(innerNode->Type() == kDataObject){
//                         ReplaceObject(*innerNode, from, to, ref);
//                     }
//                 }
//             }
//         }
//     }
// }

// int TypeProps::Size() const {
//     if(mDataDict != nullptr) return mDataDict->Size() / 2;
//     else return 0;
// }

// void TypeProps::ReleaseObjects(ObjRef* ref){
//     if(mDataDict != nullptr){
//         for(int cnt = mDataDict->Size() - 1; cnt > 0; cnt -= 2){
//             DataNode* node = &mDataDict->Node(cnt);
//             if(node->Type() == kDataObject){
//                 Hmx::Object* obj = node->mValue.object;
//                 if(obj != nullptr) obj->Release(ref);
//             }
//             else if(node->Type() == kDataArray){
//                 DataArray* innerArr = node->mValue.array;
//                 for(int cnt2 = innerArr->Size() - 1; cnt2 >= 0; cnt2--){
//                     DataNode* innerNode = &innerArr->Node(cnt2);
//                     if(innerNode->Type() == kDataObject){
//                         Hmx::Object* obj = innerNode->mValue.object;
//                         if(obj != nullptr) obj->Release(ref);
//                     }
//                 }
//             }
//         }
//     }
// }


// void TypeProps::AddRefObjects(ObjRef* ref){
//     if(mDataDict != nullptr){
//         for(int cnt = mDataDict->Size() - 1; cnt > 0; cnt -= 2){
//             DataNode* node = &mDataDict->Node(cnt);
//             if(node->Type() == kDataObject){
//                 Hmx::Object* obj = node->mValue.object;
//                 if(obj != nullptr) obj->AddRef(ref);
//             }
//             else if(node->Type() == kDataArray){
//                 DataArray* innerArr = node->mValue.array;
//                 for(int cnt2 = innerArr->Size() - 1; cnt2 >= 0; cnt2--){
//                     DataNode* innerNode = &innerArr->Node(cnt2);
//                     if(innerNode->Type() == kDataObject){
//                         Hmx::Object* obj = innerNode->mValue.object;
//                         if(obj != nullptr) obj->AddRef(ref);
//                     }
//                 }
//             }
//         }
//     }
// }

// TypeProps& TypeProps::Assign(const TypeProps& prop, ObjRef* ref){
//     ClearAll(ref);
//     if(prop.mDataDict != nullptr){
//         mDataDict = prop.mDataDict->Clone(true, false, 0);
//     }
//     AddRefObjects(ref);
// }

// void TypeProps::ClearAll(ObjRef* ref){
//     ReleaseObjects(ref);
//     if(mDataDict != nullptr){
//         mDataDict->Release();
//         mDataDict = 0;
//     }
// }
