#include "data.hpp"
#include "symbol.hpp"
#include "stringstrummedmsg.hpp"

// fn_80313E98
StringStrummedMsg::StringStrummedMsg(int i1, int i2, int i3, int i4)
    : Message(
        Type(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)
    ) {
}

// fn_80313F64
Symbol StringStrummedMsg::Type() {
    static Symbol t("string_strummed");
    return t;
}