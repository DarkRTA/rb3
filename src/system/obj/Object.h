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
    ~TypeProps(); // although weak, it actually does stuff

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
    DataNode* Key(int) const;
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
        if(classname.IsNull()) SetTypeDef(0); \
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

namespace Hmx {
    class Object : public ObjRef {
    public:
        TypeProps mTypeProps;
        DataArray* mTypeDef;
        const char* mName;
        class ObjectDir* mDir;
        char mRefs[8]; // actually a vector<ObjRef*> - thank you stlport, very cool

        // o7 farts, you will be missed
        enum CopyType {
            kCopyDeep = 0,
            kCopyShallow = 1,
            kCopyFromMax = 2,
        };

        Object();
        Object(const Object&);
        virtual ~Object();
        virtual Hmx::Object* RefOwner(){}
        virtual void Replace(Hmx::Object*, Hmx::Object*);
        OBJ_CLASSNAME(Object);
        OBJ_SET_TYPE(Object);
        virtual DataNode Handle(DataArray*, bool);
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
        virtual char* FindPathName();

        const char* Name() const { return mName; }
        // T* New<T>();
        // vector& Refs();

        Symbol Type() const {
            if(mTypeDef != 0) return mTypeDef->Sym(0);
            else return gNullStr;
        }
        class ObjectDir* Dir() const { return mDir; }

        static Object* NewObject();

        DataNode *Property(DataArray *, bool) const;
        DataNode* Property(Symbol, bool);
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

        DataNode OnGet(const DataArray*);
        DataNode OnSet(const DataArray*);
        DataNode OnIterateRefs(const DataArray*);
        DataNode HandleType(DataArray*);
        DataNode PropertyArray(Symbol);
        char* GetHeap();

    };
}

#define BEGIN_HANDLERS(objType) \
DataNode objType::Handle(DataArray* _msg, bool _warn){ \
    Symbol sym = _msg->Sym(1); \
    MessageTimer timer((MessageTimer::Active()) ? this : 0, sym);

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

#define HANDLE_SUPERCLASS(parent) \
    { \
        DataNode baseResult = parent::Handle(_msg, false); \
        if (baseResult.Type() != kDataUnhandled) return baseResult; \
    }

#define HANDLE_CHECK(line_num) \
    if(_warn) MILO_WARN("%s(%d): %s unhandled msg: %s", __FILE__, line_num, PathName(this), sym);

#define END_HANDLERS \
    return DataNode(kDataUnhandled, 0); \
}

#endif
