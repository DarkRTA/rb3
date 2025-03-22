#include "obj/Object.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Utl.h"
#include "obj/MessageTimer.h"
#include "utl/MemMgr.h"
#include "os/OSFuncs.h"
#include "obj/DataUtl.h"
#include "obj/ObjVersion.h"

#include "decomp.h"

DECOMP_FORCEACTIVE(Object, "", "unknown")

INIT_REVS(Hmx::Object)

std::map<Symbol, ObjectFunc *> Hmx::Object::sFactories;
Hmx::Object *Hmx::Object::sDeleting = 0;
bool gLoadingProxyFromDisk = 0;
std::vector<ObjVersion> sRevStack;

ObjectDir *Hmx::Object::DataDir() {
    if (mDir != 0)
        return mDir;
    else
        return ObjectDir::Main();
}

Hmx::Object *Hmx::Object::NewObject(Symbol s) {
    std::map<Symbol, ObjectFunc *>::iterator it = sFactories.find(s);
    if (it != sFactories.end())
        return (it->second)();
    else {
        MILO_FAIL("Unknown class %s", s);
        return NULL;
    }
}

void Hmx::Object::RegisterFactory(Symbol s, ObjectFunc *func) { sFactories[s] = func; }

bool Hmx::Object::RegisteredFactory(Symbol s) {
    const std::map<Symbol, ObjectFunc *>::iterator it = sFactories.find(s);
    return it != sFactories.end();
}

Hmx::Object::Object() : mTypeDef(0), mName(gNullStr), mDir(0) {}

Hmx::Object &Hmx::Object::operator=(const Hmx::Object &obj) {
    mName = obj.mName;
    mTypeDef = obj.mTypeDef;
    mTypeProps.Copy(obj.mTypeProps, this);
    mDir = obj.mDir;
    mRefs = obj.mRefs;
    return *this;
}

Hmx::Object::~Object() {
    mTypeProps.ClearAll(this);
    MILO_ASSERT(MainThread(), 0xA7);
    if (mTypeDef) {
        mTypeDef->Release();
        mTypeDef = 0;
    }
    RemoveFromDir();
    Hmx::Object *tmp = sDeleting;
    sDeleting = this;
    std::vector<ObjRef *>::reverse_iterator rit = mRefs.rbegin();
    std::vector<ObjRef *>::reverse_iterator ritEnd = mRefs.rend();
    for (; rit != ritEnd; rit++) {
        (*rit)->Replace(this, 0);
    }
    sDeleting = tmp;
    if (gDataThis == this)
        gDataThis = 0;
}

void Hmx::Object::SetName(const char *name, class ObjectDir *dir) {
    RemoveFromDir();
    if (name == 0 || *name == '\0') {
        mName = gNullStr;
        mDir = 0;
    } else {
        MILO_ASSERT(dir, 0xE0);
        mDir = dir;
        ObjectDir::Entry *entry = dir->FindEntry(name, true);
        if (entry->obj)
            MILO_FAIL("%s already exists", name);
        entry->obj = this;
        mName = entry->name;
        dir->AddedObject(this);
    }
}

void Hmx::Object::RemoveFromDir() {
    if (mDir && mDir != sDeleting) {
        mDir->RemovingObject(this);
        ObjectDir::Entry *entry = mDir->FindEntry(mName, false);
        bool entryExists = false;
        if (entry && entry->obj == this)
            entryExists = true;
        if (!entryExists) {
            MILO_FAIL("No entry for %s in %s", PathName(this), PathName(mDir));
        }
        entry->obj = 0;
    }
}

void Hmx::Object::SetTypeDef(DataArray *da) {
    if (mTypeDef != da) {
        if (mTypeDef != 0) {
            mTypeDef->Release();
            mTypeDef = 0;
        }
        mTypeProps.ClearAll(this);
        mTypeDef = da;
        if (da != 0)
            da->AddRef();
    }
}

const DataNode *Hmx::Object::Property(DataArray *prop, bool fail) const {
    static DataNode n(0);
    // if prop was synced, return the prop node n
    if (const_cast<Hmx::Object *>(this)->SyncProperty(n, prop, 0, kPropGet))
        return &n;
    Symbol propKey = prop->Sym(0);
    // retrieve property val from typeprops array
    const DataNode *propValue = mTypeProps.KeyValue(propKey, false);
    // if it wasn't found, search typedef array
    if (!propValue) {
        if (mTypeDef) {
            DataArray *found = mTypeDef->FindArray(propKey, fail);
            if (found)
                propValue = &found->Evaluate(1);
        }
    }
    if (propValue) {
        int cnt = prop->Size();
        if (cnt == 1)
            return propValue;
        else if (cnt == 2) {
            if (propValue->Type() == kDataArray) {
                DataArray *ret = propValue->mValue.array;
                return &ret->Node(prop->Int(1));
            }
        }
    }
    if (fail) {
        String str;
        str << prop;
        MILO_FAIL("%s: property %s not found", PathName(this), str);
    }
    return nullptr;
}

