#include "jsonobject.hpp"
#include "common.hpp"
#include "data.hpp"

// fn_800CF370
int Minimum(int x, int y)
{
	return (y < x) ? y : x;
}

// fn_800D7964
float DataArray::GetFloatAtIndex(int i) const {
	DataNode* dn = GetNodeAtIndex(i);
    return dn->Float(this);
}