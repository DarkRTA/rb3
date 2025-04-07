#pragma once
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
private:
    /** The DataArray structure representing the property dictionary.
     * Rather than an std::map or a dictionary from a language like Python,
     * the dictionary is laid out in one continuous DataArray, in the style of:
     * (key1 value1 key2 value2 key3 value3).
     * Each key is a DataNode of type Symbol,
     * while each value is a DataNode of some other compatible node type (int/float/const
     * char*). */
    DataArray *mMap; // 0x0

    /** If the DataNode n contains from, replaces it with to.
     * @param [in] n The DataNode containing a Hmx::Object.
     * @param [in] from The Object to be replaced.
     * @param [in] to The Object serving as the replacement.
     * @param [in] ref The Object to update refs for.
     */
    void ReplaceObject(
        DataNode &n, Hmx::Object *from, Hmx::Object *to, Hmx::Object *ref
    ); // likely a private method

    /** Releases all Object values currently in the dictionary.
     * @param [in] ref The Object to release from.
     */
    void ReleaseObjects(Hmx::Object *ref);

    /** Adds references to all Object values currently in the dictionary.
     * @param [in] ref The Object to add refs to.
     */
    void AddRefObjects(Hmx::Object *ref);

public:
    TypeProps() : mMap(0) {}
    ~TypeProps() { MILO_ASSERT(!mMap, 0x3D); }

    /** Saves the dictionary to a BinStream, using ref's TypeDef to determine which props
     * to write.
     * @param [in] bs The BinStream to write to.
     * @param [in] ref The Object to reference from.
     */
    void Save(BinStream &bs, Hmx::Object *ref);

    /** Loads the dictionary from a BinStream.
     * @param [in] bs The BinStream to read from
     * @param [in] old_proxy TODO: currently unknown
     * @param [in] ref The Object to add any Object refs to.
     */
    void Load(BinStream &bs, bool old_proxy, Hmx::Object *ref);

    /** Search for a key in the dictionary, and remove its key/value pair.
     * @param [in] key The key to search for.
     * @param [in] ref The Object to release from, if the value is an Object.
     */
    void ClearKeyValue(Symbol key, Hmx::Object *ref);

    /** Completely clear the dictionary.
     * @param [in] ref The Object that any objects will release from.
     */
    void ClearAll(Hmx::Object *ref);

    /** Search for a key in the dictionary, and insert arrVal into the resulting DataArray
     * value at index idx.
     * @param [in] key The key to search for.
     * @param [in] idx The index of the resulting DataArray value in which to insert
     * arrVal.
     * @param [in] arrVal The value to insert into the key's resulting DataArray value.
     * @param [in] tdef The type def DataArray to search in, if the key isn't in the
     * dictionary.
     * @param [in] ref The Object to update refs for.
     */
    void InsertArrayValue(
        Symbol key, int idx, const DataNode &arrVal, DataArray *tdef, Hmx::Object *ref
    );

    /** Search for a key in the dictionary, and assign arrVal to the resulting DataArray
     * value at index idx.
     * @param [in] key The key to search for.
     * @param [in] idx The index of the resulting DataArray value in which to insert
     * arrVal.
     * @param [in] arrVal The value to insert into the key's resulting DataArray value.
     * @param [in] tdef The type def DataArray to search in, if the key isn't in the
     * dictionary.
     * @param [in] ref The Object to update refs for.
     */
    void SetArrayValue(
        Symbol key, int idx, const DataNode &arrVal, DataArray *tdef, Hmx::Object *ref
    );

    /** Search for a key in the dictionary, and remove the DataNode of the resulting
     * DataArray value at index idx.
     * @param [in] key The key to search for.
     * @param [in] idx The index of the resulting DataArray value in which to insert
     * arrVal.
     * @param [in] tdef The type def DataArray to search in, if the key isn't in the
     * dictionary.
     * @param [in] ref The Object to update refs for.
     */
    void RemoveArrayValue(Symbol key, int idx, DataArray *tdef, Hmx::Object *ref);

    /** Search for a key in the dictionary, and return the value DataNode.
     * @param [in] key The key to search for.
     * @param [in] fail Whether or not to fail the program if the key cannot be found.
     * @returns A DataNode containing the key's corresponding value.
     */
    DataNode *KeyValue(Symbol key, bool fail) const;

    /** Search for a key in the dictionary, and return the DataArray value.
     * @param [in] key The key to search for.
     * @param [in] typeDef The type def DataArray to search in, if the key isn't in the
     * dictionary.
     * @param [in] ref The Object to update refs for.
     * @returns The key's corresponding value, of type DataArray.
     */
    DataArray *GetArray(Symbol key, DataArray *typeDef, Hmx::Object *ref);

    /** Either adds or updates the key/value pair in the dictionary.
     * @param [in] key The key to either add or update
     * @param [in] value The corresponding value associated with the key.
     * @param [in] b TODO: currently unknown
     * @param [in] ref The Object to update refs for.
     */
    void SetKeyValue(Symbol key, const DataNode &value, bool b, Hmx::Object *ref);

    /** Replaces all instances of from in the dictionary with to.
     * @param [in] from The Object to be replaced.
     * @param [in] to The Object serving as the replacement.
     * @param [in] ref The Object to update refs for.
     */
    void Replace(Hmx::Object *from, Hmx::Object *to, Hmx::Object *ref);

    /** Get the number of properties currently in the dictionary. */
    int Size() const;

    /** Copy props' dictionary into this dictionary.
     * @param [in] props The TypeProps to copy from.
     * @param [in] ref The Object to update refs for.
     */
    void Copy(const TypeProps &props, Hmx::Object *ref);

    /** Retrieve key number idx from the dictionary.
     * @param [in] idx The number key in the dictionary to grab.
     * @returns The desired key.
     */
    Symbol Key(int idx) const;

    /** Retrieve value number idx from the dictionary.
     * @param [in] idx The number value in the dictionary to grab.
     * @returns The desired value.
     */
    DataNode &Value(int idx) const;
};

