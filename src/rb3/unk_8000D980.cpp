#include "string.hpp"
#include "textstream.hpp"
#include "filepath.hpp"
#include "objref.hpp"
#include "unknown.hpp"

// fn_8000DB9C
// this could possibly be an inlining from a header file
const char *String::c_str() const
{
	return text;
}

// fn_8000DD10
// this could also possibly be an inline
TextStream::~TextStream()
{
}

// fn_8000EC00
FilePath::FilePath(const String& str) : String(str) {

}

extern String lbl_8097BB0C;

// fn_8000EC5C
FilePath::FilePath(const char* str){
	fn_8034C91C(lbl_8097BB0C.c_str(), str);
}

// fn_8000EA28
FilePath::~FilePath(){

}

// fn_8000ED3C
ObjRef::ObjRef(){

}

// fn_8000DD10 - could possibly be an inline
// ObjRef::~ObjRef(){

// }