#include "messages/stringstrummedmsg.hpp"
#include "obj/Data.h"

// fn_80313E98
StringStrummedMsg::StringStrummedMsg(int i1, int i2, int i3, int i4)
    : Message(
        Type(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)
    ) {
}
