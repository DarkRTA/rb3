#pragma once
#include "utl/BinStream.h"
#include "utl/PoolAlloc.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "utl/TextStream.h"
#include "math/Color.h"

// forward declarations
class DataNode;
class DataArray;
class DataArrayPtr;
namespace Hmx {
    class Object;
}

/** A function which can be called by a script/command. */
typedef DataNode DataFunc(DataArray *);

/** The possible DataNode types. */
enum DataType {
    kDataUnhandled = 0,
    kDataFloat = 1,
    kDataVar = 2,
    kDataFunc = 3,
    kDataObject = 4,
    kDataSymbol = 5,
    kDataInt = 6,
    kDataIfdef = 7,
    kDataElse = 8,
    kDataEndif = 9,
    kDataArray = 16,
    kDataCommand = 17,
    kDataString = 18,
    kDataProperty = 19,
    kDataGlob = 20,
    kDataDefine = 32,
    kDataInclude = 33,
    kDataMerge = 34,
    kDataIfndef = 35,
    kDataAutorun = 36,
    kDataUndef = 37,
};

/** A value which can be configured and accessed by scripts. */
class DataNode {
public:
    /** The possible data types that a DataNode can have. */
    union {
        const char *symbol;
        int integer;
        float real;
        DataArray *array;
        DataNode *var;
        DataFunc *func;
        Hmx::Object *object;
    } mValue; // 0x0
    /** The type of this DataNode. Used to verify which member of the union is currently
     * being stored. */
    DataType mType; // 0x4

    DataNode() {
        mValue.integer = 0;
        mType = kDataInt;
    }

    DataNode(int i) {
        mValue.integer = i;
        mType = kDataInt;
    }

    DataNode(long l) {
        mValue.integer = l;
        mType = kDataInt;
    }

    DataNode(Symbol s) {
        mType = kDataSymbol;
        mValue.symbol = s.mStr;
    }

    DataNode(Hmx::Object *obj) {
        mValue.object = obj;
        mType = kDataObject;
    }

    DataNode(DataType ty, int i) {
        mType = ty;
        mValue.integer = i;
    }

    DataNode(DataType ty, const char *s) {
        mType = ty;
        mValue.symbol = s;
    }

    DataNode(float f) {
        mValue.real = f;
        mType = kDataFloat;
    }

    DataNode(const DataNode &);
    DataNode(const char *string);
    DataNode(const class String &string);
    // DataNode(const void *glob, int size); // goes unused
    DataNode(const DataArrayPtr &);
    DataNode(DataArray *array, DataType type);

    DataNode(DataNode *var) {
        mValue.var = var;
        mType = kDataVar;
    }

    DataNode(DataFunc *func) {
        mValue.func = func;
        mType = kDataFunc;
    }

    ~DataNode();

    DataType Type() const { return mType; }

    /** Is this node's type compatible with the supplied DataType?
     * @param [in] t The DataType in question
     * @returns True if the two types are compatible, false if not.
     */
    bool CompatibleType(DataType t) const;

    /** Evaluate the contents of this DataNode and return the result.
     * @returns A DataNode with the results of the evaluation.
     */
    const DataNode &Evaluate() const;

    // these were implemented to match up in retail
    // please do not use these in regular code
    int UncheckedInt() const { return mValue.integer; }
    const char *UncheckedStr() const { return mValue.symbol; }
    Hmx::Object *UncheckedObj() const { return mValue.object; }
    DataArray *UncheckedArray() const { return mValue.array; }
    DataNode *UncheckedVar() const { return mValue.var; }
    DataFunc *UncheckedFunc() const { return mValue.func; }

    /** Evalute this DataNode, and return the resulting int.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The resulting int from this DataNode.
     */
    int Int(const DataArray *source = nullptr) const;

    /** Return the int directly inside of this DataNode.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The aforementioned int.
     */
    int LiteralInt(const DataArray *source = nullptr) const;

