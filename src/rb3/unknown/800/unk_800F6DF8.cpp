#include "unknown.hpp"
#include "common.hpp"
#include "data.hpp"
#include "symbol.hpp"

// fn_80119C38
unsigned short SwapDataHalfWord(unsigned short s) {
    unsigned short us = s;
    return us << 8 | us >> 8;
}

// fn_80119134
Symbol DataArray::ForceSymAtIndex(int i) const {
    DataNode *dn = GetNodeAtIndex(i);
    return dn->ForceSym(this);
}

// fn_80107B50
int CountBits(int num) {
    int temp_r0;
    int var_r3;
    int var_r4;

    var_r3 = num;
    var_r4 = 0;
    while (var_r3 != 0) {
        temp_r0 = var_r3 & 1;
        var_r3 = (int)((unsigned int)var_r3 >> 1U);
        var_r4 += temp_r0;
    }
    return var_r4;
}

// fn_80117BAC
DataType DataArray::GetTypeAtIndex(int i) const {
    DataNode *dn = GetNodeAtIndex(i);
    return dn->GetType();
}