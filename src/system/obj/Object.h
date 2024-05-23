#ifndef OBJ_OBJECT_H
#define OBJ_OBJECT_H
#include "obj/Data.h"
#include "utl/BinStream.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "utl/TextStream.h"
#include "os/System.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "obj/MessageTimer.h"
#include <vector>
#include <map>

// forward declarations
class DataNode;
class DataArray;
class ObjectDir;
namespace Hmx {
    class Object;
}

enum PropOp {
    kPropGet = 1,
    kPropSet = 2,
    kPropInsert = 4,
    kPropRemove = 8,
    kPropSize = 16,
    kPropHandle = 32,
};

#include "obj/PropSync_p.h"

/** A dictionary representing the different properties an Object can have. */
class TypeProps {
public:
    /** The DataArray structure representing the property dictionary.
        Rather than an std::map or a dictionary from a language like Python,
        the dictionary is laid out in one continuous DataArray, in the style of:
        (key1 value1 key2 value2 key3 value3).
        Each key is a DataNode of type Symbol, while each value is a DataNode of some other compatible node type (int/float/const char*). */
    DataArray* mMap;

    TypeProps() : mMap(0) {} // weak
    ~TypeProps(){
        MILO_ASSERT(!mMap, 0x3D);
    }

    void Save(BinStream &, Hmx::Object *);
    void Load(BinStream &, bool, Hmx::Object *);

    void ClearKeyValue(Symbol, Hmx::Object*);
    void ClearAll(Hmx::Object*);
    void ReleaseObjects(Hmx::Object*);
    void AddRefObjects(Hmx::Object*);
    void InsertArrayValue(Symbol, int, const DataNode&, DataArray*, Hmx::Object*);
    void SetArrayValue(Symbol, int, const DataNode&, DataArray*, Hmx::Object*);
    void RemoveArrayValue(Symbol, int, DataArray*, Hmx::Object*);
    DataNode* KeyValue(Symbol, bool) const;
    DataArray* GetArray(Symbol, DataArray*, Hmx::Object*);
    void SetKeyValue(Symbol, const DataNode&, bool, Hmx::Object*);
    void ReplaceObject(DataNode&, Hmx::Object*, Hmx::Object*, Hmx::Object*);
    void Replace(Hmx::Object*, Hmx::Object*, Hmx::Object*);
    int Size() const;
    TypeProps& Copy(const TypeProps&, Hmx::Object*);
    Symbol Key(int) const;
    DataNode& Value(int) const;
};

class ObjRef {
public:
    ObjRef(){}
    virtual ~ObjRef(){}
    virtual Hmx::Object* RefOwner() = 0;
    virtual void Replace(Hmx::Object*, Hmx::Object*) = 0;
    virtual bool IsDirPtr(){ return 0; }
};

#define OBJ_SET_TYPE(classname) \
    virtual void SetType(Symbol classname){ \
        static DataArray* types = SystemConfig("objects", StaticClassName(), "types"); \
        if(classname.Null()) SetTypeDef(0); \
        else { \
            DataArray* found = types->FindArray(classname, false); \
            if(found != 0) SetTypeDef(found); \
            else { \
                MILO_WARN("%s:%s couldn't find type %s", ClassName(), PathName(this), classname); \
                SetTypeDef(0); \
            } \
        } \
    }

