#include "data.hpp"
#include "symbol.hpp"

extern DataNode* NodesAlloc(int);

DataArray::DataArray(int i){
    mNodeCount = i;
    mRefCount = 1;
    mLine = 0;
    mUnknown = 0;
    // nodes = NodesAlloc(i << 3);
}