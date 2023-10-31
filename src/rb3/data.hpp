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

enum DataTypes { /* differs from serialized, for... some reason */
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
	DataNode(int); // fn_8000E128?
	DataNode(const DataNode &);
	DataNode(const char *); // fn_803231CC
	DataNode(const String &); // fn_8032324C
	DataNode(Symbol); // fn_8000E114
	DataNode(const void *, int);
	DataNode(DataArray *, DataTypes); // fn_80323318
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

	DataTypes GetType(); // same code as JsonObject::GetJsonObjectStruct()
	void AssignValue(
		const DataNode &); // same code as Symbol::operator=(const Symbol&)

	DataNodeValue value;
	DataTypes type;
};

class DataArray {
public:
	DataArray(int);
	DataArray(const void *, int);
	~DataArray();

	int Size() const;
	void Int(int) const;
	void Insert(int, const DataNode &);
	void InsertNodes(int, const DataArray &);
	void Resize(int);
	void Remove(int);
	void Remove(const DataNode &);
	bool Contains(const DataNode &);
	void SortNodes(); // fn_80316E84
	void SaveGlob(BinStream &, bool) const; // fn_80317B18
	void LoadGlob(BinStream &, bool); // fn_80317B9C

	void IncRefCount(); // fn_800AE758
	void DecRefCount(); // fn_8000DFC4
	int GetNodeCount(); // fn_8000FDA0
	DataNode *GetNodeAtIndex(int); // fn_8000DF50

	static DataArray *fn_8035CF9C(int, int, int);

	DataNode *mNodes;
	Symbol symbol;
	short mNodeCount;
	short mRefCount;
	short mLine;
	short mUnknown;
};

#endif