#define OBJ_CLASSNAME(classname) \
    virtual Symbol ClassName() const { return StaticClassName(); } \
    static Symbol StaticClassName(){ \
        static Symbol name(#classname); \
        return name; \
    }

typedef Hmx::Object* ObjectFunc(void);

namespace Hmx {
    class Object : public ObjRef {
    public:
        TypeProps mTypeProps;
        DataArray* mTypeDef;
        const char* mName;
        class ObjectDir* mDir;
        std::vector<ObjRef*> mRefs;

        static std::map<Symbol, ObjectFunc*> sFactories;
        static Object* sDeleting;

        // o7 farts, you will be missed
        enum CopyType {
            kCopyDeep = 0,
            kCopyShallow = 1,
            kCopyFromMax = 2,
        };

        Object();
        Object(const Object&);
        virtual Hmx::Object* RefOwner(){ return this; }
        virtual void Replace(Hmx::Object*, Hmx::Object*);
        OBJ_CLASSNAME(Object);
        OBJ_SET_TYPE(Object);
        virtual DataNode Handle(DataArray*, bool);
        virtual ~Object();
        virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
        virtual void Save(BinStream&);
        virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
        virtual void Load(BinStream&);
        virtual void PreSave(BinStream&){}
        virtual void PostSave(BinStream&){}
        virtual void Print(){}
        virtual void Export(DataArray*, bool){}
        virtual void SetTypeDef(DataArray *);
        virtual void SetName(const char*, class ObjectDir*);
        virtual class ObjectDir* DataDir();
        virtual void PreLoad(BinStream&);
        virtual void PostLoad(BinStream&){}
        virtual const char* FindPathName();

        const char* Name() const { return mName; }

        template <class T> static T* New(){
            T* obj = dynamic_cast<T*>(Hmx::Object::NewObject(T::StaticClassName()));
            if(!obj) MILO_FAIL("Couldn't instantiate class %s", T::StaticClassName());
            return obj;
        }

        std::vector<ObjRef*>& Refs(){ return mRefs; }

        const DataArray* TypeDef() const { return mTypeDef; }
        Symbol Type() const {
            if(mTypeDef != 0) return mTypeDef->Sym(0);
            else return Symbol();
        }
        class ObjectDir* Dir() const { return mDir; }

        static Object* NewObject();

        static void RegisterFactory(Symbol, ObjectFunc*);
        static bool RegisteredFactory(Symbol);
        Object& operator=(const Object&);
        void RemoveFromDir();

        DataNode *Property(DataArray *, bool) const;
        DataNode* Property(Symbol, bool) const;
        void SetProperty(DataArray *, const DataNode &);
        void SetProperty(Symbol, const DataNode &);
        int PropertySize(DataArray *);
        DataNode OnPropertyAppend(const DataArray*);
        void InsertProperty(DataArray*, const DataNode&);
        void RemoveProperty(DataArray*);
        void PropertyClear(DataArray*);
        void AddRef(ObjRef*);
        void Release(ObjRef*);
        DataNode HandleProperty(DataArray*, DataArray*, bool);
        static Object* NewObject(Symbol);

        void SaveType(BinStream&);
        void SaveRest(BinStream&);
        void LoadType(BinStream&);
        void LoadRest(BinStream&);

        DataNode OnGet(const DataArray*);
        DataNode OnSet(const DataArray*);
        DataNode OnIterateRefs(const DataArray*);
        DataNode HandleType(DataArray*);
        DataNode PropertyArray(Symbol);
        const char* AllocHeapName();

        static unsigned short gRev;
        static unsigned short gAltRev;

    };
}

inline TextStream& operator<<(TextStream& ts, const Hmx::Object* obj){
    if(obj) ts << obj->Name();
    else ts << "<null>";
    return ts;
}

inline unsigned short getHmxRev(int ui){
    return ui;
}

inline unsigned short getAltRev(int ui){
    return (unsigned int)ui >> 0x10;
}

#define NEW_OVERLOAD \
    void* operator new(size_t t) {return _MemAlloc(t, 0);}

#define DELETE_OVERLOAD \
    void operator delete(void* v){ _MemFree(v); }

#define NEW_OBJ(objType) \
    static Hmx::Object* NewObject() { return new objType; }

// BEGIN HANDLE MACROS ---------------------------------------------------------------------------------

#define BEGIN_HANDLERS(objType) \
DataNode objType::Handle(DataArray* _msg, bool _warn){ \
    Symbol sym = _msg->Sym(1); \
    MessageTimer timer((MessageTimer::Active()) ? static_cast<Hmx::Object*>(this) : 0, sym);

#define HANDLE(symbol, func) \
    if(sym == symbol){ \
        DataNode result = func(_msg); \
        if(result.Type() != kDataUnhandled) return DataNode(result); \
    }

#define HANDLE_EXPR(symbol, expr) \
    if (sym == symbol) return DataNode(expr);

#define HANDLE_ACTION(symbol, expr) \
    if(sym == symbol){ \
        expr; \
        return DataNode(0); \
    }

#define HANDLE_MESSAGE(msg) \
    if(sym == msg::Type()){ \
        DataNode result = OnMsg(msg(_msg)); \
        if(result.Type() != kDataUnhandled) return DataNode(result); \
    }

#define NEW_STATIC_SYMBOL(str) \
    static Symbol _s(#str);

#define HANDLE_STATIC(sym, func) { \
    NEW_STATIC_SYMBOL(sym) \
    HANDLE(_s, func); \
}

#define HANDLE_EXPR_STATIC(symbol, expr) { \
    NEW_STATIC_SYMBOL(symbol) \
    HANDLE_EXPR(_s, expr) \
}

#define HANDLE_ACTION_STATIC(symbol, expr) { \
    NEW_STATIC_SYMBOL(symbol) \
    HANDLE_ACTION(_s, expr) \
}

#define HANDLE_SUPERCLASS(parent) \
    { \
        DataNode baseResult = parent::Handle(_msg, false); \
        if (baseResult.Type() != kDataUnhandled) return baseResult; \
    }

#define HANDLE_MEMBER(member) \
    { \
        DataNode baseResult = member.Handle(_msg, false); \
        if (baseResult.Type() != kDataUnhandled) return baseResult; \
    }

#define HANDLE_MEMBER_PTR(member) \
    { \
        if (member) {\
            DataNode baseResult = member->Handle(_msg, false); \
            if (baseResult.Type() != kDataUnhandled) return baseResult; \
        } \
    }

#define HANDLE_CHECK(line_num) \
    if(_warn) MILO_NOTIFIER_WARN("%s(%d): %s unhandled msg: %s", __FILE__, line_num, PathName(this), sym);

