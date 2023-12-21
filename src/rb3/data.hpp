#ifndef RB3_DATA_HPP
#define RB3_DATA_HPP
#include "symbol.hpp"
#include "string.hpp"
#include "binstream.hpp"
#include "textstream.hpp"
#include "hmx/object.hpp"

class DataArray; // forward declaration
class DataNode; // also a forward declaration
class DataArrayPtr; // yet another forward declaration

typedef DataNode DataFunc(DataArray *);

union DataNodeValue {
	int intVal;
	float floatVal;
	DataArray *dataArray;
	Hmx::Object* objVal;
	Symbol* symVal;
	char *strVal;
	DataNode* varVal;
    DataFunc* funcVal;
};

enum DataType { /* differs from serialized, for... some reason; i trusted ghidra more that i probably should've, just FYI */
	kDataUnhandled = 0,
	kDataFloat = 1,
	kDataVariable = 2,
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
	DataNode(); // fn_801C7058
	DataNode(int); // fn_8000E128
	DataNode(float); // fn_800B30B8
	DataNode(const DataNode &); // fn_80323178
	DataNode(Hmx::Object*); // fn_800AFF98
	DataNode(const char *); // fn_803231CC
	DataNode(const String &); // fn_8032324C
	DataNode(const DataArrayPtr&);
	DataNode(Symbol); // fn_8000E114
	DataNode(const void *, int);
	DataNode(DataArray *, DataType); // fn_80323318
	DataNode(DataType, DataNodeValue); // fn_800AB8A8
	DataNode(DataFunc*); // fn_803170FC
	~DataNode(); // fn_8000DFE4
	DataNode *Evaluate() const;
	DataNode* AddToBuffer();
	int Int(const DataArray *) const; // fn_80322F28
	int LiteralInt(const DataArray *) const; // fn_80322F4C
	Symbol Sym(const DataArray *) const; // fn_80322F54
	Symbol LiteralSym(const DataArray *) const; // fn_80322F78
	Symbol ForceSym(const DataArray *) const; // fn_80322F80
	const char *Str(const DataArray *) const; // fn_80322FC8
	const char *LiteralStr(const DataArray *) const; // fn_80323004
	float Float(const DataArray *) const; // fn_80323024
	float LiteralFloat(const DataArray *) const; // fn_8032307C
	DataArray *Array(const DataArray *) const; // fn_8032313C
	DataArray *LiteralArray(const DataArray *) const; // fn_80323160
	DataNode* Var(const DataArray*) const; // fn_80323170
	Hmx::Object* GetObj(const DataArray*) const;
	DataFunc* Func(const DataArray*) const; // fn_803230C0
	bool operator==(const DataNode &) const; // fn_80323360
	bool operator!=(const DataNode &) const; // fn_80323508
	bool NotNull() const; // fn_80323530
	DataNode *operator=(const DataNode &); // fn_803235D4
	void Print(TextStream &, bool) const; // fn_8032364C
	void Save(BinStream &) const; // fn_80323A18
	void Load(BinStream &); // fn_80323B64

	DataType GetType() const; // same asm as JsonObject::GetJsonObjectStruct()
	void AssignValue(
		const DataNode &); // same asm as Symbol::operator=(const Symbol&)
	DataNodeValue GetDataNodeVal() const; // fn_80018808

	DataNodeValue value;
	DataType type;
};

class DataArray {
public:
	DataArray(int);
	DataArray(const void *, int);
	~DataArray();

	int Size() const;
	void Int(int) const;
	void Insert(int, const DataNode &); // fn_80315CFC
	void InsertNodes(int, const DataArray *); // fn_80315E1C
	void Resize(int); // fn_80315F74
	void Remove(int); // fn_80316064
	void Remove(const DataNode &); // fn_80316150
	bool Contains(const DataNode &) const; // fn_80316190
	void SortNodes(); // fn_80316E84
	void Save(BinStream &) const; // fn_803171F8
	void Load(BinStream &);
	void SaveGlob(BinStream &, bool) const; // fn_80317B18
	void LoadGlob(BinStream &, bool); // fn_80317B9C
	DataArray* Clone(bool, bool, int); // fn_803169C4

	DataNode Execute();
	DataNode ExecuteScript(int, Hmx::Object*, const DataArray*, int);

	void IncRefCount(); // fn_800AE758
	void DecRefCount(); // fn_8000DFC4
	int GetNodeCount() const; // fn_8000FDA0
	DataNode *GetNodeAtIndex(int) const; // fn_8000DF50
	int GetIntAtIndex(int) const; // fn_800A8410
	float GetFloatAtIndex(int) const; // fn_800D7964
	DataNodeValue GetDataNodeValueAtIndex(int) const; // fn_80316258
	Symbol GetSymAtIndex(int) const; // fn_80010140
	const char *GetStrAtIndex(int) const; // fn_8000ECC0
	DataArray *GetArrayAtIndex(int) const; // fn_800B27F0
	DataNode* GetVarAtIndex(int) const; // fn_800E7878
	DataType GetTypeAtIndex(int) const; // fn_80117BAC
	DataArray* GetCommandAtIndex(int) const;
	Hmx::Object* GetObjAtIndex(int) const;
	Symbol ForceSymAtIndex(int) const; // fn_80119134
	void Print(TextStream &, DataType, bool) const; // fn_80315A70
	void SetFileLine(Symbol, int); // fn_80316CB0

	int GetLine(); // fn_801FBAFC
	char* GetSymbol(); // same asm as DataNode::GetType
	DataNode RunCommandsFromIndex(int); // fn_80317C7C

	DataArray* FindArray(int, bool) const; // fn_803161D4
	DataArray* FindArray(Symbol, bool) const; // fn_8031627C
	DataArray* FindArray(Symbol, Symbol) const; // fn_803162BC
	DataArray* FindArray(Symbol, Symbol, Symbol) const; // fn_80316300
	DataArray* FindArray(Symbol, const char*) const; // fn_80316358

	int FindArrayAndGetInt(Symbol) const; // fn_800AE0BC
	float FindArrayAndGetFloat(Symbol) const; // fn_800D792C
	
	bool FindData(Symbol, const char*&, bool) const; // fn_803163B8
	bool FindData(Symbol, Symbol&, bool) const; // fn_80316414
	bool FindData(Symbol, String&, bool) const; // fn_8031647C
	bool FindData(Symbol, int&, bool) const; // fn_803164D8
	bool FindData(Symbol, float&, bool) const; // fn_80316534
	bool FindData(Symbol, bool&, bool) const; // fn_80316590

	DataNode *mNodes;
	Symbol symbol;
	short mNodeCount;
	short mRefCount;
	short mLine;
	short mUnknown;
};

class DataArrayPtr {
public:
	DataArray* arr;
};

#endif
