#include "obj/Object.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbols.h"
#include "utl/PoolAlloc.h"
#include "utl/Loader.h"
#include "obj/DataUtl.h"
#include "obj/Dir.h"
#include <new>

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
        mMap = new DataArray(2);
        mMap->Node(0) = key;
        mMap->Node(1) = value;
    }
    else {
        int nodeCnt = mMap->Size();
        for(int cnt = nodeCnt - 2; cnt >= 0; cnt -= 2){
            int symstr = (int)CONST_ARRAY(mMap)->Node(cnt).mValue.symbol;
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
            int symstr = (int)CONST_ARRAY(mMap)->Node(i).mValue.symbol;
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
    // begin debug exclusive
    if(mMap){
        if(TheLoadMgr.EditMode()){
            const DataArray* def = ref->TypeDef();
            if(def){
                int i = 0;
                while(mMap && i < mMap->Size()){
                    DataArray* theArr = def->FindArray(mMap->Sym(i), false);
                    if(theArr){
                        DataNode& node = CONST_ARRAY(theArr)->Node(1);
                        if(node.Type() == kDataCommand) goto next;
                        if(theArr->Node(1).CompatibleType(CONST_ARRAY(mMap)->Node(i + 1).Type()))
                            goto next;
                    }
                    ClearKeyValue(mMap->Sym(i), ref);
                    if(mMap) continue;
                    else break;
            next:
                    i += 2;
                }
            }
        }
    }
    // end debug exclusive
    if(!mMap || ((Hmx::Object*)ref->DataDir() != ref) || ref == (Hmx::Object*)ref->Dir() && !gLoadingProxyFromDisk){
        d << mMap;
        return;
    }
    const DataArray* theTypeDef = ref->TypeDef();
    if(!theTypeDef){
        MILO_WARN("%s: Removing type properties without type definition", ref->Name());
        d << (DataArray*)0;
        return;
    }
    DataArray* potentialArr = 0;
    int keyIdx = 0;
    for(int i = 0; i < mMap->Size(); i += 2){
        Symbol sym = mMap->Sym(i);
        DataArray* found = theTypeDef->FindArray(sym, false);
        if(found){
            bool b1 = false;
            bool b2 = false;
            GetSaveFlags(found, b1, b2);
            if(!b2 && b1 != gLoadingProxyFromDisk){
                if(!potentialArr){
                    potentialArr = new DataArray(mMap->Size());
                }
                potentialArr->Node(keyIdx) = DataNode(sym);
                potentialArr->Node(keyIdx + 1) = mMap->Node(i + 1);
                keyIdx += 2;
            }
        }
    }
    if(potentialArr){
        potentialArr->Resize(keyIdx);
        d << potentialArr;
        potentialArr->Release();
        return;
    }
    d << potentialArr;
    
}

void TypeProps::Load(BinStream& d, bool old_proxy, Hmx::Object* ref){
    ReleaseObjects(ref);
    const DataArray* def = ref->TypeDef();
    Hmx::Object* theThis = 0;
    if(def) theThis = DataSetThis(ref);
    if(mMap && gLoadingProxyFromDisk && def){
        DataArray* arr = mMap;
        d >> mMap;
        int mapsize = arr->Size();
        for(int i = 0; i < mapsize; i += 2){
            Symbol sym = arr->Sym(i);
            if(old_proxy){
                bool b1 = false;
                bool b2 = false;
                GetSaveFlags(def->FindArray(sym, false), b1, b2);
                if(b1 || b2) continue;
            }
                SetKeyValue(sym, arr->Node(i + 1), false, ref);
        }
        arr->Release();
    }
    else {
        if(mMap){
            mMap->Release();
            mMap = 0;
        }
        d >> mMap;
    }

    if(def){
        if(mMap && TheLoadMgr.EditMode()){
            
            for(int i = 0; mMap && i < mMap->Size(); i += 2){
                DataArray* found = def->FindArray(mMap->Sym(i), false);
                if(!found || (CONST_ARRAY(found)->Node(1).Type() != kDataCommand) && !found->Node(1).CompatibleType(CONST_ARRAY(mMap)->Node(i + 1).Type())) {
                    TheDebug << MakeString("%s: type based property \"%s\" is outdated, will clear on save\n", PathName(ref), mMap->Sym(i));
                }
            }
        }
        DataSetThis(theThis);
        AddRefObjects(ref);
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
            int symstr = (int)CONST_ARRAY(mMap)->Node(cnt).mValue.symbol;
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