const DataNode *Hmx::Object::Property(Symbol prop, bool fail) const {
    static DataArrayPtr d(1);
    d.Node(0) = prop;
    return Property(d, fail);
}

#pragma push
#pragma pool_data off
DataNode Hmx::Object::PropertyArray(Symbol sym) {
    static DataArrayPtr d(1);
    d.Node(0) = sym;
    int size = PropertySize(d.mData);
    DataArray *newArr = new DataArray(size);
    static DataArrayPtr path(new DataArray(2));
    path.Node(0) = sym;
    for (int i = 0; i < size; i++) {
        path.Node(1) = i;
        newArr->Node(i) = *Property(path.mData, true);
    }
    DataNode ret = DataNode(newArr, kDataArray);
    newArr->Release();
    return ret;
}
#pragma pop

DataNode Hmx::Object::HandleProperty(DataArray *prop, DataArray *a2, bool fail) {
    static DataNode n(a2, kDataArray);
    if (SyncProperty(n, prop, 0, kPropHandle)) {
        return n;
    }
    if (fail) {
        MILO_FAIL(
            "%s: property %s not found",
            PathName(this),
            (prop != 0) ? prop->Sym(0) : "<none>"
        );
    }
    return 0;
}

void Hmx::Object::SetProperty(DataArray *prop, const DataNode &val) {
    if (!SyncProperty((DataNode &)val, prop, 0, kPropSet)) {
        Symbol name = prop->Sym(0);
        if (prop->Size() == 1) {
            mTypeProps.SetKeyValue(name, val, true, this);
        } else {
            MILO_ASSERT(prop->Size() == 2, 0x17D);
            mTypeProps.SetArrayValue(name, prop->Int(1), val, mTypeDef, this);
        }
    }
}

void Hmx::Object::SetProperty(Symbol prop, const DataNode &val) {
    static DataArrayPtr d(1);
    d.Node(0) = prop;
    SetProperty(d, val);
}

int Hmx::Object::PropertySize(DataArray *prop) {
    static DataNode n;
    if (SyncProperty(n, prop, 0, kPropSize)) {
        return n.Int();
    } else {
        MILO_ASSERT(prop->Size() == 1, 0x192);
        Symbol name = prop->Sym(0);
        const DataNode *a = mTypeProps.KeyValue(name, false);
        if (a == nullptr) {
            if (mTypeDef != nullptr) {
                a = &mTypeDef->FindArray(name)->Evaluate(1);
            } else
                MILO_FAIL("%s: property %s not found", PathName(this), name);
        }
        MILO_ASSERT(a->Type() == kDataArray, 0x1A1);
        return a->mValue.array->Size();
    }
}

void Hmx::Object::PropertyClear(DataArray *propArr) {
    int size = PropertySize(propArr);
    DataArray *cloned = propArr->Clone(true, false, 1);
    while (size-- != 0) {
        cloned->Node(cloned->Size() - 1) = size;
        RemoveProperty(cloned);
    }
    cloned->Release();
}

void Hmx::Object::RemoveProperty(DataArray *prop) {
    static DataNode n;
    if (!SyncProperty(n, prop, 0, kPropRemove)) {
        MILO_ASSERT(prop->Size() == 2, 0x1BB);
        mTypeProps.RemoveArrayValue(prop->Sym(0), prop->Int(1), mTypeDef, this);
    }
}

void Hmx::Object::InsertProperty(DataArray *prop, const DataNode &val) {
    if (!SyncProperty((DataNode &)val, prop, 0, kPropInsert)) {
        MILO_ASSERT(prop->Size() == 2, 0x1C5);
        mTypeProps.InsertArrayValue(prop->Sym(0), prop->Int(1), val, mTypeDef, this);
    }
}

void Hmx::Object::AddRef(ObjRef *ref) {
    if (ref->RefOwner() != this)
        mRefs.push_back(ref);
}

