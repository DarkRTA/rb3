#include "obj/Object.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "utl/PoolAlloc.h"
#include "utl/Loader.h"
#include <new>

extern LoadMgr TheLoadMgr;

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

void TypeProps::SetKeyValue(Symbol key, const DataNode& value, bool b, Hmx::Object* ref){
    if(b && value.Type() == kDataObject){
        Hmx::Object* o = value.mValue.object;
        if(o) o->AddRef(ref);
    }
    if(!mMap){
        mMap = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(2);
        mMap->Node(0) = key;
        mMap->Node(1) = value;
    }
    else {
        int nodeCnt = mMap->Size();
        for(int cnt = nodeCnt - 2; cnt >= 0; cnt -= 2){
            int symstr = (int)((const DataArray*)mMap)->Node(cnt).mValue.symbol;
            int keystr = (int)key.Str();
            if(symstr == keystr){
                DataNode& n = mMap->Node(cnt + 1);
                if(n.Type() == kDataObject){
                    Hmx::Object* o = n.mValue.object;
                    if(o) o->Release(ref);
                }
                n = value;
                return;
            }
        }

        mMap->Resize(nodeCnt + 2);
        mMap->Node(nodeCnt) = DataNode(key);
        mMap->Node(nodeCnt + 1) = value;
    }
}

DataNode* TypeProps::KeyValue(Symbol key, bool fail) const {
    if(mMap != 0){
        for(int i = mMap->Size() - 2; i >= 0; i -= 2){
            int symstr = (int)((const DataArray*)mMap)->Node(i).mValue.symbol;
            int keystr = (int)key.Str();
            if(symstr == keystr){
                return &mMap->Node(i + 1);
            }
        }
    }
    if(fail) MILO_FAIL("Key %s not found", key);
    return 0;
}

void GetSaveFlags(DataArray* arr, bool& proxy, bool& none){
    if(arr != 0){
        for(int i = 2; i < arr->Size(); i++){
            if(arr->Sym(i) == proxy_save) proxy = true;
            else if(arr->Sym(i) == no_save) none = true;
            else MILO_WARN("Unknown type def attribute %s", arr->Sym(i));
        }
    }
}

// https://decomp.me/scratch/igDEo
void TypeProps::Save(BinStream& d, Hmx::Object* ref){
    DataArray* arr = mMap;
    DataArray* def = ref->mTypeDef;
    if(arr && TheLoadMgr.mCacheMode && def->Size() != 0){
        int i9 = 0;
        while(arr){
            while(true){
                arr = mMap;
                if(!mMap || mMap->Size() <= i9) break;
                arr = def->FindArray(arr->Sym(i9), false);
                if(!arr) break;
                DataNode& n10 = arr->Node(1);
                if(n10.Type() != kDataCommand){
                    if(!arr->Node(1).CompatibleType(mMap->Node(i9 + 1).Type())){
                        break;
                    }
                }
                i9 += 2;
            }
            arr = mMap;
            ClearKeyValue(arr->Sym(i9), ref);
            arr = mMap;
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

Symbol TypeProps::Key(int i) const {
    MILO_ASSERT(mMap, 0x1CC);
    return STR_TO_SYM(mMap->Node(i * 2).mValue.symbol);
}

DataNode& TypeProps::Value(int i) const {
    MILO_ASSERT(mMap, 0x1D2);
    return mMap->Node(i * 2 + 1);
}

void TypeProps::ClearKeyValue(Symbol key, Hmx::Object* ref){
    if(mMap != 0){
        int cnt = mMap->Size() - 2;
        while(cnt >= 0){
            int symstr = (int)((const DataArray*)mMap)->Node(cnt).mValue.symbol;
            int keystr = (int)key.Str();
            if(symstr == keystr){
                DataNode& n = mMap->Node(cnt + 1);
                if(n.Type() == kDataObject){
                    Hmx::Object* obj = n.mValue.object;
                    if(obj) obj->Release(ref);
                }
                mMap->Remove(cnt);
                mMap->Remove(cnt);
                if(mMap->Size() == 0 && mMap){
                    mMap->Release();
                    mMap = 0;
                }
                return;
            }
            cnt -= 2;
        }
    }    
}

void TypeProps::ClearAll(Hmx::Object* ref){
    ReleaseObjects(ref);
    if(mMap != 0){
        mMap->Release();
        mMap = 0;
    }
}
