#include "data.hpp"
#include "hmx/object.hpp"
#include "varstack.hpp"

extern Hmx::Object* gDataThis;

Hmx::Object* DataThis(){
    return gDataThis;
}

extern VarStack* gVarStackPtr;

void DataPushVar(DataNode* dn){
    gVarStackPtr++;
    gVarStackPtr->ptr = dn;
    gVarStackPtr->node = *dn;
}

void DataPopVar(){
    *gVarStackPtr->ptr = gVarStackPtr->node;
    gVarStackPtr->node = DataNode(0);
    gVarStackPtr--;
}