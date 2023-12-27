#include "hmx/object.hpp"
#include "data.hpp"
#include "textfile.hpp"
#include "formatstring.hpp"
#include "debug.hpp"

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

int TypeProps::Size() const {
    if(data != nullptr) return data->GetNodeCount() / 2;
    else return 0;
}

void TypeProps::Replace(Hmx::Object* obj1, Hmx::Object* obj2, ObjRef* ref){
    if(data != nullptr){
        for(int cnt = data->GetNodeCount() - 1; cnt > 0; cnt -= 2){
            DataNode* node = data->GetNodeAtIndex(cnt);
            if(node->GetType() == kDataObject){
                ReplaceObject(*node, obj1, obj2, ref);
            }
            else if(node->GetType() == kDataArray){
                DataArray* innerArr = node->value.dataArray;
                for(int cnt2 = innerArr->GetNodeCount() - 1; cnt2 >= 0; cnt2--){
                    DataNode* innerNode = innerArr->GetNodeAtIndex(cnt2);
                    if(innerNode->GetType() == kDataObject){
                        ReplaceObject(*innerNode, obj1, obj2, ref);
                    }
                }
            }
        }
    }
}

void TypeProps::ReleaseObjects(ObjRef* ref){
    if(data != nullptr){
        for(int cnt = data->GetNodeCount() - 1; cnt > 0; cnt -= 2){
            DataNode* node = data->GetNodeAtIndex(cnt);
            if(node->GetType() == kDataObject){
                Hmx::Object* obj = node->value.objVal;
                if(obj != nullptr) obj->Release(ref);
            }
            else if(node->GetType() == kDataArray){
                DataArray* innerArr = node->value.dataArray;
                for(int cnt2 = innerArr->GetNodeCount() - 1; cnt2 >= 0; cnt2--){
                    DataNode* innerNode = innerArr->GetNodeAtIndex(cnt2);
                    if(innerNode->GetType() == kDataObject){
                        Hmx::Object* obj = innerNode->value.objVal;
                        if(obj != nullptr) obj->Release(ref);
                    }
                }
            }
        }
    }
}

void TypeProps::AddRefObjects(ObjRef* ref){
    if(data != nullptr){
        for(int cnt = data->GetNodeCount() - 1; cnt > 0; cnt -= 2){
            DataNode* node = data->GetNodeAtIndex(cnt);
            if(node->GetType() == kDataObject){
                Hmx::Object* obj = node->value.objVal;
                if(obj != nullptr) obj->AddRef(ref);
            }
            else if(node->GetType() == kDataArray){
                DataArray* innerArr = node->value.dataArray;
                for(int cnt2 = innerArr->GetNodeCount() - 1; cnt2 >= 0; cnt2--){
                    DataNode* innerNode = innerArr->GetNodeAtIndex(cnt2);
                    if(innerNode->GetType() == kDataObject){
                        Hmx::Object* obj = innerNode->value.objVal;
                        if(obj != nullptr) obj->AddRef(ref);
                    }
                }
            }
        }
    }
}

void TypeProps::Assign(const TypeProps& tp, ObjRef* ref){
    ClearAll(ref);
    if(tp.data != nullptr){
        data = tp.data->Clone(true, false, 0);
    }
    AddRefObjects(ref);
}

Symbol TextFile::ClassName() const {
    return StaticClassName();
}

TextFile::~TextFile(){
    if(unk20 != 0){
        delete this;
    }
}

void TextFile::SetName(const char* c, ObjectDir* dir){
    Hmx::Object::SetName(c, dir);
    delete this;
    unk20 = 0;
}

DataNode TextFile::OnPrint(DataArray* da){
    if(unk20 != 0){
        for(int i = 2; i < da->GetNodeCount(); i++){
            DataNode* eval = EvaluateNodeAtIndex(da, i);
            eval->Print(*this, true);
        }
    }
    return DataNode(0);
}

DataNode TextFile::OnPrintf(DataArray* da){
    if(unk20 != 0){
        FormatString fs(da->GetStrAtIndex(2));
        for(int i = 3; i < da->GetNodeCount(); i++){
            fs << *EvaluateNodeAtIndex(da, i);
        }
        Print(fs.Str());
    }
    return DataNode(0);
}

extern Symbol SymPrint, SymReflect;
extern char* PathName(const Hmx::Object*);

DataNode TextFile::Handle(DataArray* da, bool b){
    Symbol match = match;
    match = da->GetSymAtIndex(1);
    if(match == SymPrint){
        DataNode print = OnPrint(da);
        if(print.GetType() != kDataUnhandled) return DataNode(print);
    }
    static Symbol SymPrintf("printf");
    if(match == SymPrintf){
        DataNode node_printf = OnPrintf(da);
        if(node_printf.GetType() != kDataUnhandled) return DataNode(node_printf);
    }
    if(match == SymReflect){
        DataNode ref = OnReflect(da);
        if(ref.GetType() != kDataUnhandled) return DataNode(ref);
    }
    // if no match, fall to here
    {
    DataNode base = Hmx::Object::Handle(da, false);
    if(base.GetType() != kDataUnhandled) return DataNode(base);
    }
    if(b) PathName(this);
    return DataNode(kDataUnhandled, 0);
}

extern DataArray* SystemConfig(Symbol, Symbol, Symbol);

void TextFile::SetType(Symbol s){
    static DataArray* types = SystemConfig(StaticClassName(), "types", "objects");
    if(s.IsNull()) SetTypeDef(nullptr);
    else {
        DataArray* found = types->FindArray(s, false);
        if(found != nullptr){
            SetTypeDef(found);
        }
        else {
            PathName(this);
            ClassName();
            SetTypeDef(nullptr);
        }
    }
}

extern DataArray* SystemConfig(Symbol);

void InitObject(Hmx::Object* obj){
    static DataArray* objects = SystemConfig("objects");
    static Symbol initSym("init");
    obj->ClassName();
    DataArray* found1 = objects->FindArray(initSym, true);
    DataArray* found2 = found1->FindArray(initSym, false);
    if(found2 != nullptr)
        found2->ExecuteScript(1, obj, nullptr, 1);
}

char* PathName(const Hmx::Object* obj){
    if(obj != nullptr) ((Hmx::Object*)obj)->FindPathName();
    else return "NULL Object";
}

const char* SafeName(Hmx::Object* obj){
    if(obj != nullptr) return obj->Name();
    else return "NULL";
}