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

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(7);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5, const DataNode & arg6){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(8);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
        mData->Node(7) = arg6;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5, const DataNode & arg6, const DataNode & arg7){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(9);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
        mData->Node(7) = arg6;
        mData->Node(8) = arg7;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5, const DataNode & arg6, const DataNode & arg7, const DataNode & arg8){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(10);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
        mData->Node(7) = arg6;
        mData->Node(8) = arg7;
        mData->Node(9) = arg8;
    }

    Message(Symbol type, const DataNode & arg1, const DataNode & arg2, const DataNode & arg3, const DataNode & arg4, const DataNode & arg5, const DataNode & arg6, const DataNode & arg7, const DataNode & arg8, const DataNode & arg9){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(11);
        mData->Node(1) = DataNode(type);
        mData->Node(2) = arg1;
        mData->Node(3) = arg2;
        mData->Node(4) = arg3;
        mData->Node(5) = arg4;
        mData->Node(6) = arg5;
        mData->Node(7) = arg6;
        mData->Node(8) = arg7;
        mData->Node(9) = arg8;
        mData->Node(10) = arg9;
    }
    
    Message(DataArray* da) : mData(da) { da->AddRef(); }

    Message(int i){
        mData = new (_PoolAlloc(0x10, 0x10, FastPool)) DataArray(i + 2);
    }
    
    virtual ~Message(){ mData->Release(); }

    DataArray* mData;
    DataArray* GetArray(){ return mData; }
};

#endif
