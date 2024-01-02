#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "message.hpp"
#include "jsonconverter.hpp"
#include "data.hpp"
#include "joinresultmsg.hpp"
#include "hmx/object.hpp"
#include "makestring.hpp"
#include "user.hpp"

// fn_800AFE60
// probably inline
bool UnknownJsonConverterMember::fn_800AFE60() {
    return unk4 == 0;
}

// fn_800AE6D8
JoinResultMsg::JoinResultMsg(DataArray *da) : Message(da) {
}

extern void fn_800AE758(Message *, int);

// fn_800AE714
Message::Message(DataArray *da) {
    unk4 = da;
    unk4->IncRefCount();
}

// fn_800AE758
void DataArray::IncRefCount() {
    mRefCount++;
}

// fn_800B27F0
DataArray *DataArray::GetArrayAtIndex(int i) const {
    DataNode *dn = GetNodeAtIndex(i);
    return dn->Array(this);
}

// fn_800B30B8
DataNode::DataNode(float f) {
    value.floatVal = f;
    type = kDataFloat;
}

// fn_800AFF98
DataNode::DataNode(Hmx::Object *obj) {
    value.objVal = obj;
    type = kDataObject;
}

// fn_800B441C
const char *MakeString(const char *c) {
    FormatString fs(c);
    return fs.Str();
}

// fn_800AE0BC
int DataArray::FindInt(Symbol s) const {
    return FindArray(s, true)->GetIntAtIndex(1);
}

User* GetUserAtIndex(DataArray* da, int idx){
    return GetUser(da->GetNodeAtIndex(idx), da);
}

User* GetUser(DataNode* node, DataArray* arr){
    return dynamic_cast<User*>(node->GetObj(arr));
}
