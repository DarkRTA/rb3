#ifndef HMX_OBJECT_HPP
#define HMX_OBJECT_HPP
#include "objref.hpp"
#include "data.hpp"
#include "binstream.hpp"
#include "types.h"
#include "symbol.hpp"

// forward declarations
class DataNode;
class DataArray;
class ObjectDir;
namespace Hmx { class Object; }

enum PropOp { i, d, k, l, m, a, o };

class TypeProps {
public:
    DataArray *data;

    TypeProps();
    ~TypeProps();

    void Save(BinStream &, Hmx::Object *);
    void Load(BinStream &, u16, Hmx::Object *);

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
    void Assign(const TypeProps&, ObjRef*);
};

namespace Hmx {
    /** An Object used in the game. Most of Rock Band 3's objects derive from this class. */
    class Object : public ObjRef {
    public:
        TypeProps props;
        DataArray* arr;
        const char *name;
        ObjectDir* dir;
        char unk14[8]; // this is an std::vector<const char*>, 8 bytes long (4 + 2 + 2)

        enum CopyType { f, a, r, t, s };

        Object(); // fn_8033560c
        virtual ~Object(); // fn_803356ec
        virtual Hmx::Object* RefOwner(){} // links to fn_8076F540, which returns void
        virtual void Replace(Hmx::Object*, Hmx::Object*); // fn_80336C88
        // ObjRef::IsDirPtr // links to fn_8077BAA0, which returns 0
        virtual Symbol ClassName() const; // fn_800103C8
        virtual void SetType(Symbol); // fn_800102A0
        virtual DataNode Handle(DataArray*, bool); // fn_80336C94
        virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp); // fn_80337B7C
        virtual void Save(BinStream&);
        virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
        virtual void Load(BinStream&);
        virtual void Print(){} // links to fn_8076F540, which returns void
        virtual void Export(){} // links to fn_8076F540, which returns void
        virtual void V_Unk14(){} // links to fn_8076F540, which returns void
        virtual void V_Unk15(){} // links to fn_8076F540, which returns void
        virtual void SetTypeDef(DataArray *);
        virtual void SetName(const char*, ObjectDir*); // fn_80335904
        virtual void DataDir(); // fn_803351D0
        virtual void PreLoad(BinStream&); // fn_800AB8B4
        virtual void PostLoad(BinStream&){} // links to fn_8076F540, which returns void
        virtual char* FindPathName(); // fn_80336A84

        static Symbol StaticClassName();
        Symbol Type() const;
        static Hmx::Object* NewObject();

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
        static Hmx::Object* NewObject(Symbol);

        DataNode OnGet(const DataArray*);
        DataNode OnSet(const DataArray*);
        DataNode OnIterateRefs(const DataArray*);
        ObjectDir* GetObjectDir();
        DataNode HandleType(DataArray*);
    };
}



#endif