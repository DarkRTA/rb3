#include "data.hpp"
#include "symbol.hpp"

extern DataNode* NodesAlloc(int);

DataArray::DataArray(int i){
    symbol = &Symbol();
    mNodeCount = i;
    mRefCount = 1;
    mLine = 0;
    mUnknown = 0;
    mNodes = NodesAlloc(i << 3);
}