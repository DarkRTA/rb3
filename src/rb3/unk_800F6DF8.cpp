#include "unknown.hpp"
#include "data.hpp"
#include "symbol.hpp"

// fn_80119C38
unsigned short SwapDataHalfWord(unsigned short s)
{
	unsigned short us = s;
	return us << 8 | us >> 8;
}

// fn_80119134
Symbol DataArray::ForceSymAtIndex(int i) const {
	DataNode* dn = GetNodeAtIndex(i);
	return dn->ForceSym(this);
}