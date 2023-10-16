#ifndef RB3_DATA_HPP
#define RB3_DATA_HPP
#include "symbol.hpp"
#include "string.hpp"

enum DataType {
	Int, Float, Variable, Func, Object, SymbolDtaType, Unhandled, IfDef, Else, EndIf,
	Array = 0x10,
	Command, StringDtaType, Property, Glob,
	Define = 0x20,
	Include, Merge, IfNDef, Autorun, Undef
};

class DataArray; // forward declaration

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

	DataArray* arr;
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

	DataNode* node;
	Symbol* symbol;
	short size;
	short unka;
	short unkc;
	short unke;
};

#endif
