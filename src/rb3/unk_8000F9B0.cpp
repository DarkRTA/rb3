#include "data.hpp"
#include "common.hpp"
#include "symbol.hpp"
#include "message.hpp"

// fn_8000FDA0
int DataArray::GetNodeCount() const
{
	return mNodeCount;
}

// fn_80010140
const char* DataArray::GetSymAtIndex(int i) const {
	DataNode* dn = GetNodeAtIndex(i);
	return dn->Sym(this);
}

extern char* gNullStr;
// fn_800103CC
bool Symbol::IsNull(){
	return m_string == gNullStr;
}

extern DataArray *fn_8035CF9C(int, int, int);
// fn_8000E048
Message::Message(Symbol s)
{
	DataArray* da = new (fn_8035CF9C(0x10, 0x10, 1)) DataArray(2);
	unk4 = da;

	unk4->GetNodeAtIndex(1)->operator=(DataNode(s));
}

// fn_8001008C
Message::Message(Symbol s, const DataNode& dn){
	DataArray* da = new (fn_8035CF9C(0x10, 0x10, 1)) DataArray(3);
	unk4 = da;

	unk4->GetNodeAtIndex(1)->operator=(DataNode(s));
	unk4->GetNodeAtIndex(2)->operator=(dn);
}

// fn_8000FCA4
bool Symbol::operator==(const Symbol& sym){
	return m_string == sym.m_string;
}