    /** Evalute this DataNode, and return the resulting Symbol.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The resulting Symbol from this DataNode.
     */
    Symbol Sym(const DataArray *source = nullptr) const;

    /** Return the Symbol directly inside of this DataNode.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The aforementioned Symbol.
     */
    Symbol LiteralSym(const DataArray *source = nullptr) const;
    Symbol ForceSym(const DataArray *source = nullptr) const;

    /** Evalute this DataNode, and return the resulting string.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The resulting string from this DataNode.
     */
    const char *Str(const DataArray *source = nullptr) const;

    /** Return the string directly inside of this DataNode.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The aforementioned string.
     */
    const char *LiteralStr(const DataArray *source = nullptr) const;

    // void *Glob(int *size, const DataArray *source = nullptr) const; // deadstripped lol

    /** Evalute this DataNode, and return the resulting float.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The resulting float from this DataNode.
     */
    float Float(const DataArray *source = nullptr) const;

    /** Return the float directly inside of this DataNode.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The aforementioned float.
     */
    float LiteralFloat(const DataArray *source = nullptr) const;

    /** Return the DataFunc directly inside of this DataNode.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The aforementioned DataFunc.
     */
    DataFunc *Func(const DataArray *source = nullptr) const;

    /** Evalute this DataNode, and return the resulting Hmx::Object.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The resulting Hmx::Object from this DataNode.
     */
    Hmx::Object *GetObj(const DataArray *source = nullptr) const;

    /** Evalute this DataNode, and return the resulting DataArray.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The resulting DataArray from this DataNode.
     */
    DataArray *Array(const DataArray *source = nullptr) const;

    /** Return the DataArray directly inside of this DataNode.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The aforementioned DataArray.
     */
    DataArray *LiteralArray(const DataArray *source = nullptr) const;

    /** Return the command DataArray directly inside of this DataNode.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The aforementioned DataArray.
     */
    DataArray *Command(const DataArray *source = nullptr) const;

    /** Return the var DataNode directly inside of this DataNode.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The aforementioned DataNode.
     */
    DataNode *Var(const DataArray *source = nullptr) const;

    /** Get the Hmx::Object derivative resulting from this DataNode.
     * @param [in] source The DataArray this DataNode comes from.
     * @returns The aforementioned Hmx::Object derivative.
     */
    template <class T>
    T *Obj(const DataArray *source = nullptr) const {
        return dynamic_cast<T *>(GetObj(source));
    }

    bool operator==(const DataNode &n) const;
    bool operator!=(const DataNode &n) const;
    bool NotNull() const;
    bool operator!() const { return !NotNull(); }
    DataNode &operator=(const DataNode &n);

    /** Print the DataNode's contents to the TextStream.
     * @param [in] s The TextStream to print to.
     * @param [in] compact If true, print any strings in a compact manner.
     */
    void Print(TextStream &s, bool compact) const;
    /** As the name would indicate, this goes unused. */
    bool PrintUnused(TextStream &, bool) const;
    /** Saves this DataNode into a BinStream. */
    void Save(BinStream &d) const;
    /** Loads this DataNode from a BinStream. */
    void Load(BinStream &d);
};

/** An array of DataNodes. */
class DataArray {
public:
    /** The collection of DataNodes in this DataArray. */
    DataNode *mNodes; // 0x0
    /** The file this DataArray is in. */
    Symbol mFile; // 0x4
    /** The number of nodes in this DataArray. */
    short mSize; // 0x8
    /** The number of references to this DataArray. */
    short mRefs; // 0xA
    /** The line of the file this DataArray is in. */
    short mLine; // 0xC
    /** unused, supposedly node number in dtb, for debugging */
    short mDeprecated; // 0xE
    static Symbol gFile;
    static DataFunc *sDefaultHandler;

    static int NodeCmp(const void *, const void *);
    static void SetFile(Symbol);

