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
        const char* symbol;
        int integer;
        float real;
        DataArray* array;
        DataNode* var;
        DataFunc* func;
        Hmx::Object* object;
    } mValue; // 0x0
    /** The type of this DataNode. Used to verify which member of the union is currently being stored. */
    DataType mType; // 0x4

    DataNode(){
        mValue.integer = 0;
        mType = kDataInt;
    }

    DataNode(int i){
        mValue.integer = i;
        mType = kDataInt;
    }

    DataNode(long l){
        mValue.integer = l;
        mType = kDataInt;
    }

    DataNode(Symbol s){
        mType = kDataSymbol;
        mValue.symbol = s.mStr;
    }

    DataNode(Hmx::Object* obj){
        mValue.object = obj;
        mType = kDataObject;
    }

    DataNode(DataType ty, int i){
        mType = ty;
        mValue.integer = i;
    }

    DataNode(DataType ty, const char* s){
        mType = ty;
        mValue.symbol = s;
    }

    DataNode(float f){
        mValue.real = f;
        mType = kDataFloat;
    }

    DataNode(const DataNode&);
    DataNode(const char* string);
    DataNode(const class String& string);
    DataNode(const void* glob, int size);
    DataNode(const DataArrayPtr&);
    DataNode(DataArray* array, DataType type);

    DataNode(DataNode* var){
        mValue.var = var;
        mType = kDataVar;
    }

    DataNode(DataFunc* func){
        mValue.func = func;
        mType = kDataFunc;
    }

    ~DataNode();

    DataType Type() const { return mType; }
    bool CompatibleType(DataType) const;
    DataNode& Evaluate() const;

    // these were implemented to match up in retail
    // please do not use these in regular code
    int UncheckedInt() const { return mValue.integer; }
    const char* UncheckedStr() const { return mValue.symbol; }
    Hmx::Object* UncheckedObj() const { return mValue.object; }
    DataArray* UncheckedArray() const { return mValue.array; }
    DataNode* UncheckedVar() const { return mValue.var; }

    int Int(const DataArray* source = nullptr) const;
    int LiteralInt(const DataArray* source = nullptr) const;
    Symbol Sym(const DataArray* source = nullptr) const;
    Symbol LiteralSym(const DataArray* source = nullptr) const;
    Symbol ForceSym(const DataArray* source = nullptr) const;
    const char* Str(const DataArray* source = nullptr) const;
    const char* LiteralStr(const DataArray* source = nullptr) const;
    void* Glob(int* size, const DataArray* source = nullptr) const;
    float Float(const DataArray* source = nullptr) const;
    float LiteralFloat(const DataArray* source = nullptr) const;
    DataFunc* Func(const DataArray* source = nullptr) const;
    Hmx::Object* GetObj(const DataArray* source = nullptr) const;
    DataArray* Array(const DataArray* source = nullptr) const;
    DataArray* LiteralArray(const DataArray* source = nullptr) const;
    DataArray* Command(const DataArray* source = nullptr) const;
    DataNode* Var(const DataArray* source = nullptr) const;

    // for retrieving a Hmx::Object derivative from a DataNode
    template <class T>
    T* Obj(const DataArray* source = nullptr) const {
        return dynamic_cast<T*>(GetObj(source));
    }

    bool operator==(const DataNode& n) const;
    bool operator!=(const DataNode& n) const;
    bool NotNull() const;
    bool operator!() const {
        return !NotNull();
    }
    DataNode& operator=(const DataNode& n);

    /** Print the DataNode's contents to the TextStream.
     * @param [in] s The TextStream to print to.
     * @param [in] b TODO: currently unknown
     */
    void Print(TextStream& s, bool) const;
    bool PrintUnused(TextStream&, bool) const;
    /** Saves this DataNode into a BinStream. */
    void Save(BinStream& d) const;
    /** Loads this DataNode from a BinStream. */
    void Load(BinStream& d);
};

