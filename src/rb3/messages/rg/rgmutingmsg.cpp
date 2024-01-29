#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_803142C4
RGMutingMsg::RGMutingMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}