    const char *File() const { return mFile.mStr; }
    int Size() const { return mSize; }
    int Line() const { return mLine; }

    int UncheckedInt(int i) const { return Node(i).UncheckedInt(); }
    Hmx::Object *UncheckedObj(int i) const { return Node(i).UncheckedObj(); }
    DataNode *UncheckedVar(int i) const { return Node(i).UncheckedVar(); }
    DataArray *UncheckedArray(int i) const { return Node(i).UncheckedArray(); }
    DataFunc *UncheckedFunc(int i) const { return Node(i).UncheckedFunc(); }

    /** Get the DataType at the given node index.
     * @param [in] i The node index.
     * @returns The resulting DataType.
     */
    DataType Type(int i) const { return Node(i).Type(); }

    /** Get the int at the given node index.
     * @param [in] i The node index.
     * @returns The resulting int.
     */
    int Int(int i) const { return Node(i).Int(this); }

    /** Get the Symbol at the given node index.
     * @param [in] i The node index.
     * @returns The resulting Symbol.
     */
    Symbol Sym(int i) const { return Node(i).Sym(this); }

    /** Get the literal Symbol at the given node index.
     * @param [in] i The node index.
     * @returns The resulting Symbol.
     */
    Symbol LiteralSym(int i) const { return Node(i).LiteralSym(this); }
    Symbol ForceSym(int i) const { return Node(i).ForceSym(this); }

    /** Get the string at the given node index.
     * @param [in] i The node index.
     * @returns The resulting string.
     */
    const char *Str(int i) const { return Node(i).Str(this); }

    /** Get the literal string at the given node index.
     * @param [in] i The node index.
     * @returns The resulting string.
     */
    const char *LiteralStr(int i) const { return Node(i).LiteralStr(this); }

    /** Get the float at the given node index.
     * @param [in] i The node index.
     * @returns The resulting float.
     */
    float Float(int i) const { return Node(i).Float(this); }

    /** Get the Hmx::Object at the given node index.
     * @param [in] i The node index.
     * @returns The resulting Hmx::Object.
     */
    Hmx::Object *GetObj(int i) const { return Node(i).GetObj(this); }

    /** Get the DataArray at the given node index.
     * @param [in] i The node index.
     * @returns The resulting DataArray.
     */
    DataArray *Array(int i) const { return Node(i).Array(this); }

    /** Get the command DataArray at the given node index.
     * @param [in] i The node index.
     * @returns The resulting command DataArray.
     */
    DataArray *Command(int i) const { return Node(i).Command(this); }

    /** Get the var DataNode at the given node index.
     * @param [in] i The node index.
     * @returns The resulting var DataNode.
     */
    DataNode *Var(int i) const { return Node(i).Var(this); }

    /** Get the Hmx::Object derivative at the given node index.
     * @param [in] i The node index.
     * @returns The resulting Hmx::Object derivative.
     */
    template <class T>
    T *Obj(int i) const {
        return Node(i).Obj<T>(this);
    }

    /** Increment this DataArray's reference count. */
    void AddRef() { mRefs++; }
    /** Decrement this DataArray's reference count. */
    void Release() {
        if (--mRefs == 0)
            delete this;
    }

    /** Get the DataNode at the given node index.
     * @param [in] i The node index.
     * @returns The resulting DataNode.
     */
    DataNode &Node(int i);
    /** Get the DataNode at the given node index.
     * @param [in] i The node index.
     * @returns The resulting DataNode.
     */
    DataNode &Node(int i) const;

    /** Print the DataArray's contents to the TextStream.
     * @param [in] s The TextStream to print to.
     * @param [in] type The type of this DataArray (array, command, property, etc)
     * @param [in] compact If true, print any strings in a compact manner.
     */
    void Print(TextStream &s, DataType type, bool compact) const;
    /** As the name would indicate, this goes unused. */
    bool PrintUnused(TextStream &, DataType, bool) const;

