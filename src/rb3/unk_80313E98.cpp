#include "data.hpp"
#include "symbol.hpp"

extern DataNode* NodesAlloc(int);

DataArray::DataArray(int i) : symbol(), mNodeCount(i), mRefCount(1), mLine(0), mUnknown(0) {
    mNodes = NodesAlloc(i * sizeof(DataNode));
    for(int n = 0; n < i; n++){
        DataNode* dn = &mNodes[n];
        if(dn != nullptr) dn->CreateEmptyDataNode();
    }
}