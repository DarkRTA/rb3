#ifndef RB3_DATA_HPP
#define RB3_DATA_HPP
#include "symbol.hpp"
#include "string.hpp"
#include "textstream.hpp"

class DataArray; // forward declaration

union DataNodeValue {
    int intVal;
    float floatVal;
    DataArray *dataArray;
    int *object; // should be Object?
	Symbol* symVal;
    char *strVal;
};

enum DataType {
	INT_VALUE = 0,
    FLOAT_VALUE = 1,
    VAR = 2,
    FUNC = 3,
    OBJECT = 4,
    SYMBOL = 5,
    EMPTY = 6,
    IFDEF = 7,
    ELSE = 8,
    ENDIF = 9,
    ARRAY = 16,
    COMMAND = 17,
    STRING_VALUE = 18,
    OBJECT_PROP_REF = 19,
    GLOB = 20,
    DEFINE = 32,
    INCLUDE = 33,
    MERGE = 34,
    IFNDEF = 35,
    AUTORUN = 36,
    UNDEF = 37
};

class DataNode {
public:
	DataNode();
	DataNode(int);
	DataNode(const DataNode&);
	DataNode(const char*); // fn_803231CC
	DataNode(const String&); // fn_8032324C
	DataNode(const void*, int);
	DataNode(DataArray*, DataType); // fn_80323318
	~DataNode();
	DataNode* Evaluate() const;
	int Int(const DataArray*) const; // fn_80322F28
	int LiteralInt(const DataArray*) const; // fn_80322F4C
	Symbol* Sym(const DataArray*) const; // fn_80322F54
	Symbol* LiteralSym(const DataArray*) const; // fn_80322F78
	Symbol* ForceSym(const DataArray*) const; // fn_80322F80
	const char* Str(const DataArray*) const; // fn_80322FC8
	const char* LiteralStr(const DataArray*) const; // fn_80323004
	float Float(const DataArray*) const; // fn_80323024
	float LiteralFloat(const DataArray*) const; // fn_8032307C
	DataArray* Array(const DataArray*) const; // fn_8032313C
	DataArray* LiteralArray(const DataArray*) const; // fn_80323160
	bool operator==(const DataNode&) const; // fn_80323360
	bool operator!=(const DataNode&) const; // fn_80323508
	DataNode* operator=(const DataNode&); // fn_803235D4
	void Print(TextStream&, bool) const; // fn_8032364C

	DataNodeValue value;
	DataType type;
};

class DataArray {
public:
	DataArray(int);
	DataArray(const void*, int);
	~DataArray();

	int Size() const;
	void Int(int) const;
	void Insert(int, const DataNode&);
	void InsertNodes(int, const DataArray&);
	void Resize(int);
	void Remove(int);
	void Remove(const DataNode&);
	bool Contains(const DataNode&);

	void IncRefCount(); // fn_800AE758
	void DecRefCount(); // fn_8000DFC4

	DataNode* mNodes;
	Symbol* symbol;
	short mNodeCount;
	short mRefCount;
	short mLine;
	short mUnknown;
};

#endif