    /** Insert the supplied DataNode at the supplied index.
     * @param [in] index The index of the DataArray to insert in.
     * @param [in] node The DataNode to insert.
     */
    void Insert(int index, const DataNode &node);

    /** Insert the supplied DataArray's DataNodes at the supplied index.
     * @param [in] index The index of the DataArray to insert in.
     * @param [in] array The DataArray whose DataNodes we want to insert.
     */
    void InsertNodes(int index, const DataArray *array);

    /** Resize the DataArray.
     * @param [in] size The desired new size of the DataArray.
     */
    void Resize(int size);

    /** Remove the DataNode at the supplied index.
     * @param [in] index The index of the DataArray to remove.
     */
    void Remove(int index);

    /** Remove the DataNode from this DataArray.
     * @param [in] node The DataNode to remove.
     */
    void Remove(const DataNode &node);

    /** Is the supplied DataNode part of this DataArray?
     * @param [in] node The DataNode.
     * @returns True if the supplied DataNode is in this DataArray, false if not.
     */
    bool Contains(const DataNode &node) const;

    DataArray *FindArray(int tag, bool fail = true) const;
    DataArray *FindArray(Symbol tag, bool fail = true) const;
    DataArray *FindArray(Symbol s1, Symbol s2) const;
    DataArray *FindArray(Symbol s1, Symbol s2, Symbol s3) const;
    DataArray *FindArray(Symbol, const char *) const;

    bool FindData(Symbol tag, const char *&ret, bool fail = true) const;
    bool FindData(Symbol tag, Symbol &ret, bool fail = true) const;
    bool FindData(Symbol tag, class String &ret, bool fail = true) const;
    bool FindData(Symbol tag, int &ret, bool fail = true) const;
    bool FindData(Symbol tag, float &ret, bool fail = true) const;
    bool FindData(Symbol tag, bool &ret, bool fail = true) const;
    bool FindData(Symbol tag, class Vector2 &ret, bool fail = true) const;
    bool FindData(Symbol tag, class Vector3 &ret, bool fail = true) const;
    bool FindData(Symbol tag, class Plane &ret, bool fail = true) const;
    bool FindData(Symbol tag, Hmx::Color &ret, bool fail = true) const;

    int FindInt(Symbol tag) const { return FindArray(tag)->Int(1); }
    float FindFloat(Symbol tag) const { return FindArray(tag)->Float(1); }
    Symbol FindSym(Symbol tag) const { return FindArray(tag)->Sym(1); }
    const char *FindStr(Symbol tag) const { return FindArray(tag)->Str(1); }

    /** Clone this DataArray.
     * @param [in] deep If true, perform a deep copy on this DataArray.
     * @param [in] eval If true, evaluate each DataNode before cloning it.
     * @param [in] extra The number of extra DataNode slots to allocate for the clone.
     * @returns The newly created DataArray clone.
     */
    DataArray *Clone(bool deep, bool eval, int extra);

    DataArray(int size);
    DataArray(const void *glob, int size);
    ~DataArray();

    void SetFileLine(Symbol, int);
    /** Sort the nodes in this DataArray. */
    void SortNodes();

    /** Execute the value of this DataNode.
     * If the value is a DataFunc, call it directly.
     * Else, if the value is not a number,
     * retrieve the corresponding Object and call its handler.
     * @returns The return value of whatever code was executed.
     */
    DataNode Execute();

    /** Execute each Command in this DataArray, starting at the given index.
     * The final DataNode in the DataArray will be evaluated separately,
     * so it can be any DataType.
     * @param [in] idx The index to begin retrieving and executing commands from.
     * @returns The results of the evaluated final DataNode.
     */
    DataNode ExecuteBlock(int idx);
    /** Saves this DataArray into a BinStream. */
    void Save(BinStream &d) const;
    /** Loads this DataArray from a BinStream. */
    void Load(BinStream &d);
    void SaveGlob(BinStream &d, bool str) const;
    void LoadGlob(BinStream &d, bool str);