/** An array of DataNodes. */
class DataArray {
public:
    /** The collection of DataNodes in this DataArray. */
    DataNode* mNodes;   // 0x0
    /** The file this DataArray is in. */
    Symbol mFile;       // 0x4
    /** The number of nodes in this DataArray. */
    short mSize;        // 0x8
    /** The number of references to this DataArray. */
    short mRefs;        // 0xA
    /** The line of the file this DataArray is in. */
    short mLine;        // 0xC
    /** unused */
    short mDeprecated;  // 0xE
    static Symbol gFile;
    static DataFunc* sDefaultHandler;

    static int NodeCmp(const void*, const void*);
    static void SetFile(Symbol);

    const char* File() const { return mFile.mStr; }
    int Size() const { return mSize; }
    int Line() const { return mLine; }

    int UncheckedInt(int i) const { return Node(i).UncheckedInt(); }
    Hmx::Object* UncheckedObj(int i) const { return Node(i).UncheckedObj(); }
    DataNode* UncheckedVar(int i) const { return Node(i).UncheckedVar(); }
    DataArray* UncheckedArray(int i) const { return Node(i).UncheckedArray(); }

    DataType Type(int i) const { return Node(i).Type(); }
    int Int(int i) const { return Node(i).Int(this); }
    Symbol Sym(int i) const { return Node(i).Sym(this); }
    Symbol LiteralSym(int i) const { return Node(i).LiteralSym(this); }
    Symbol ForceSym(int i) const { return Node(i).ForceSym(this); }
    const char* Str(int i) const { return Node(i).Str(this); }
    const char* LiteralStr(int i) const { return Node(i).LiteralStr(this); }
    float Float(int i) const { return Node(i).Float(this); }
    Hmx::Object* GetObj(int i) const { return Node(i).GetObj(this); }
    DataArray* Array(int i) const { return Node(i).Array(this); }
    DataArray* Command(int i) const { return Node(i).Command(this); }
    DataNode* Var(int i) const { return Node(i).Var(this); }
    template <class T> T* Obj(int i) const {
        return Node(i).Obj<T>(this);
    }

    void AddRef(){ mRefs++; }
    void Release(){ if (--mRefs == 0) delete this; }

    // these two are actually strong symbols
    DataNode& Node(int i);
    DataNode& Node(int i) const;

    void Print(TextStream& s, DataType type, bool compact) const;
    bool PrintUnused(TextStream&, DataType, bool) const;
    void Insert(int index, const DataNode& node);
    void InsertNodes(int index, const DataArray* array);
    void Resize(int size);
    void Remove(int index);
    void Remove(const DataNode& node);
    bool Contains(const DataNode& node) const;

    DataArray* FindArray(int tag, bool fail) const;
    DataArray* FindArray(Symbol tag, bool fail) const;
    DataArray* FindArray(Symbol s1, Symbol s2) const;
    DataArray* FindArray(Symbol s1, Symbol s2, Symbol s3) const;
    DataArray* FindArray(Symbol, const char*) const;

    bool FindData(Symbol tag, const char *& ret, bool fail) const;
    bool FindData(Symbol tag, Symbol & ret, bool fail) const;
    bool FindData(Symbol tag, class String & ret, bool fail) const;
    bool FindData(Symbol tag, int & ret, bool fail) const;
    bool FindData(Symbol tag, float & ret, bool fail) const;
    bool FindData(Symbol tag, bool & ret, bool fail) const;
    bool FindData(Symbol tag, class Vector2 & ret, bool fail) const;
    bool FindData(Symbol tag, class Vector3 & ret, bool fail) const;
    bool FindData(Symbol tag, class Plane & ret, bool fail) const;
    bool FindData(Symbol tag, Hmx::Color & ret, bool fail) const;

    int FindInt(Symbol tag) const { return FindArray(tag, true)->Int(1); }
    float FindFloat(Symbol tag) const { return FindArray(tag, true)->Float(1); }
    Symbol FindSym(Symbol tag) const { return FindArray(tag, true)->Sym(1); }
    const char* FindStr(Symbol tag) const { return FindArray(tag, true)->Str(1); }