void Hmx::Object::Release(ObjRef *o) {
    if (sDeleting != this && o->RefOwner() != this) {
        for (std::vector<ObjRef *>::reverse_iterator i = mRefs.rbegin();
             i != mRefs.rend();
             i++) {
            if (*(i.base()) == o) {
                MILO_ASSERT(*(i.base()) == o, 0x1E6);
                mRefs.erase(i.base());
                return;
            }
        }
    }
}

void Hmx::Object::Save(BinStream &bs) {
    SaveType(bs);
    SaveRest(bs);
}

void Hmx::Object::SaveType(BinStream &bs) {
    bs << packRevs(0, 2);
    bs << Type();
}

void Hmx::Object::SaveRest(BinStream &bs) {
    mTypeProps.Save(bs, this);
    bs << 0;
}

void Hmx::Object::Copy(const Hmx::Object *obj, Hmx::Object::CopyType ty) {
    if (ty == kCopyFromMax)
        return;
    if (ClassName() == obj->ClassName()) {
        SetTypeDef((DataArray *)obj->TypeDef());
        mTypeProps.Copy(obj->mTypeProps, this);
    } else if (obj->TypeDef() || TypeDef()) {
        const Symbol className = obj->ClassName();
        const Symbol selfclass = ClassName();
        const char *objname = obj->Name();
        const char *selfname = Name();
        const Symbol typ = obj->Type();

        MILO_WARN(
            "Can't copy type \"%s\" or type props of %s to %s, different classes %s and %s",
            typ,
            selfname,
            objname,
            selfclass,
            className
        );
    }
}

void Hmx::Object::LoadType(BinStream &bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(2, 0)
    Symbol s;
    bs >> s;
    SetType(s);
    PushRev(packRevs(gAltRev, gRev), this);
}

void Hmx::Object::LoadRest(BinStream &bs) {
    int revs = PopRev(this);
    gAltRev = getAltRev(revs);
    gRev = getHmxRev(revs);
    mTypeProps.Load(bs, gRev < 2, this);
    if (gRev != 0) {
        int i;
        bs >> i;
        if (i != 0) {
            void *v = _MemAllocTemp(i + 1, 1);
            bs.Read(v, i);
            _MemFree(v);
        }
    }
}

void Hmx::Object::Load(BinStream &bs) {
    LoadType(bs);
    LoadRest(bs);
}

const char *Hmx::Object::FindPathName() {
    const char *name = (mName && *mName) ? mName : ClassName().Str();

    class ObjectDir *dataDir = DataDir();
    if (dataDir) {
        if (dataDir->mLoader) {
            return MakeString(
                "%s (%s)", name, FileLocalize(dataDir->mLoader->mFile.c_str(), 0)
            );
        } else if (!dataDir->ProxyFile().empty()) {
            return MakeString(
                "%s (%s)", name, FileLocalize(dataDir->ProxyFile().c_str(), 0)
            );
        } else if (*dataDir->mPathName != '\0') {
            return MakeString("%s (%s)", name, FileLocalize(dataDir->mPathName, 0));
        } else if (dataDir != this && dataDir->mName && *dataDir->mName) {
            return MakeString("%s/%s", dataDir->mName, name);
        } else if (mDir && *mDir->mPathName) {
            return MakeString("%s (%s)", name, FileLocalize(mDir->mPathName, 0));
        }
    }
    return name;
}

const char *Hmx::Object::AllocHeapName() { return MemHeapName(MemFindAddrHeap(this)); }

void Hmx::Object::Replace(Hmx::Object *obj1, Hmx::Object *obj2) {
    mTypeProps.Replace(obj1, obj2, this);
}

