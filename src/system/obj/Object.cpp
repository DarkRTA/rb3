#include "obj/Object.h"
#include "os/Debug.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Utl.h"
#include "obj/MessageTimer.h"
#include "os/OSFuncs.h"

extern Hmx::Object *gDataThis;

const char* blank = "";
const char* unk = "unknown";

INIT_REVS(Hmx::Object)

Hmx::Object* Hmx::Object::sDeleting = 0;
std::map<Symbol, ObjectFunc*> Hmx::Object::sFactories;

ObjectDir* Hmx::Object::DataDir(){
    if(mDir != 0) return mDir;
    else return ObjectDir::Main();
}

Hmx::Object* Hmx::Object::NewObject(Symbol s) {
    ObjectFunc* f = sFactories[s];
    if (f) return (*f)();
    else {
        MILO_FAIL("Unknown class %s", s);
        return NULL;
    }
}

void Hmx::Object::RegisterFactory(Symbol s, ObjectFunc* func){
    sFactories[s] = func;
}

bool Hmx::Object::RegisteredFactory(Symbol s){
    const std::map<Symbol, ObjectFunc*>::iterator it = sFactories.find(s);
    return it != sFactories.end();
}

Hmx::Object::Object() : mTypeDef(0), mName(gNullStr), mDir(0) { }

Hmx::Object& Hmx::Object::operator=(const Hmx::Object& obj){
    mName = obj.mName;
    mTypeDef = obj.mTypeDef;
    mTypeProps.Copy(obj.mTypeProps, this);
    mDir = obj.mDir;
    mRefs = obj.mRefs;
    return *this;
}

Hmx::Object::~Object(){
    mTypeProps.ClearAll(this);
    MILO_ASSERT(MainThread(), 0xA7);
    if(mTypeDef) mTypeDef->Release();
    mTypeDef = 0;
    RemoveFromDir();
    Hmx::Object* tmp = sDeleting;
    sDeleting = this;
    for(std::vector<ObjRef*>::reverse_iterator it = mRefs.rbegin(); it != mRefs.rend(); it++){
        (*it)->Replace(this, 0);
    }
    if(gDataThis == this) gDataThis = 0;
    sDeleting = tmp;
}

void Hmx::Object::SetName(const char* cc, class ObjectDir* dir){
    RemoveFromDir();
    if(cc == 0 || *cc == '\0'){
        mName = gNullStr;
        mDir = 0;
    }
    else {
        MILO_ASSERT(dir, 0xE0);
        mDir = dir;
        ObjectDir::Entry* entry = dir->FindEntry(cc, true);
        if(entry->obj) MILO_FAIL("%s already exists", cc);
        entry->obj = this;
        mName = entry->name;
        dir->AddedObject(this);
    }
}

void Hmx::Object::RemoveFromDir(){
    if(mDir){
        if(mDir != sDeleting){
            mDir->RemovingObject(this);
            ObjectDir::Entry* entry = mDir->FindEntry(mName, false);
            bool b = false;
            if(entry && entry->obj == this) b = true;
            if(!b){
                MILO_FAIL("No entry for %s in %s", PathName(this), PathName(mDir));
            }
            entry->obj = 0;
        }
    }
}

void Hmx::Object::SetTypeDef(DataArray* da){
    if(mTypeDef != da){
        if(mTypeDef != 0){
            mTypeDef->Release();
            mTypeDef = 0;
        }
        mTypeProps.ClearAll(this);
        mTypeDef = da;
        if(da != 0) da->AddRef();
    }
}

DataNode* Hmx::Object::Property(DataArray* prop, bool fail) const {
    static DataNode n(0);
    // if(SyncProperty(n, prop, 0, kPropGet)) return &n; // fails because n needs to be a DataNode&...why tho?
    Symbol name = prop->Sym(0);
    DataNode* kv = mTypeProps.KeyValue(name, false);
    if(!kv){
        if(mTypeDef){
            DataArray* found = mTypeDef->FindArray(name, fail);
            if(found) kv = &found->Evaluate(1);
        }
    }
    if(kv){
        int cnt = prop->Size();
        if(cnt == 1) return kv;
        else if(cnt == 2){
            if(kv->Type() == kDataArray){
                DataArray* ret = kv->mValue.array;
                return &ret->Node(prop->Int(1));
            }
        }
    }
    if(fail){
        String str;
        str << prop;
        MILO_FAIL("%s: property %s not found", PathName(this), String(str));
    }
    return 0;
}

DataNode* Hmx::Object::Property(Symbol prop, bool fail) const {
    static DataArrayPtr d(DataNode(1));
    d.Node(0) = DataNode(prop);
    return Property(d.mData, fail);
}

#pragma push
#pragma pool_data off
DataNode Hmx::Object::PropertyArray(Symbol sym){
    static DataArrayPtr d(DataNode(1));
    d.Node(0) = DataNode(sym);
    int size = PropertySize(d.mData);
    DataArray* newArr = new DataArray(size);
    static DataArrayPtr path(new DataArray(2));
    path.Node(0) = DataNode(sym);
    for(int i = 0; i < size; i++){
        path.Node(1) = DataNode(i);
        newArr->Node(i) = *Property(path.mData, true);
    }
    DataNode ret = DataNode(newArr, kDataArray);
    newArr->Release();
    return ret;
}
#pragma pop