/** A reference to an Object type. */
class ObjRef {
public:
    ObjRef() {}
    virtual ~ObjRef() {}

    /** Get the owner of this Hmx::Object reference. */
    virtual Hmx::Object *RefOwner() = 0;

    /** Removes the properties from the first Hmx::Object, and moves them to the second.
     * @param [in] from The Object from which to remove properties.
     * @param [in] to The Object to which to add the removed properties.
     */
    virtual void Replace(Hmx::Object *from, Hmx::Object *to) = 0;

    /** Returns whether or not this object is an ObjDirPtr. */
    virtual bool IsDirPtr() { return false; }
};

typedef Hmx::Object *ObjectFunc(void);

namespace Hmx {
    /**
     * @brief: The base class from which all major Objects used in-game build upon.
     * Original _objects description:
     * "The Object class is the root of the class hierarchy. Every
     * class has Object as a superclass."
     */
    class Object : public ObjRef {
    protected:
        /** An array of properties this Object can have. */
        TypeProps mTypeProps; // 0x4

        /** An Object in the process of being deleted. */
        static Object *sDeleting;

        /** Handler to get the value of a given Object property.
         * @param [in] arr The supplied DataArray.
         * @returns The property value.
         * Expected DataArray contents:
         *     Node 2: The property to search for, either as a Symbol or DataArray.
         *     Node 3: The fallback value if no property is found.
         * Example usage: {$this get some_value 69}
         */
        DataNode OnGet(const DataArray *arr);

    private:
        /** A collection of handler methods this Object can have.
         *  More specifically, this is an array of arrays, with each array
         *  housing a name, followed by a handler script.
         *  Formatted in the style of:
         *  ( (name1 {handler1}) (name2 {handler2}) (name3 {handler3}) )
         */
        DataArray *mTypeDef; // 0x8
        /** This Object's name. */
        const char *mName; // 0xc
        /** The ObjectDir in which this Object resides. */
        class ObjectDir *mDir; // 0x10
        /** A collection of object instances which reference this Object. */
        std::vector<ObjRef *> mRefs; // 0x14

        /** A collection of Object class names and their corresponding instantiators. */
        static std::map<Symbol, ObjectFunc *> sFactories;

        /** Remove this Object from its associated ObjectDir. */
        void RemoveFromDir();

        /** Handler to execute dta for each of this Object's refs.
         * @param [in] arr The supplied DataArray.
         * Expected DataArray contents:
         *     Node 2: The variable representing the current ObjRef's owner.
         *     Node 3+: Any commands to execute.
         * Example usage: {$this iterate_refs $ref {$ref set 0}}
         */
        DataNode OnIterateRefs(const DataArray *arr);

