#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"

// fn_800A6E18
// probably inline
unsigned int String::length()
{
	return strlen(text);
}

// // fn_800A6BD0
// // also probably inline
// unsigned short String::GetTextLengthWithoutStrLen(){
// 	return len;
// }