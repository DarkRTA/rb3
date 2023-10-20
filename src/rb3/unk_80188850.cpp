#include "data.hpp"
#include "binstream.hpp"

// fn_801C7058
void DataNode::CreateEmptyDataNode(){
    value.intVal = 0;
    type = EMPTY;
}

// fn_801CCA70
BinStream* BinStream::ReadHalfWord(void* v){
    ReadEndian(v, 2);
    return this;
}