    /** Clone this DataArray.
     * @param [in] deep If true, perform a deep copy on this DataArray.
     * @param [in] eval If true, evaluate each DataNode before cloning it.
     * @param [in] extra The number of extra DataNode slots to allocate for the clone.
     * @returns The newly created DataArray clone.
     */
    DataArray* Clone(bool deep, bool eval, int extra);

    DataArray(int size);
    DataArray(const void* glob, int size);
    ~DataArray();

    void SetFileLine(Symbol, int);
    /** Sort the nodes in this DataArray. */
    void SortNodes();
    DataNode Execute();
    DataNode ExecuteBlock(int);
    /** Saves this DataArray into a BinStream. */
    void Save(BinStream& d) const;
    /** Loads this DataArray from a BinStream. */
    void Load(BinStream& d);
    void SaveGlob(BinStream& d, bool str) const;
    void LoadGlob(BinStream& d, bool str);
    DataNode ExecuteScript(int firstCmd, Hmx::Object* _this, const DataArray* _args, int firstArg);
    DataNode& Evaluate(int i) const {
        return Node(i).Evaluate();
    }

    NEW_POOL_OVERLOAD(DataArray);
    DELETE_POOL_OVERLOAD(DataArray);
};

inline BinStream& operator<<(BinStream &bs, const DataNode& node) {
    node.Save(bs);
    return bs;
}

inline BinStream& operator>>(BinStream& bs, DataNode& node){
    node.Load(bs);
    return bs;
}

TextStream& operator<<(TextStream&, const DataArray*);
BinStream& operator>>(BinStream&, DataArray*&);
BinStream& operator<<(BinStream&, const DataArray*);

inline DataNode::~DataNode(){
    if((mType & kDataArray) != 0) mValue.array->Release();
}

DataNode& DataVariable(Symbol);
bool DataVarExists(Symbol);
bool DataArrayDefined();
const char* DataVarName(const DataNode*);

// to properly generate DataArray::Node const vs non-const
#define CONST_ARRAY(array) ((const DataArray*)(array))
#define UNCONST_ARRAY(array) ((DataArray*)(array))

/** A smart pointer that manages the lifetime of a DataArray. */
class DataArrayPtr {
public:

    DataArrayPtr(){
        mData = new DataArray(0);
    }

    DataArrayPtr(const DataNode& node){
        mData = new DataArray(1);
        mData->Node(0) = node;
    }

    DataArrayPtr(const DataNode& node, const DataNode& node2){
        mData = new DataArray(2);
        mData->Node(0) = node;
        mData->Node(1) = node2;
    }

    DataArrayPtr(const DataNode& node, const DataNode& node2, const DataNode& node3){
        mData = new DataArray(3);
        mData->Node(0) = node;
        mData->Node(1) = node2;
        mData->Node(2) = node3;
    }

    DataArrayPtr(const DataNode& node, const DataNode& node2, const DataNode& node3, const DataNode& node4){
        mData = new DataArray(4);
        mData->Node(0) = node;
        mData->Node(1) = node2;
        mData->Node(2) = node3;
        mData->Node(3) = node4;
    }

    DataArrayPtr(DataArray* arr){
        mData = arr;
        if(!mData) mData = new DataArray(0);
    }

    DataArrayPtr& operator=(DataArray* arr){
        if(mData != arr){
            mData->Release();
            mData = arr;
            if(arr) arr->AddRef();
            else mData = new DataArray(0);
        }
        return *this;
    }

    operator DataArray*() const { return mData; }
    DataArray* operator->() const { return mData; }

    DataArray* mData;

    ~DataArrayPtr(){ mData->Release(); }
    DataNode& Node(int i) const { return mData->Node(i); }
};

inline BinStream& operator>>(BinStream& bs, DataArrayPtr& ptr) { ptr.mData->Load(bs); return bs; }
