#include "data.hpp"
#include "symbol.hpp"
#include "std/string.h"
#include "std/stdlib.h"

extern DataNode* NodesAlloc(int);

DataArray::DataArray(int i) : symbol(), mNodeCount(i), mRefCount(1), mLine(0), mUnknown(0) {
    mNodes = NodesAlloc(i * sizeof(DataNode));
    for(int n = 0; n < i; n++){
        DataNode* dn = &mNodes[n];
        if(dn != nullptr) dn->CreateEmptyDataNode();
    }
}

DataArray::DataArray(const void* v, int i) : symbol(), mNodeCount(-i), mRefCount(1), mLine(0), mUnknown(0) {
    mNodes = NodesAlloc(i);
    memcpy(mNodes, v, i);
}

extern void NodesFree(int, DataNode*);

DataArray::~DataArray(){
    if(mNodeCount < 0) NodesFree(-mNodeCount, mNodes);
    else {
        for(int i = 0; i < mNodeCount; i++){
            delete &mNodes[i];
        }
        NodesFree(mNodeCount * sizeof(DataNode), mNodes);
    }
}

int NodeCmp(const void* a, const void* b){
    DataNode* da = (DataNode*)a;
    DataNode* db = (DataNode*)b;
    switch(da->GetType()){
        case FLOAT_VALUE: 
        case EMPTY:
            double d1 = da->LiteralFloat(nullptr);
            double d2 = db->LiteralFloat(nullptr);
            if(d1 < d2) return -1;
            return (d1 != d2);
        case STRING_VALUE:
        case SYMBOL:
            const char* s1 = da->Str(nullptr);
            const char* s2 = db->Str(nullptr);
            return stricmp(s1, s2);
        default:
            return 0;
    }
}

void DataArray::SortNodes(){
    if(mNodeCount <= 0) return;
    qsort(mNodes, mNodeCount, 8, NodeCmp);
}

// fn_80317B18
void DataArray::SaveGlob(BinStream& bs, bool b) const {
    if(b){
        int i = -1 - mNodeCount;
        bs.WriteWord(i);
        bs.Write(mNodes, i);
    }
    else {
        bs.WriteHalfWord(mNodeCount);
        bs.Write(mNodes, -mNodeCount);
    }
}

// fn_80317B9C
void DataArray::LoadGlob(BinStream& bs, bool b){
    int v;
    NodesFree(-mNodeCount, mNodes);
    if(b){
        bs.ReadWord(&v);
        mNodeCount = -(v + 1);
        mNodes = NodesAlloc(-mNodeCount);
        bs.Read(mNodes, v);
    }
    else {
        bs.ReadHalfWord(&mNodeCount);
        mNodes = NodesAlloc(-mNodeCount);
        bs.Read(mNodes, -mNodeCount);
    }
}