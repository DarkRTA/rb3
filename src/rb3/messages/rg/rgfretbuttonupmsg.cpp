#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_8031471C
RGFretButtonUpMsg::RGFretButtonUpMsg(int i1, int i2, int i3)
    : Message(Type(), DataNode(i1), DataNode(i2), DataNode(i3)) {
}