#pragma push
#pragma dont_inline on
#pragma pool_data off
BEGIN_HANDLERS(Hmx::Object)
    HANDLE_STATIC(get, OnGet);
    HANDLE_EXPR_STATIC(get_array, PropertyArray(_msg->Sym(2)));
    HANDLE_EXPR_STATIC(size, PropertySize(_msg->Array(2)));
    HANDLE_STATIC(set, OnSet);
    HANDLE_ACTION_STATIC(insert, InsertProperty(_msg->Array(2), _msg->Evaluate(3)));
    HANDLE_ACTION_STATIC(remove, RemoveProperty(_msg->Array(2)));
    HANDLE_ACTION_STATIC(clear, PropertyClear(_msg->Array(2)));
    HANDLE_STATIC(append, OnPropertyAppend);
    HANDLE_EXPR_STATIC(has, Property(_msg->Array(2), false) != 0);
    HANDLE_EXPR_STATIC(prop_handle, HandleProperty(_msg->Array(2), _msg, true));
    HANDLE_ACTION_STATIC(copy, Copy(_msg->Obj<Hmx::Object>(2), (CopyType)_msg->Int(3)));
    HANDLE_ACTION_STATIC(
        replace, Replace(_msg->Obj<Hmx::Object>(2), _msg->Obj<Hmx::Object>(3))
    );
    HANDLE_EXPR_STATIC(class_name, ClassName());
    HANDLE_EXPR_STATIC(name, mName);
    HANDLE_STATIC(iterate_refs, OnIterateRefs);
    HANDLE_EXPR_STATIC(dir, mDir);
    HANDLE_ACTION_STATIC(
        set_name,
        SetName(_msg->Str(2), _msg->Size() > 3 ? _msg->Obj<ObjectDir>(3) : Dir())
    )
    HANDLE_ACTION_STATIC(set_type, SetType(_msg->Sym(2)));
    HANDLE_EXPR_STATIC(is_a, IsASubclass(ClassName(), _msg->Sym(2)));
    HANDLE_EXPR_STATIC(get_type, Type());
    HANDLE_EXPR_STATIC(get_heap, AllocHeapName());
    HANDLE_ARRAY(mTypeDef)
    HANDLE_CHECK(0x2E6);
END_HANDLERS
#pragma pop

DataNode Hmx::Object::HandleType(DataArray *msg) {
    Symbol t = msg->Sym(1);
    bool found = false;
    DataArray *handler;
    if (mTypeDef != 0) {
        handler = mTypeDef->FindArray(t, false);
        if (handler != 0)
            found = true;
    }
    if (found) {
        MessageTimer timer(this, t);
        return handler->ExecuteScript(1, this, (const DataArray *)msg, 2);
    } else
        return DataNode(kDataUnhandled, 0);
}

DataNode Hmx::Object::OnIterateRefs(const DataArray *da) {
    DataNode *var = da->Var(2);
    DataNode node(*var);
    for (std::vector<ObjRef *>::reverse_iterator it = mRefs.rbegin(); it != mRefs.rend();
         ++it) {
        *var = (*it)->RefOwner();
        for (int i = 3; i < da->Size(); i++) {
            da->Command(i)->Execute();
        }
    }
    *var = node;
    return 0;
}

DataNode Hmx::Object::OnSet(const DataArray *da) {
    if (da->Size() % 2) {
        MILO_FAIL(
            "Uneven number of properties (file %s, line %d)", da->File(), da->Line()
        );
    }
    for (int i = 2; i < da->Size(); i += 2) {
        const DataNode &node = da->Evaluate(i);
        if (node.Type() == kDataSymbol) {
            SetProperty(STR_TO_SYM(node.mValue.symbol), da->Evaluate(i + 1));
        } else {
            if (node.Type() != kDataArray) {
                String str;
                node.Print(str, true);
                MILO_FAIL(
                    "Data %s is not array or symbol (file %s, line %d)",
                    str.c_str(),
                    da->File(),
                    da->Line()
                );
            }
            SetProperty(node.mValue.array, da->Evaluate(i + 1));
        }
    }
    return 0;
}

DECOMP_FORCEACTIVE(Object, "%s")

DataNode Hmx::Object::OnPropertyAppend(const DataArray *da) {
    DataArray *arr = da->Array(2);
    int size = PropertySize(arr);
    DataArray *cloned = arr->Clone(true, false, 1);
    cloned->Node(cloned->Size() - 1) = size;
    InsertProperty(cloned, da->Evaluate(3));
    cloned->Release();
    return size;
}

DataNode Hmx::Object::OnGet(const DataArray *da) {
    const DataNode &node = da->Evaluate(2);
    if (node.Type() == kDataSymbol) {
        const DataNode *prop = Property(STR_TO_SYM(node.mValue.symbol), da->Size() < 4);
        if (prop)
            return *prop;
    } else {
        if (node.Type() != kDataArray) {
            String str;
            node.Print(str, true);
            MILO_FAIL(
                "Data %s is not array or symbol (file %s, line %d)",
                str.c_str(),
                da->File(),
                da->Line()
            );
        }
        bool size = da->Size() < 4;
        const DataNode *prop = Property(node.mValue.array, size);
        if (prop)
            return *prop;
    }
    return da->Node(3);
}

BEGIN_PROPSYNCS(Hmx::Object)
END_PROPSYNCS
