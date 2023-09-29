#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"

// fn_800A6E18
// probably inline
unsigned int String::GetTextLength()
{
	return strlen(text);
}