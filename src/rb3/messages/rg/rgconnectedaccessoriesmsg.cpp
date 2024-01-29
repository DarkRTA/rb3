#include "data.hpp"
#include "symbol.hpp"
#include "rg_messages.hpp"

// fn_80314114
RGConnectedAccessoriesMsg::RGConnectedAccessoriesMsg(int i1, int i2)
    : Message(Type(), DataNode(i1), DataNode(i2)) {
}