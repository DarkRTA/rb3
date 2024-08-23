#ifndef OBJ_OBJECT_H
#define OBJ_OBJECT_H
#include "obj/Data.h"
#include "utl/BinStream.h"
#include "utl/Symbol.h"
#include "utl/TextStream.h"
#include "os/Debug.h"
#include "obj/ObjMacros.h"
#include <vector>
#include <map>

// forward declarations
class DataNode;
class DataArray;
class ObjectDir;
namespace Hmx {
    class Object;
}

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
    void Copy(const TypeProps&, Hmx::Object*);
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
        OBJ_CLASSNAME(Object);
        OBJ_SET_TYPE(Object);
        virtual DataNode Handle(DataArray*, bool);
        virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
        virtual ~Object();
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
        virtual void Replace(Hmx::Object*, Hmx::Object*);

        const char* Name() const { return mName; }

        template <class T> static T* New(){
            T* obj = dynamic_cast<T*>(Hmx::Object::NewObject(T::StaticClassName()));
        #ifdef VERSION_SZBE69_B8
            if(!obj) MILO_FAIL("Couldn't instantiate class %s", T::StaticClassName());
        #endif
            return obj;
        }

        const std::vector<ObjRef*>& Refs() const { return mRefs; }

        const DataArray* TypeDef() const { return mTypeDef; }
        Symbol Type() const {
            if(mTypeDef != 0) return mTypeDef->Sym(0);
            else return Symbol();
        }
        class ObjectDir* Dir() const { return mDir; }

        NEW_OBJ(Object)
        static void Init(){
            REGISTER_OBJ_FACTORY(Object)
        }

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

struct ObjPair {
    Hmx::Object* from;
    Hmx::Object* to;
};

struct ObjMatchPr {
    bool operator() (const Hmx::Object*& value) { return value == obj; }
    Hmx::Object* obj;
};

inline TextStream& operator<<(TextStream& ts, const Hmx::Object* obj){
    if(obj) ts << obj->Name();
    else ts << "<null>";
    return ts;
}

RETAIL_DONT_INLINE_FUNC unsigned short getHmxRev(int packed){
    return packed;
}

RETAIL_DONT_INLINE_FUNC unsigned short getAltRev(int packed){
    return (unsigned int)packed >> 0x10;
}

RETAIL_DONT_INLINE_FUNC int packRevs(unsigned short alt, unsigned short rev){
    return (rev & ~0xFFFF0000) | (alt << 0x10);
}

#endif
