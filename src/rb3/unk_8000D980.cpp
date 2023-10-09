#include "string.hpp"
#include "textstream.hpp"
#include "filepath.hpp"
#include "objref.hpp"
#include "unknown.hpp"
#include "symbol.hpp"
#include "message.hpp"
#include "matchmakingsettings.hpp"

// fn_8000DB9C
// this could possibly be an inlining from a header file
const char *String::c_str() const
{
	return text;
}

// fn_8000DD10
// generic dtor function

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

// fn_8000DCA8
Symbol* Symbol::operator=(const Symbol& s){
	m_string = s.m_string;
	return this;
}

// fn_8000EC3C
bool String::empty() const {
	return (*text == '\0');
}

// fn_8000DF60
Message::~Message(){
	
}

// fn_8000DF3C
Symbol MatchmakingSettings::GetSymbol() const {
	return unk4;
} 