DataNode Hmx::Object::HandleProperty(DataArray* prop, DataArray* a2, bool fail){
    static DataNode n(a2, kDataArray);
    if(SyncProperty(n, prop, 0, kPropHandle)){
        return DataNode(n);
    }
    if(fail){
        MILO_FAIL("%s: property %s not found", PathName(this), (prop != 0) ? prop->Sym(0) : "<none>");
    }
    return DataNode(0);
}

void Hmx::Object::SetProperty(DataArray* prop, const DataNode& val){
    if(!SyncProperty((DataNode&)val, prop, 0, kPropSet)){
        Symbol name = prop->Sym(0);
        if(prop->Size() == 1){
            mTypeProps.SetKeyValue(name, val, true, this);
        }
        else {
            MILO_ASSERT(prop->Size() == 2, 0x17D);
            mTypeProps.SetArrayValue(name, prop->Int(1), val, mTypeDef, this);
        }
    }
}

void Hmx::Object::SetProperty(Symbol prop, const DataNode& val){
    static DataArrayPtr d(DataNode(1));
    d.Node(0) = DataNode(prop);
    SetProperty(d.mData, val);
}

int Hmx::Object::PropertySize(DataArray* prop){
    static DataNode n;
    if(SyncProperty(n, prop, 0, kPropSize)){
        return n.Int(nullptr);
    }
    else {
        MILO_ASSERT(prop->Size() == 1, 0x192);
        Symbol name = prop->Sym(0);
        DataNode* a = mTypeProps.KeyValue(name, false);
        if(a == nullptr){
            if(mTypeDef != nullptr){
                a = &mTypeDef->FindArray(name, true)->Evaluate(1);
            }
            else MILO_FAIL("%s: property %s not found", PathName(this), name);
        }
        MILO_ASSERT(a->Type() == kDataArray, 0x1A1);
        return a->mValue.array->Size();
    }
}

void Hmx::Object::PropertyClear(DataArray* propArr){
    int size = PropertySize(propArr);
    DataArray* cloned = propArr->Clone(true, false, 1);
    while(size-- != 0){
        cloned->Node(cloned->Size() - 1) = DataNode(size);
        RemoveProperty(cloned);
    }
    cloned->Release();
}

void Hmx::Object::RemoveProperty(DataArray* prop){
    static DataNode n;
    if(!SyncProperty(n, prop, 0, kPropRemove)){
        MILO_ASSERT(prop->Size() == 2, 0x1BB);
        mTypeProps.RemoveArrayValue(prop->Sym(0), prop->Int(1), mTypeDef, this);
    }
}

void Hmx::Object::InsertProperty(DataArray* prop, const DataNode& val){
    if(!SyncProperty((DataNode&)val, prop, 0, kPropInsert)){
        MILO_ASSERT(prop->Size() == 2, 0x1C5);
        mTypeProps.InsertArrayValue(prop->Sym(0), prop->Int(1), val, mTypeDef, this);
    }
}

void Hmx::Object::AddRef(ObjRef* ref){
    if(ref->RefOwner() != this)
        mRefs.push_back(ref);
}

void Hmx::Object::Release(ObjRef* o){
    if(sDeleting != this && o->RefOwner() != this){
        for(std::vector<ObjRef*>::reverse_iterator i = mRefs.rbegin(); i != mRefs.rend(); i++){
            if(*(i.base()) == o){
                MILO_ASSERT(*(i.base()) == o, 0x1E6);
                mRefs.erase(i.base());
                return;
            }
        }
    }
}

void Hmx::Object::Save(BinStream& bs){
    SaveType(bs);
    SaveRest(bs);
}

void Hmx::Object::SaveType(BinStream& bs){
    bs << 2;
    bs << Type();
}

void Hmx::Object::SaveRest(BinStream& bs){
    mTypeProps.Save(bs, this);
    bs << 0;
}

void Hmx::Object::Copy(const Hmx::Object* obj, Hmx::Object::CopyType ty){
    if(ty != kCopyFromMax){
        if(ClassName() == obj->ClassName()){
            SetTypeDef((DataArray*)obj->TypeDef());
            mTypeProps.Copy(obj->mTypeProps, this);
        }
        else if(obj->TypeDef() || TypeDef()){
            MILO_WARN("Can't copy type \"%s\" or type props of %s to %s, different classes %s and %s", obj->Type(), Name(), obj->Name(), ClassName(), obj->ClassName());
        }
    }
}

void Hmx::Object::LoadType(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(29, 0)
    Symbol& s = (Symbol&)gNullStr;
    bs >> s;
    // ObjVersion: an ObjPtr and a word, the word being the packing of rev and altrev
}

void Hmx::Object::LoadRest(BinStream& bs) {

}

void Hmx::Object::Load(BinStream& bs) {
    LoadType(bs);
    LoadRest(bs);
}

