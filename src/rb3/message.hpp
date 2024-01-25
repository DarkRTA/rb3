#ifndef RB3_MESSAGE_HPP
#define RB3_MESSAGE_HPP
#include "data.hpp"
#include "symbol.hpp"

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

    DataArray *unk4;
    DataArray* GetArray();
};

#endif
