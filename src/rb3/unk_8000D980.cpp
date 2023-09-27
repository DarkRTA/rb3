#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"

// fn_8000DB9C
// this could possibly be an inlining from a header file
const char* String::GetText() const {
    return text;
}

// fn_8000DD10
// this could also possibly be an inline
TextStream::~TextStream() { }