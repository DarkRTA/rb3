#ifndef RB3_MESSAGE_HPP
#define RB3_MESSAGE_HPP
#include "data.hpp"
#include "symbol.hpp"

class Message {
public:
	Message(); // fn_8000FFE0
	Message(Symbol*, DataNode*, DataNode*); // fn_8000E048
	Message(DataArray*); // fn_800AE714
	virtual ~Message(); // fn_8000DF60
	virtual void Unk1() = 0;

	DataArray* unk4;
};

#endif
