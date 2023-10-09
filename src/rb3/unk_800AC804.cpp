#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "message.hpp"

// fn_800AFE60
// probably inline
bool String::IsTextLengthZero()
{
	return len == 0;
}

extern void fn_800AE758(Message *, int);

// fn_800AE714
Message::Message()
{
}