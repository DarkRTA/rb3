#include "data.hpp"
#include "binstream.hpp"

// fn_801C7058
DataNode::DataNode(){
    value.intVal = 0;
    type = kDataInt;
}

// fn_801CB744
BinStream& BinStream::operator<<(short s){
    WriteEndian(&s, 2);
    return *this;
}

// fn_801CCA70
BinStream& BinStream::operator>>(short& s){
    ReadEndian(&s, 2);
    return *this;
}