const char* Hmx::Object::FindPathName(){
    bool b = false;
    if(mName && *mName) b = true;
    if(!b) return ClassName().Str();
    class ObjectDir* dataDir = DataDir();
    if(dataDir){
        return MakeString("%s (%s)", FileLocalize(dataDir->Name(), 0));
    }
    if(!dataDir->ProxyFile()->empty()){
        return MakeString("%s (%s)", FileLocalize(dataDir->ProxyFile()->c_str(), 0));
    }
    if(dataDir->mPathName){
        return MakeString("%s (%s)", FileLocalize(dataDir->mPathName, 0));
    }
    if(dataDir == this || dataDir->mName == 0 || *dataDir->mName == '\0'){
        return MakeString("%s/%s", dataDir->mName, ClassName());
    }
    if(mDir && mDir->mPathName && *mDir->mPathName != '\0'){
        return MakeString("%s (%s)", ClassName(), FileLocalize(mDir->mPathName, 0));
    }
}

void Hmx::Object::Replace(Hmx::Object* obj1, Hmx::Object* obj2){
    mTypeProps.Replace(obj1, obj2, this);
}

#pragma push
#pragma dont_inline on
#pragma pool_data off
// see scratch: https://decomp.me/scratch/9abtP
DataNode Hmx::Object::Handle(DataArray* _msg, bool _warn){
    Symbol sym = _msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? this : 0, sym);
    HANDLE_STATIC(get, OnGet);
    {
        static Symbol _s("get_array");
        if(sym == _s){
            return PropertyArray(_msg->Sym(2));
        }
    }
    HANDLE_EXPR_STATIC(size, PropertySize(_msg->Array(2)));
    HANDLE_STATIC(set, OnSet);
    HANDLE_ACTION_STATIC(insert, InsertProperty(_msg->Array(2), _msg->Evaluate(3)));
    HANDLE_ACTION_STATIC(remove, RemoveProperty(_msg->Array(2)));
    HANDLE_ACTION_STATIC(clear, PropertyClear(_msg->Array(2)));
    HANDLE_STATIC(append, OnPropertyAppend);
    HANDLE_EXPR_STATIC(has, Property(_msg->Array(2), false) != 0);
    {
        static Symbol _s("prop_handle");
        if(sym == _s){
            return HandleProperty(_msg, _msg->Array(2), true);
        }
    }
    HANDLE_ACTION_STATIC(copy, Copy(_msg->GetObj(2), (CopyType)_msg->Int(3)));
    HANDLE_ACTION_STATIC(replace, Replace(_msg->GetObj(2), _msg->GetObj(3)));
    HANDLE_EXPR_STATIC(class_name, ClassName());
    HANDLE_EXPR_STATIC(name, mName);
    HANDLE_STATIC(iterate_refs, OnIterateRefs);
    {
        static Symbol _s("dir");
        if(sym == _s){
            return DataNode(mDir);
        }
    }
    {
        static Symbol _s("set_name");
        if(sym == _s){
            ObjectDir* theDir = _msg->Size() > 3 ? _msg->Obj<ObjectDir>(3) : Dir();
            SetName(_msg->Str(2), theDir);
            return DataNode(0);
        }
    }
    HANDLE_ACTION_STATIC(set_type, SetType(_msg->Sym(2)));
    HANDLE_EXPR_STATIC(is_a, IsASubclass(ClassName(), _msg->Sym(2)));
    HANDLE_EXPR_STATIC(get_type, Type());
    HANDLE_EXPR_STATIC(get_heap, AllocHeapName());
    // if none of those symbols matched, we fall back here
    bool stank = false;
    if(mTypeDef != 0){
        DataArray* found = mTypeDef->FindArray(sym, false);
        if(found != 0) stank = true;
        if(stank){
            DataNode ran = found->ExecuteScript(1, this, _msg, 2);
            if(ran.Type() != kDataUnhandled) return DataNode(ran);
        }
        HANDLE_CHECK(0x2E6);
    }

    return DataNode(kDataUnhandled, 0);
}
#pragma pop

DataNode Hmx::Object::HandleType(DataArray* msg){
    Symbol t = msg->Sym(1);
    MessageTimer timer((MessageTimer::Active()) ? this : 0, t);
    bool found = false;
    DataArray* handler;
    if(mTypeDef != 0){
        handler = mTypeDef->FindArray(t, false);
        if(handler != 0) found = true;
    }
    if(found){
        return handler->ExecuteScript(1, this, (const DataArray*)msg, 2);
    }
    else return DataNode(kDataUnhandled, 0);
}

DataNode Hmx::Object::OnPropertyAppend(const DataArray* da){
    DataArray* arr = da->Array(2);
    int size = PropertySize(arr);
    DataArray* cloned = arr->Clone(true, false, 1);
    cloned->Node(cloned->Size() - 1) = DataNode(size);
    InsertProperty(cloned, da->Evaluate(3));
    cloned->Release();
    return DataNode(size);
}

BEGIN_PROPSYNCS(Hmx::Object);
END_PROPSYNCS;