    /** Execute a script in dta.
     * @param [in] firstCmd The index of this DataArray containing the first Command.
     * @param [in] _this The value gDataThis should be during execution.
     * @param [in] _args The DataArray containing any input parameters for the script.
     * @param [in] firstArg The index in _args containing the first input parameter.
     * @returns The return value of the dta script.
     */
    DataNode
    ExecuteScript(int firstCmd, Hmx::Object *_this, const DataArray *_args, int firstArg);
    const DataNode &Evaluate(int i) const { return Node(i).Evaluate(); }

    NEW_POOL_OVERLOAD(DataArray);
    DELETE_POOL_OVERLOAD(DataArray);
};

inline TextStream &operator<<(TextStream &ts, const DataNode &node) {
    node.Print(ts, false);
    return ts;
}

inline BinStream &operator<<(BinStream &bs, const DataNode &node) {
    node.Save(bs);
    return bs;
}

inline BinStream &operator>>(BinStream &bs, DataNode &node) {
    node.Load(bs);
    return bs;
}

TextStream &operator<<(TextStream &, const DataArray *);
BinStream &operator>>(BinStream &, DataArray *&);
BinStream &operator<<(BinStream &, const DataArray *);

inline DataNode::~DataNode() {
    if ((mType & kDataArray) != 0)
        mValue.array->Release();
}

DataNode &DataVariable(Symbol);
bool DataVarExists(Symbol);
bool DataArrayDefined();
const char *DataVarName(const DataNode *);

// to properly generate DataArray::Node const vs non-const
#define CONST_ARRAY(array) ((const DataArray *)(array))
#define UNCONST_ARRAY(array) ((DataArray *)(array))

/** A smart pointer that manages the lifetime of a DataArray. */
class DataArrayPtr {
public:
    DataArrayPtr() { mData = new DataArray(0); }

    DataArrayPtr(const DataNode &node) {
        mData = new DataArray(1);
        mData->Node(0) = node;
    }

    DataArrayPtr(const DataNode &node, const DataNode &node2) {
        mData = new DataArray(2);
        mData->Node(0) = node;
        mData->Node(1) = node2;
    }

    DataArrayPtr(const DataNode &node, const DataNode &node2, const DataNode &node3) {
        mData = new DataArray(3);
        mData->Node(0) = node;
        mData->Node(1) = node2;
        mData->Node(2) = node3;
    }

    DataArrayPtr(
        const DataNode &node,
        const DataNode &node2,
        const DataNode &node3,
        const DataNode &node4
    ) {
        mData = new DataArray(4);
        mData->Node(0) = node;
        mData->Node(1) = node2;
        mData->Node(2) = node3;
        mData->Node(3) = node4;
    }

    DataArrayPtr(DataArray *da) {
        mData = da;
        if (!mData)
            mData = new DataArray(0);
    }

    DataArrayPtr &operator=(DataArray *da) {
        if (mData != da) {
            mData->Release();
            mData = da;
            if (da)
                da->AddRef();
            else
                mData = new DataArray(0);
        }
        return *this;
    }

    operator DataArray *() const { return mData; }
    DataArray *operator->() const { return mData; }

    DataArray *mData;

    ~DataArrayPtr() { mData->Release(); }
    DataNode &Node(int i) const { return mData->Node(i); }
};

inline BinStream &operator>>(BinStream &bs, DataArrayPtr &ptr) {
    ptr.mData->Load(bs);
    return bs;
}

#define HANDLE_STACK_SIZE 100
extern DataArray *gCallStack[HANDLE_STACK_SIZE];
extern DataArray **gCallStackPtr;
extern DataFunc *gPreExecuteFunc;
extern int gPreExecuteLevel;