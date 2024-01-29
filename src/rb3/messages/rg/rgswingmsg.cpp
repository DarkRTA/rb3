#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_8031454C
RGSwingMsg::RGSwingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}