        /** Handler to set this Object's properties.
         * @param [in] arr The supplied DataArray.
         * Expected DataArray contents:
         *     Node 2+: The property key to set. Must be either a Symbol or a DataArray.
         *     Node 3+: The corresponding property value to set.
         * Example usage: {$this set key1 val1 key2 val2 key3 val3}
         */
        DataNode OnSet(const DataArray *arr);
        DataNode OnPropertyAppend(const DataArray *);

        const char *AllocHeapName();

    public:
        // o7 farts, you will be missed
        enum CopyType {
            kCopyDeep = 0,
            kCopyShallow = 1,
            kCopyFromMax = 2,
        };

        Object();
        Object(const Object &);
        virtual Hmx::Object *RefOwner() { return this; }

        /** This Object's class name. */
        OBJ_CLASSNAME(Object);
        /** Set this Object's mTypeDef array based this Object's types entry in
         * SystemConfig. */
        OBJ_SET_TYPE(Object);

        /** Execute code based on the contents of a received message.
         * @param [in] _msg The received message.
         * @param [in] _warn If true, and the message goes unhandled, print to console.
         * @returns The return value of whatever code was executed.
         */
        virtual DataNode Handle(DataArray *_msg, bool _warn = true);

        /** Syncs an Object's property to or from a supplied DataNode.
         * @param [out] _val A DataNode to either place the property val into, or set the
         * property val with.
         * @param [in] _prop The DataArray containing the symbol representing the property
         * to sync.
         * @param [in] _i The index in _prop containing the symbol of the property to
         * sync.
         * @param [in] _op The operation to be performed with the property.
         * @returns Returns true if a property was synced, or if the desired index == the
         * prop array size.
         */
        virtual bool SyncProperty(DataNode &_val, DataArray *_prop, int _i, PropOp _op);
        virtual ~Object();

        /** Saves this Object into a BinStream. */
        virtual void Save(BinStream &);

        /** Copy the contents of another Object into this Object based on the CopyType.
         * @param [in] o The other Object to copy from.
         * @param [in] ty The copy type.
         */
        virtual void Copy(const Hmx::Object *o, Hmx::Object::CopyType ty);

        /** Loads this Object from a BinStream. */
        virtual void Load(BinStream &);

        /** Any routines to write relevant data to a BinStream before the main Save method
         * executes. */
        virtual void PreSave(BinStream &) {}
        /** Any routines to write relevant data to a BinStream after the main Save method
         * executes. */
        virtual void PostSave(BinStream &) {}
        /** Prints relevant info about this Object to the debug console. */
        virtual void Print() {}
        virtual void Export(DataArray *, bool) {}
        /** Set this Object's mTypeDef array.
         * @param [in] a The array to set.
         */
        virtual void SetTypeDef(DataArray *a);
        /** Sets this Object's name and updates the ObjectDir this Object resides in.
         * @param [in] name The name to give this Object.
         * @param [in] dir The ObjectDir to place this Object in. If name is null, this
         * Object won't have a set ObjectDir.
         */
        virtual void SetName(const char *name, class ObjectDir *dir);
        virtual class ObjectDir *DataDir();
        /** Any routines to read relevant data from a BinStream before the main Load
         * method executes. */
        virtual void PreLoad(BinStream &);
        /** Any routines to read relevant data from a BinStream after the main Load method
         * executes. */
        virtual void PostLoad(BinStream &) {}
        /** Get this Object's path name. */
        virtual const char *FindPathName();
        virtual void Replace(Hmx::Object *, Hmx::Object *);

        /** Create a new Object derivative based on its entry in the factory list. */
        template <class T>
        static T *New() {
            T *obj = dynamic_cast<T *>(Hmx::Object::NewObject(T::StaticClassName()));
#ifdef MILO_DEBUG
            if (!obj)
                MILO_FAIL("Couldn't instantiate class %s", T::StaticClassName());
#endif
            return obj;
        }

        const DataArray *TypeDef() const { return mTypeDef; }
        const char *Name() const { return mName; }
        class ObjectDir *Dir() const { return mDir; }
        const std::vector<ObjRef *> &Refs() const { return mRefs; }
        Symbol Type() const {
            if (mTypeDef)
                return mTypeDef->Sym(0);
            else
                return Symbol();
        }