#define END_HANDLERS \
    return DataNode(kDataUnhandled, 0); \
}

// END HANDLE MACROS -----------------------------------------------------------------------------------

// BEGIN SYNCPROPERTY MACROS ---------------------------------------------------------------------------

#define BEGIN_PROPSYNCS(objType) \
bool objType::SyncProperty(DataNode& _val, DataArray* _prop, int _i, PropOp _op){ \
    if(_i == _prop->Size()) return true; \
    else { \
        Symbol sym = _prop->Sym(_i);

#define SYNC_PROP(symbol, member) \
        if(sym == symbol) return PropSync(member, _val, _prop, _i + 1, _op);

#define SYNC_PROP_METHOD(symbol, member, method) \
        if(sym == symbol){ \
            if(_op == kPropSet) method; \
            else { \
                if(_op == (PropOp)0x40) return false; \
                _val = DataNode(member); \
            } \
            return true; \
        }

#define SYNC_PROP_ACTION(symbol, member, opmask, action) \
        if(sym == symbol){ \
            bool synced = PropSync(member, _val, _prop, _i + 1, _op); \
            if(!synced) return false; \
            else { \
                if(!(_op & (opmask))){ \
                    action; \
                } \
                return true; \
            } \
        }

#define SYNC_PROP_STATIC(symbol, member) { \
    NEW_STATIC_SYMBOL(symbol) \
    SYNC_PROP(symbol, member) \
}

#define SYNC_SUPERCLASS(parent) \
        return parent::SyncProperty(_val, _prop, _i, _op);

#define END_PROPSYNCS \
        return false; \
    } \
}

// END SYNCPROPERTY MACROS -----------------------------------------------------------------------------

// BEGIN SAVE MACRO ------------------------------------------------------------------------------------

#define SAVE_OBJ(objType, line_num) \
void objType::Save(BinStream&){ \
    MILO_ASSERT(0, line_num); \
}

// END SAVE MACRO --------------------------------------------------------------------------------------

// BEGIN COPY MACROS -----------------------------------------------------------------------------------

#define BEGIN_COPYS(objType) \
void objType::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){

#define COPY_SUPERCLASS(parent) \
    parent::Copy(o, ty);

#define GET_COPY(objType) \
    const objType* c = dynamic_cast<const objType*>(o);

#define GET_COPY_AND_ASSERT(objType, line_num) \
    const objType* c = dynamic_cast<const objType*>(o); \
    MILO_ASSERT(c, line_num);

#define BEGIN_COPY_CHECKED \
    if(c){

#define COPY_MEMBER(mem) \
        mem = c->mem;

#define END_COPY_CHECKED \
    }

#define END_COPYS \
}

// END COPY MACROS -------------------------------------------------------------------------------------

// BEGIN LOAD MACROS -----------------------------------------------------------------------------------

#define DECLARE_REVS \
    static unsigned short gRev; \
    static unsigned short gAltRev;

#define INIT_REVS(objType) \
    unsigned short objType::gRev = 0; \
    unsigned short objType::gAltRev = 0;

#define BEGIN_LOADS(objType) \
void objType::Load(BinStream& bs){

#define LOAD_REVS(bs) \
    int rev; \
    bs >> rev; \
    gRev = getHmxRev(rev); \
    gAltRev = getAltRev(rev);

#define ASSERT_REV(ver) \
    if ((ver == 0) ? (gRev != ver) : (gRev > ver)){ \
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), gRev, (unsigned short)ver); \
    }

#define ASSERT_ALTREV(ver) \
    if ((ver == 0) ? (gAltRev != ver) : (gAltRev > ver)){ \
        MILO_FAIL("%s can't load new %s alt version %d > %d", PathName(this), ClassName(), gAltRev, (unsigned short)ver); \
    }

#define ASSERT_REVS(rev1, rev2) \
    ASSERT_REV(rev1) \
    ASSERT_ALTREV(rev2)

// for loading in a version number that isn't a class's gRev/gAltRev
#define ASSERT_GLOBAL_REV(ver, rev_name) \
    if (ver > rev_name){ \
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), rev_name, ver); \
    }

#define LOAD_SUPERCLASS(parent) \
    parent::Load(bs);

#define END_LOADS \
}

// END LOAD MACROS -------------------------------------------------------------------------------------

// BEGIN ADDTONOTIFIES MACRO ---------------------------------------------------------------------------

#define ADD_NOTIFS \
namespace {\
    bool AddToNotifies(const char* str, std::list<class String>& list){\
        if(list.size() > 0x10) return false;\
        for(std::list<class String>::iterator it = list.begin(); it != list.end(); it++){\
            bool strFound = !strcmp(it->c_str(), str);\
            if(strFound) return false;\
        }\
        list.push_back(str);\
        return true;\
    }\
}

// END ADDTONOTIFIES MACRO -----------------------------------------------------------------------------

#endif
