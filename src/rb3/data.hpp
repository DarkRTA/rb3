#ifndef RB3_DATA_HPP
#define RB3_DATA_HPP
#include "symbol.hpp"
#include "string.hpp"
#include "binstream.hpp"
#include "textstream.hpp"

class DataArray; // forward declaration

union DataNodeValue {
	int intVal;
	float floatVal;
	DataArray *dataArray;
	int *object; // should be Object?
	Symbol *symVal;
	char *strVal;
};

enum DataType { /* differs from serialized, for... some reason; i trusted ghidra more that i probably should've, just FYI */
	kDataUnhandled = 0,
	kDataFloat = 1,
	kDataVariable = 2,
	kDataSymbol = 3,
	kDataFunc = 4,
	kDataObject = 5,
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
	DataNode(const DataNode&); // fn_80323178
	DataNode(const char*); // fn_803231CC
	DataNode(const String&); // fn_8032324C
	DataNode(Symbol); // fn_8000E114
	DataNode(const void *, int);
	DataNode(DataArray *, DataType); // fn_80323318
	~DataNode(); // fn_8000DFE4
	DataNode *Evaluate() const;
	int Int(const DataArray *) const; // fn_80322F28
	int LiteralInt(const DataArray *) const; // fn_80322F4C
	Symbol *Sym(const DataArray *) const; // fn_80322F54
	Symbol *LiteralSym(const DataArray *) const; // fn_80322F78
	Symbol *ForceSym(const DataArray *) const; // fn_80322F80
	const char *Str(const DataArray *) const; // fn_80322FC8
	const char *LiteralStr(const DataArray *) const; // fn_80323004
	float Float(const DataArray *) const; // fn_80323024
	float LiteralFloat(const DataArray *) const; // fn_8032307C
	DataArray *Array(const DataArray *) const; // fn_8032313C
	DataArray *LiteralArray(const DataArray *) const; // fn_80323160
	bool operator==(const DataNode &) const; // fn_80323360
	bool operator!=(const DataNode &) const; // fn_80323508
	bool NotNull() const; // fn_80323530
	DataNode *operator=(const DataNode &); // fn_803235D4
	void Print(TextStream &, bool) const; // fn_8032364C
	void Save(BinStream&) const; // fn_80323A18
	void Load(BinStream&); // fn_80323B64

	DataType GetType(); // same asm as JsonObject::GetJsonObjectStruct()
	void AssignValue(
		const DataNode &); // same asm as Symbol::operator=(const Symbol&)

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
	void InsertNodes(int, const DataArray*); // fn_80315E1C
	void Resize(int); // fn_80315F74
	void Remove(int); // fn_80316064
	void Remove(const DataNode &); // fn_80316150
	bool Contains(const DataNode &) const; // fn_80316190
	void SortNodes(); // fn_80316E84
	void Save(BinStream&) const; // fn_803171F8
	void Load(BinStream&);
	void SaveGlob(BinStream &, bool) const; // fn_80317B18
	void LoadGlob(BinStream &, bool); // fn_80317B9C

	void IncRefCount(); // fn_800AE758
	void DecRefCount(); // fn_8000DFC4
	int GetNodeCount() const; // fn_8000FDA0
	DataNode* GetNodeAtIndex(int) const; // fn_8000DF50
	const char* GetStrAtIndex(int); // fn_8000ECC0
	void Print(TextStream&, DataType, bool) const; // fn_80315A70
	void SetFileLine(Symbol, int); // fn_80316CB0

	DataNode *mNodes;
	Symbol symbol;
	short mNodeCount;
	short mRefCount;
	short mLine;
	short mUnknown;
};

#endif
