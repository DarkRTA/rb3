#ifndef OBJ_DATA_H
#define OBJ_DATA_H
#include "utl/BinStream.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "utl/TextStream.h"
//#include "math/Vec.h"
#include "math/Color.h"

// forward declarations
class DataNode;
class DataArray;
class DataArrayPtr;
namespace Hmx {
    class Object;
}

typedef DataNode DataFunc(DataArray *);

union DataNodeValue {
    const char* symbol;
    int integer;
    float real;
    DataArray* array;
    DataNode* var;
    DataFunc* func;
    Hmx::Object* object;
};

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

class DataNode {
public:
    DataNodeValue mValue;
    DataType mType;

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
    DataNodeValue RawVal() { return mValue; }
    bool CompatibleType(DataType) const;
    DataNode& Evaluate() const;

    int Int(const DataArray* a) const;
    int LiteralInt(const DataArray* a) const;
    Symbol Sym(const DataArray* a) const;
    Symbol LiteralSym(const DataArray* a) const;
    Symbol ForceSym(const DataArray* a) const;
    const char* Str(const DataArray* a) const;
    const char* LiteralStr(const DataArray* a) const;
    void* Glob(int* size, const DataArray* a) const;
    float Float(const DataArray* a) const;
    float LiteralFloat(const DataArray* a) const;
    DataFunc* Func(const DataArray* a) const;
    Hmx::Object* GetObj(const DataArray* a) const;
    DataArray* Array(const DataArray* a) const;
    DataArray* LiteralArray(const DataArray* a) const;
    DataArray* Command(const DataArray* a) const;
    DataNode* Var(const DataArray* a) const;
    // for retrieving a Hmx::Object derivative from a DataNode
    template <class T> T* Obj(const DataArray* a) const {
        return dynamic_cast<T*>(GetObj(a));
    }

    bool operator==(const DataNode& n) const;
    bool operator!=(const DataNode& n) const;
    bool NotNull() const;
    bool operator!(void) const {
        return !NotNull();
    }
    DataNode& operator=(const DataNode& n);

    void Print(TextStream& s, bool) const;
    bool PrintUnused(TextStream&, bool) const;
    void Save(BinStream& d) const;
    void Load(BinStream& d);
};

class DataArray {
public:
    DataNode* mNodes;   // 0x0
    Symbol mFile;       // 0x4
    short mSize;        // 0x8
    short mRefs;        // 0xA
    short mLine;        // 0xC
    short mDeprecated;  // 0xE
    static Symbol gFile;
    static DataFunc* sDefaultHandler;

    static int NodeCmp(const void*, const void*);
    static void SetFile(Symbol);

    const char* File() const { return mFile.mStr; }
    int Size() const { return mSize; }
    int Line() const { return mLine; }

    DataType Type(int i) const { return Node(i).Type(); }
    int Int(int i) const { return Node(i).Int(this); }
    Symbol Sym(int i) const { return Node(i).Sym(this); }
    Symbol LiteralSym(int i) const { return Node(i).LiteralSym(this); }
    Symbol ForceSym(int i) const { return Node(i).ForceSym(this); }
    const char* Str(int i) const { return Node(i).Str(this); }
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
    // void* operator new(unsigned long); make the param size_t?

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

    DataArray* Clone(bool deep, bool eval, int);

    DataArray(int size);
    DataArray(const void* glob, int size);
    ~DataArray();

    void SetFileLine(Symbol, int);
    void SortNodes();
    DataNode Execute();
    DataNode ExecuteBlock(int);
    void Save(BinStream& d) const;
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

TextStream& operator<<(TextStream&, const DataArray*);
BinStream& operator>>(BinStream&, DataArray*&);
BinStream& operator<<(BinStream&, const DataArray*);

inline DataNode::~DataNode(){
    if((mType & kDataArray) != 0) mValue.array->Release();
}

DataNode& DataVariable(Symbol);
bool DataVarExists(Symbol);
bool DataArrayDefined();

// to properly generate DataArray::Node const vs non-const
#define CONST_ARRAY(array) ((const DataArray*)(array))
#define UNCONST_ARRAY(array) ((DataArray*)(array))

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

#endif
