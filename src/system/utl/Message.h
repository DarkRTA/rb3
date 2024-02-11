#ifndef UTL_MESSAGE_H
#define UTL_MESSAGE_H
#include "Data.h"
#include "Symbol.h"

// every method in here is weak
class Message {
public:
    Message(); // fn_8000FFE0
    Message(Symbol, const DataNode &, const DataNode &); // fn_8000E048
    Message(Symbol, const DataNode &, const DataNode &,
            const DataNode &); // fn_800B7D98
    Message(
		Symbol, const DataNode &, const DataNode &, const DataNode &,
		const DataNode &); // fn_80177AD4
    Message(Symbol, const DataNode &); // fn_8001008C
    Message(Symbol); // fn_8000FFE0
    Message(DataArray *); // fn_800AE714
    virtual ~Message(); // fn_8000DF60

    DataArray* mData;
    DataArray* GetArray(){ return mData; }
};

#endif
