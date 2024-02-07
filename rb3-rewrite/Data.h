#ifndef OBJ_DATA_H
#define OBJ_DATA_H

// remove these once you #include the appropriate files
class Symbol; 
class String;
class TextStream;
class BinStream;
class Vector2;
class Vector3;
class Plane;
namespace Hmx {
    class Color;
}

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

    DataNode(Symbol);
    DataNode(Hmx::Object*);
    DataNode(DataType, int);
    DataNode(float);
    DataNode(const DataNode&);
    DataNode(const char* string);
    DataNode(const String& string);
    DataNode(const void* glob, int size);
    DataNode(const DataArrayPtr&);
    DataNode(DataArray* array, DataType type);
    DataNode(DataNode*);
    DataNode(DataFunc *);

    ~DataNode(){

    }

    DataType Type(){ return mType; }
    bool CompatibleType();
    DataNode& Evaluate() const;

    int Int(const DataArray* a);
    int LiteralInt(const DataArray* a) const;
    Symbol Sym(const DataArray* a);
    Symbol LiteralSym(const DataArray* a) const;
    Symbol ForceSym(const DataArray* a);
    char* Str(const DataArray* a);
    char* LiteralStr(const DataArray* a) const;
    void* Glob(int* size, const DataArray* a);
    float Float(const DataArray* a);
    float LiteralFloat(const DataArray* a) const;
    DataFunc* Func(const DataArray* a) const;
    Hmx::Object* GetObj(const DataArray* a);
    DataArray* Array(const DataArray* a);
    DataArray* LiteralArray(const DataArray* a) const;
    DataArray* Command(const DataArray* a);
    DataNode* Var(const DataArray* a);

    bool operator==(const DataNode& n) const;
    bool operator!=(const DataNode& n) const;
    bool NotNull() const;
    DataNode& operator=(const DataNode& n) const;

    void Print(TextStream& s) const;
    void Save(BinStream& d) const;
    void Load(BinStream& d) const;
};

class DataArray {
public:
    DataNode* mNodes;
    Symbol mFile;
    short mSize;
    short mRefs;
    short mLine;
    short mDeprecated;
    static DataFunc* sDefaultHandler;

    int Size(){ return mSize; }

    Symbol Sym(int) const;
    // T* Obj<T>(int) const;
    int Int(int) const;
    float Float(int) const;
    Symbol ForceSym(int) const;
    DataArray* Array(int) const;
    char* Str(int) const;

    void AddRef();
    void Release();
    // void* operator new(unsigned long); make the param size_t?

    DataNode& Node(int);
    DataNode& Node(int) const;

    void Print(TextStream& s, DataType type, bool compact) const;
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
    DataArray* FindArray(Symbol s1, Symbol s2, Symbol s3, Symbol s4) const;
    DataArray* FindArray(Symbol, const char*) const;

    bool FindData(Symbol tag, const char *& ret, bool fail) const;
    bool FindData(Symbol tag, Symbol & ret, bool fail) const;
    bool FindData(Symbol tag, String & ret, bool fail) const;
    bool FindData(Symbol tag, int & ret, bool fail) const;
    bool FindData(Symbol tag, float & ret, bool fail) const;
    bool FindData(Symbol tag, bool & ret, bool fail) const;
    bool FindData(Symbol tag, Vector2 & ret, bool fail) const;
    bool FindData(Symbol tag, Vector3 & ret, bool fail) const;
    bool FindData(Symbol tag, Plane & ret, bool fail) const;
    bool FindData(Symbol tag, Hmx::Color & ret, bool fail) const;

    int FindInt(Symbol) const;
    float FindFloat(Symbol) const;
    Symbol FindSym(Symbol) const;
    char* FindStr(Symbol) const;

    DataArray* Clone(bool deep, bool eval, int);

    DataArray(int size);
    DataArray(const void* glob, int size);
    ~DataArray();

    void SetFileLine(Symbol, int);
    void SortNodes();
    DataNode Execute();
    void Save(BinStream& d) const;
    void Load(BinStream& d);
    void SaveGlob(BinStream& d, bool str) const;
    void LoadGlob(BinStream& d, bool str);
    DataNode ExecuteScript(int firstCmd, Hmx::Object* _this, const DataArray* _args, int firstArg);
    DataNode& Evaluate(int) const;
    
};

TextStream& operator<<(TextStream&, const DataArray*);
BinStream& operator>>(BinStream&, DataArray*&);
BinStream& operator<<(BinStream&, const DataArray*);

class DataArrayPtr {
public:
    DataArray* mData;
};

#endif