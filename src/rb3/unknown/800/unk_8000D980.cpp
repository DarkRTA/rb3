#include "string.hpp"
#include "textstream.hpp"
#include "filepath.hpp"
#include "objref.hpp"
#include "unknown.hpp"
#include "symbol.hpp"
#include "message.hpp"
#include "matchmakingsettings.hpp"
#include "jsonobjects.hpp"


// fn_8000DB9C
// this could possibly be an inlining from a header file
const char *String::c_str() const {
    return text;
}

// fn_8000DD10
// generic dtor function

extern DataArray *fn_8035CF9C(int, int, int);
extern "C" DataNode *fn_8000DF50(DataArray *, int);

// fn_8000E048
Message::Message(Symbol s, const DataNode &dn1, const DataNode &dn2) {
    DataArray *da = fn_8035CF9C(0x10, 0x10, 1);
    if (da != 0)
        da = new DataArray(4);
    unk4 = da;

    unk4->GetNodeAtIndex(1)->operator=(DataNode(s));
    unk4->GetNodeAtIndex(2)->operator=(dn1);
    unk4->GetNodeAtIndex(3)->operator=(dn2);
}

// fn_8000EC00
FilePath::FilePath(const String &str) : String(str) {
}

extern String lbl_8097BB0C;

// fn_8000EC5C
FilePath::FilePath(const char *str) {
    Set(lbl_8097BB0C.c_str(), str);
}

// fn_8000EA28
FilePath::~FilePath() {
}

// fn_8000ED3C
ObjRef::ObjRef() {
}

// fn_8000DD10 - could possibly be an inline
// ObjRef::~ObjRef(){

// }

// fn_8000DCA8
Symbol *Symbol::operator=(const Symbol &s) {
    m_string = s.m_string;
    return this;
}

// fn_8000EC3C
bool String::empty() const {
    return (*text == '\0');
}

// fn_8000DF60
Message::~Message() {
    unk4->DecRefCount();
}

// // fn_8000DF3C
// Symbol MatchmakingSettings::GetSymbol() const
// {
// 	return unk4;
// }

// fn_8000DF3C
json_object *JsonObject::GetJsonObjectStruct() {
    return json_object_struct;
}
