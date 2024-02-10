#ifndef OBJ_OBJECT_H
#define OBJ_OBJECT_H
#include "Data.h"
#include "Symbol.h"
#include "Str.h"
#include "TextStream.h"
#include "BinStream.h"

// forward declarations
class ObjRef;
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
    DataArray* mDataDict;

    TypeProps(); // weak
    ~TypeProps(); // weak

    void Save(BinStream &, Hmx::Object *);
    void Load(BinStream &, unsigned short, Hmx::Object *);

    void ClearAll(ObjRef*);
    void ReleaseObjects(ObjRef*);
    void AddRefObjects(ObjRef*);
    void InsertArrayValue(Symbol, int, const DataNode&, DataArray*, ObjRef*);
    void SetArrayValue(Symbol, int, const DataNode&, DataArray*, ObjRef*);
    void RemoveArrayValue(Symbol, int, DataArray*, ObjRef*);
    DataNode* KeyValue(Symbol, bool);
    DataArray* GetArray(Symbol, DataArray*, ObjRef*);
    void SetKeyValue(Symbol, const DataNode&, bool, ObjRef*);
    void ReplaceObject(DataNode&, Hmx::Object*, Hmx::Object*, ObjRef*);
    void Replace(Hmx::Object*, Hmx::Object*, ObjRef*);
    int Size() const;
    TypeProps& Assign(const TypeProps&, ObjRef*);
};

class ObjRef {
public:
    ObjRef();
    virtual ~ObjRef();
    virtual Hmx::Object* RefOwner() = 0;
    virtual void Replace(Hmx::Object*, Hmx::Object*) = 0;
    virtual bool IsDirPtr(){ return 0; }
};

namespace Hmx {
    class Object : public ObjRef {
    public:
        TypeProps mTypeProps; // RB2 has this protected

        // RB2 has the following members private
        DataArray* mTypeDef;
        char* mNote;
        const char* mName;
        ObjectDir* mDir;
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
        virtual Symbol ClassName() const;
        virtual void SetType(Symbol);
        virtual DataNode Handle(DataArray*, bool);
        virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
        virtual void Save(BinStream&);
        virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
        virtual void Load(BinStream&);
        virtual void Print(){}
        virtual void Export(DataArray*, bool){}
        virtual void V_Unk14(){}
        virtual void V_Unk15(){}
        virtual void SetTypeDef(DataArray *);
        virtual void SetName(const char*, ObjectDir*);
        virtual ObjectDir* DataDir();
        virtual void PreLoad(BinStream&);
        virtual void PostLoad(BinStream&){}
        virtual char* FindPathName();

        const char* Name();
        // T* New<T>();
        // vector& Refs();

        static Symbol StaticClassName();
        Symbol Type() const;
        static Object* NewObject();

        DataNode *Property(DataArray *, bool);
        DataNode* Property(Symbol, bool);
        void SetProperty(DataArray *, const DataNode &);
        void SetProperty(Symbol, const DataNode &);
        int PropertySize(DataArray *);
        const char *Name() const;
        DataNode OnAppendToArray(const DataArray*);
        void InsertProperty(DataArray*, const DataNode&);
        void RemoveProperty(DataArray*);
        void ClearProperties(DataArray*);
        void AddRef(ObjRef*);
        void Release(ObjRef*);
        DataNode HandleProperty(DataArray*, DataArray*, bool);
        static Object* NewObject(Symbol);

        DataNode OnGet(const DataArray*);
        DataNode OnSet(const DataArray*);
        DataNode OnIterateRefs(const DataArray*);
        ObjectDir* GetObjectDir();
        DataNode HandleType(DataArray*);

        DataNode OnGetArray(const DataArray*, Symbol);
        char* GetHeap();

    };
}

#endif
