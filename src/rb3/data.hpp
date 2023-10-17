#ifndef RB3_DATA_HPP
#define RB3_DATA_HPP
#include "symbol.hpp"
#include "string.hpp"

class DataArray; // forward declaration

union DataNodeValue {
    int intVal;
    float floatVal;
    DataArray *dataArray;
    int *object; // should be Object?
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
	DataNode(DataArray*, DataType);
	~DataNode();
	DataNode* Evaluate() const;
	DataNode* ForceSym(const DataArray*) const; // fn_80322F80
	DataNode* LiteralStr(const DataArray*) const; // fn_80323004
	double Float(const DataArray*) const; // fn_80323024
	bool operator==(const DataNode&) const; // fn_80323360

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

	DataNode* nodes;
	Symbol* symbol;
	short mNodeCount;
	short mRefCount;
	short mLine;
	short mUnknown;
};

#endif
