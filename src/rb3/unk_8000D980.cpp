#include "string.hpp"
#include "textstream.hpp"
#include "filepath.hpp"
#include "objref.hpp"
#include "unknown.hpp"
#include "symbol.hpp"
#include "message.hpp"
#include "matchmakingsettings.hpp"
#include "jsonobject.hpp"
#include "data.hpp"

// fn_8000DB9C
// this could possibly be an inlining from a header file
const char *String::c_str() const
{
	return text;
}

// fn_8000DD10
// generic dtor function

// fn_8000DFE4
DataNode::~DataNode(){
	if((type & 0x10) != 0){
		value.dataArray->DecRefCount();
	}
}

extern DataArray* fn_8035CF9C(int, int, int);
extern "C" DataNode* fn_8000DF50(DataArray*, int);

// fn_8000DF50
DataNode* DataArray::GetNodeAtIndex(int i){
	return &mNodes[i];
}

// fn_8000E048
Message::Message(Symbol* s, DataNode* dn2, DataNode* dn3){
	DataArray* da = fn_8035CF9C(0x10, 0x10, 1);
	if(da != 0) da = new DataArray(4);
	unk4 = da;
}

// fn_8000E114
DataNode::DataNode(Symbol s){
	type = kDataSymbol;
	value.strVal = s.m_string;
}

// fn_8000EC00
FilePath::FilePath(const String &str) : String(str)
{
}

extern String* lbl_8097BB0C;

// fn_8000EC5C
FilePath::FilePath(const char *str)
{
	Set(lbl_8097BB0C->c_str(), str);
}

// fn_8000EA28
FilePath::~FilePath()
{
}

extern "C" const char* fn_8000ECC0(DataArray*);
extern DataNode* fn_8000DF50();

// fn_8000ECC0
const char* fn_8000ECC0(DataArray* da){ // what's R4? there's an extra argument
	DataNode* dn = fn_8000DF50();
	return dn->Str(da);
}

// fn_8000ED3C
ObjRef::ObjRef()
{
}

// fn_8000DD10 - could possibly be an inline
// ObjRef::~ObjRef(){

// }

// fn_8000DCA8
Symbol *Symbol::operator=(const Symbol &s)
{
	m_string = s.m_string;
	return this;
}

// fn_8000EC3C
bool String::empty() const
{
	return (*text == '\0');
}

// fn_8000DF60
Message::~Message()
{
	unk4->DecRefCount();
}

// fn_800DFC4
void DataArray::DecRefCount(){
	if(--mRefCount == 0) delete this;
}

// // fn_8000DF3C
// Symbol MatchmakingSettings::GetSymbol() const
// {
// 	return unk4;
// }

// fn_8000DF3C
json_object* JsonObject::GetJsonObjectStruct(){
	return json_object_struct;
}
