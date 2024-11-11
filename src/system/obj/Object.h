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

/** A reference to an Object type. */
class ObjRef {
public:
    ObjRef(){}
    virtual ~ObjRef(){}

    /** Get the owner of this Hmx::Object reference. */
    virtual Hmx::Object* RefOwner() = 0;

    /** Removes the properties from the first Hmx::Object, and moves them to the second.
     * @param [in] from The Hmx::Object from which to remove properties.
     * @param [in] to The Hmx::Object to which to add the removed properties.
    */
    virtual void Replace(Hmx::Object* from, Hmx::Object* to) = 0;

    /** Returns whether or not this object is an ObjDirPtr. */
    virtual bool IsDirPtr(){ return false; }
};

typedef Hmx::Object* ObjectFunc(void);

namespace Hmx {

    /** @brief: The base class from which all major Objects used in-game build upon.
    * Original _objects description:
    * "The Object class is the root of the class hierarchy. Every
        class has Object as a superclass." */
    class Object : public ObjRef {
    public:
        /** An array of properties this Objects can have. */
        TypeProps mTypeProps; // 0x4
        DataArray* mTypeDef; // 0x8
        /** This Object's name. */
        const char* mName; // 0xc
        /** The ObjectDir in which this Object resides. */
        class ObjectDir* mDir; // 0x10
        /** A collection of object instances which reference this Object. */
        std::vector<ObjRef*> mRefs; // 0x14

        /** A collection of Object class names and their corresponding instantiators. */
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

        /** This Object's class name. */
        OBJ_CLASSNAME(Object);
        OBJ_SET_TYPE(Object);

        /** Execute code based on the contents of a received message.
        * @param [out] out The return value of whatever code was executed.
        * @param [in] _msg The received message.
        * @param [in] _warn Whether or not to print the unhandled message to the debug console.
        */
        virtual DataNode Handle(DataArray* _msg, bool _warn);

        /** Syncs an Object's property to or from a supplied DataNode.
        * @param [out] out Returns true if a property was synced, or if the desired index == the prop array size.
        * @param [in] _val A DataNode to either place the property val into, or set the property val with.
        * @param [in] _prop The DataArray containing the symbol representing the property to sync.
        * @param [in] _i The index in _prop containing the symbol of the property to sync.
        * @param [in] _op The operation to be performed with the property.
        */
        virtual bool SyncProperty(DataNode& _val, DataArray* _prop, int _i, PropOp _op);
        virtual ~Object();

        /** Saves this Object into a BinStream. */
        virtual void Save(BinStream&);

        /** Copy the contents of another Object into this Object based on the CopyType.
        * @param [in] o The other Object to copy from.
        * @param [in] ty The copy type.
        */
        virtual void Copy(const Hmx::Object* o, Hmx::Object::CopyType ty);
        
        /** Loads this Object from a BinStream. */
        virtual void Load(BinStream&);

        /** Any routines to write relevant data to a BinStream before the main Save method executes. */
        virtual void PreSave(BinStream&){}
        /** Any routines to write relevant data to a BinStream after the main Save method executes. */
        virtual void PostSave(BinStream&){}
        /** Prints relevant info about this Object to the debug console. */
        virtual void Print(){}
        virtual void Export(DataArray*, bool){}
        virtual void SetTypeDef(DataArray*);
        virtual void SetName(const char*, class ObjectDir*);
        virtual class ObjectDir* DataDir();
        /** Any routines to read relevant data from a BinStream before the main Load method executes. */
        virtual void PreLoad(BinStream&);
        /** Any routines to read relevant data from a BinStream after the main Load method executes. */
        virtual void PostLoad(BinStream&){}
        /** Get this Object's path name. */
        virtual const char* FindPathName();
        virtual void Replace(Hmx::Object*, Hmx::Object*);

        const char* Name() const { return mName; }

        /** Create a new Object derivative based on its entry in the factory list. */
        template <class T> static T* New(){
            T* obj = dynamic_cast<T*>(Hmx::Object::NewObject(T::StaticClassName()));
        #ifdef MILO_DEBUG
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

        /** Add a new Object derivative to the factory list. */
        static void RegisterFactory(Symbol, ObjectFunc*);
        /** Check if an Object derivative has an entry in the factory list. */
        static bool RegisteredFactory(Symbol);
        Object& operator=(const Object&);
        void RemoveFromDir();

        DataNode* Property(DataArray*, bool) const;
        DataNode* Property(Symbol, bool) const;
        void SetProperty(DataArray*, const DataNode &);
        void SetProperty(Symbol, const DataNode &);
        int PropertySize(DataArray*);
        DataNode OnPropertyAppend(const DataArray*);
        void InsertProperty(DataArray*, const DataNode&);
        void RemoveProperty(DataArray*);
        void PropertyClear(DataArray*);

        /** Add this Object reference into mRefs.
        * @param [in] ref The reference to add.
        */
        void AddRef(ObjRef* ref);

        /** Remove this Object reference from mRefs.
        * @param [in] ref The reference to remove.
        */
        void Release(ObjRef* ref);
        
        DataNode HandleProperty(DataArray*, DataArray*, bool);
        static Object* NewObject(Symbol);

        /** Write's this Object's rev values and its Type Symbol to the BinStream. */
        void SaveType(BinStream&);
        /** Write's this Object's TypeProps to the BinStream. */
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

inline unsigned short getHmxRev(int packed){
    return packed;
}

inline unsigned short getAltRev(int packed){
    return (unsigned int)packed >> 0x10;
}

inline int packRevs(unsigned short alt, unsigned short rev){
    return (rev & ~0xFFFF0000) | (alt << 0x10);
}

#define NULL_OBJ (Hmx::Object*)nullptr

#endif
