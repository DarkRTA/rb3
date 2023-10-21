#include "data.hpp"
#include "binstream.hpp"

// fn_801C7058
void DataNode::CreateEmptyDataNode(){
    value.intVal = 0;
    type = EMPTY;
}

// fn_801CB744
BinStream* BinStream::WriteHalfWord(short us){
    WriteEndian(&us, 2);
    return this;
}

// fn_801CCA70
BinStream* BinStream::ReadHalfWord(void* v){
    ReadEndian(v, 2);
    return this;
}