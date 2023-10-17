#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "message.hpp"
#include "jsonconverter.hpp"
#include "data.hpp"

// fn_800AFE60
// probably inline
bool UnknownJsonConverterMember::fn_800AFE60()
{
	return unk4 == 0;
}

extern void fn_800AE758(Message *, int);

// fn_800AE714
Message::Message()
{
}

// fn_800AE758
void DataArray::IncRefCount(){
	mRefCount++;
}