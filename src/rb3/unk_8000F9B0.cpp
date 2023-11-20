#include "data.hpp"
#include "symbol.hpp"

// fn_8000FDA0
int DataArray::GetNodeCount() const
{
	return mNodeCount;
}

// fn_80010140
Symbol DataArray::GetSymAtIndex(int i) const {
	DataNode* dn = GetNodeAtIndex(i);
	return dn->Sym(this);
}

extern char* gNullStr;
// fn_800103CC
bool Symbol::IsNull(){
	return m_string == gNullStr;
}