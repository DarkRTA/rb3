#include <string.h>

#include "obj/Data.h"
#include "obj/Object.h"
#include "os/User.h"
#include "utl/MakeString.h"
#include "utl/Message.h"
#include "utl/Str.h"
#include "utl/TextStream.h"

#include "unknown.hpp"
#include "joinresultmsg.hpp"
#include "jsonobjects.hpp"

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

// fn_800B441C
const char *MakeString(const char *c) {
    FormatString fs(c);
    return fs.Str();
}


User* GetUserAtIndex(DataArray* da, int idx){
    return GetUser(da->GetNodeAtIndex(idx), da);
}

User* GetUser(DataNode* node, DataArray* arr){
    return dynamic_cast<User*>(node->GetObj(arr));
}
