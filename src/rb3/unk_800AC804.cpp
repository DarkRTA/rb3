#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"

// fn_800AFE60
// probably inline
bool String::IsTextLengthZero(){
    return len == 0;
}