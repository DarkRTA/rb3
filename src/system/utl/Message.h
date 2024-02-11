#ifndef UTL_MESSAGE_H
#define UTL_MESSAGE_H
#include "Data.h"
#include "Symbol.h"
#include <new>

// every method in here is weak
class Message {
public:
    Message(); // fn_8000FFE0

    Message(Symbol type){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(2);
        mData->Node(1) = DataNode(type);
    }

    Message(Symbol type, const DataNode & arg1){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(3);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(4);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
    }
    
    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(5);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
    }
            
    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(6);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
    }
    
    Message(DataArray* da) : mData(da) { da->AddRef(); }
    
    virtual ~Message(){ mData->Release(); }

    DataArray* mData;
    DataArray* GetArray(){ return mData; }
};

#endif
