#include "data.hpp"
#include "hmx/object.hpp"

extern Hmx::Object* gDataThis;

Hmx::Object* DataThis(){
    return gDataThis;
}

extern DataNode* gVarStackPtr;

void DataPushVar(DataNode* dn){
    *gVarStackPtr = *dn;
    *(++gVarStackPtr) = *dn;
}