        NEW_OBJ(Object)
        static void Init() { REGISTER_OBJ_FACTORY(Object) }

        /** Add a new Object derivative to the factory list. */
        static void RegisterFactory(Symbol, ObjectFunc *);
        /** Check if an Object derivative has an entry in the factory list. */
        static bool RegisteredFactory(Symbol);
        Object &operator=(const Object &);

        /** Search for a key in this Object's properties, and return the corresponding
         * value.
         * @param [in] prop: The property to search for, in Symbol form.
         * @param [in] fail: If true, print a message to the console if no property value
         * was found.
         * @returns The corresponding property's value as a DataNode pointer.
         */
        const DataNode *Property(Symbol prop, bool fail = true) const;

        /** Search for a key in this Object's properties, and return the corresponding
         * value.
         * @param [in] prop: The property to search for, in DataArray form. The first node
         * must be a Symbol.
         * @param [in] fail: If true, print a message to the console if no property value
         * was found.
         * @returns The corresponding property's value as a DataNode pointer.
         */
        const DataNode *Property(DataArray *prop, bool fail = true) const;

        /** Either adds or updates the key/value pair in the properties.
         * @param [in] prop The key to either add or update
         * @param [in] val The corresponding value associated with the key.
         */
        void SetProperty(Symbol prop, const DataNode &val);

        /** Either adds or updates the key/value pair in the properties.
         * @param [in] prop The key to either add or update. The first node must be a
         * Symbol.
         * @param [in] val The corresponding value associated with the key.
         */
        void SetProperty(DataArray *prop, const DataNode &val);

        /** Get the size of a property value.
         * @param [in] prop The key to find the property with. The first node must be a
         * Symbol.
         * @returns If the property is an integer, returns the integer. If the property is
         * a DataArray, returns the DataArray's size.
         */
        int PropertySize(DataArray *prop);

        /** Insert the key/value pair in the properties.
         * @param [in] prop The key to insert. The first node must be a Symbol.
         * @param [in] val The corresponding value associated with the key.
         */
        void InsertProperty(DataArray *prop, const DataNode &val);

        /** Remove this property from this Object.
         * @param [in] prop The key to remove. The first node must be a Symbol.
         */
        void RemoveProperty(DataArray *prop);
        void PropertyClear(DataArray *);

        /** Add this Object reference into mRefs.
         * @param [in] ref The reference to add.
         */
        void AddRef(ObjRef *ref);

        /** Remove this Object reference from mRefs.
         * @param [in] ref The reference to remove.
         */
        void Release(ObjRef *ref);

        static Object *NewObject(Symbol);

        /** Write's this Object's rev values and its Type Symbol to the BinStream. */
        void SaveType(BinStream &);
        /** Write's this Object's TypeProps to the BinStream. */
        void SaveRest(BinStream &);
        void LoadType(BinStream &);
        void LoadRest(BinStream &);

        DataNode HandleType(DataArray *);
        DataNode PropertyArray(Symbol);
        DataNode HandleProperty(DataArray *, DataArray *, bool);

        static unsigned short gRev;
        static unsigned short gAltRev;
    };
}

struct ObjPair {
    ObjPair(Hmx::Object *o1, Hmx::Object *o2) : from(o1), to(o2) {}

    Hmx::Object *from;
    Hmx::Object *to;
};

struct ObjMatchPr {
    bool operator()(const Hmx::Object *&value) { return value == obj; }
    Hmx::Object *obj;
};

struct AlphaSort {
    bool operator()(Hmx::Object *o1, Hmx::Object *o2) const {
        return strcmp(o1->Name(), o2->Name()) < 0;
    }
};

inline TextStream &operator<<(TextStream &ts, const Hmx::Object *obj) {
    if (obj)
        ts << obj->Name();
    else
        ts << "<null>";
    return ts;
}

inline unsigned short getHmxRev(int packed) { return packed; }

inline unsigned short getAltRev(int packed) { return (unsigned int)packed >> 0x10; }

inline int packRevs(unsigned short alt, unsigned short rev) {
    return (rev & ~0xFFFF0000) | (alt << 0x10);
}

#define NULL_OBJ (Hmx::Object *)nullptr
