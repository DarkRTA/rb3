#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "jsonobject.hpp"
#include "jsonconverter.hpp"
#include "jsonarray.hpp"
#include "jsonstring.hpp"
#include "jsondouble.hpp"
#include "jsonint.hpp"
#include "binstream.hpp"
#include "bufstream.hpp"
#include "matchmakingsettings.hpp"
#include "symbol.hpp"
#include "memstream.hpp"
#include "json-c/printbuf.h"

// fn_800A6E18
// probably inline
unsigned int String::length() const
{
	return strlen(text);
}

// fn_800A6BD0
// also probably inline
unsigned short UnknownJsonConverterMember::fn_800A6BD0(){
	return unk4;
}

extern "C" UnknownJsonConverterMember* fn_800A6A38(UnknownJsonConverterMember*, Dummy*);

// fn_800A673C
JsonConverter::JsonConverter(){
	Dummy i;
	fn_800A6A38(&mem, &i);
}

extern "C" UnknownJsonConverterMember* fn_800A6A78(UnknownJsonConverterMember*, Dummy*);

// fn_800A6A38
UnknownJsonConverterMember* fn_800A6A38(UnknownJsonConverterMember* mem, Dummy* d){
	Dummy j;
	fn_800A6A78(mem, &j);
	return mem;
}

extern "C" UnknownJsonConverterMember* fn_800A6AA8(UnknownJsonConverterMember*, Dummy*);

// fn_800A6A78
UnknownJsonConverterMember* fn_800A6A78(UnknownJsonConverterMember* mem, Dummy* d){
	fn_800A6AA8(mem, d);
	return mem;
}

extern "C" void fn_800A6AE8(UnknownJsonConverterMember*, Dummy*, int);

// fn_800A6AA8
UnknownJsonConverterMember* fn_800A6AA8(UnknownJsonConverterMember* mem, Dummy* d){
	fn_800A6AE8(mem, d, 0);
	mem->unk4 = 0;
	mem->unk6 = 0;
	return mem;
}

// fn_800A6AE8
void fn_800A6AE8(UnknownJsonConverterMember* mem, Dummy* d, int i){ mem->unk0 = i; }

// fn_800A6AF0
JsonConverter::~JsonConverter(){
	unsigned short var_r31;
	if(mem.fn_800A6BD0() != 0){
		var_r31 = mem.fn_800A6BD0() - 1;
		while(var_r31 >= 0){
			var_r31--;
		}
	}
}

// ---------------------------------------------------------------

extern "C" JsonArray* fn_800A6BD8(JsonConverter*);
extern "C" void fn_800A6EA8(JsonConverter*, JsonObject*);

// fn_800A6BD8
JsonArray* fn_800A6BD8(JsonConverter* jc){
	JsonArray* j = new JsonArray();
	fn_800A6EA8(jc, j);
	return j;
}

extern "C" JsonString* fn_800A6C34(JsonConverter*, const char*);

// fn_800A6C34
JsonString* fn_800A6C34(JsonConverter* jc, const char* c){
	JsonString* j = new JsonString(c);
	fn_800A6EA8(jc, j);
	return j;
}

extern "C" JsonInt* fn_800A6C98(JsonConverter*, int);

// fn_800A6C98
JsonInt* fn_800A6C98(JsonConverter* jc, int i){
	JsonInt* j = new JsonInt(i);
	fn_800A6EA8(jc, j);
	return j;
}

extern "C" JsonDouble* fn_800A6CFC(JsonConverter*, double);

// fn_800A6CFC
JsonDouble* fn_800A6CFC(JsonConverter* jc, double d){
	JsonDouble* j = new JsonDouble(d);
	fn_800A6EA8(jc, j);
	return j;
}


extern "C" JsonObject* fn_800A6D68(JsonConverter*, String);

// fn_800A6D68
JsonObject* fn_800A6D68(JsonConverter* jc, String str){
	JsonObject* obj = new JsonObject();
	printbuf* pb = printbuf_new();
	if(pb == 0) return nullptr;
	printbuf_memappend(pb, str.c_str(), str.length());
	obj->json_object_struct = json_tokener_parse(pb->buf);
	printbuf_free(pb);
	fn_800A6EA8(jc, obj);
	return obj;
}

extern "C" JsonObject* fn_800A6E20(JsonConverter*, JsonArray*, int);

// fn_800A6E20
JsonObject* fn_800A6E20(JsonConverter* jc, JsonArray* ja, int i){
	ja->Length();
	JsonObject* obj = new JsonObject();
	obj->json_object_struct = json_object_array_get_idx(ja->GetJsonObjectStruct(), i);
	fn_800A6EA8(jc, obj);
	return obj;
}

extern "C" void fn_800A6EF4(UnknownJsonConverterMember*, JsonObject*);

// fn_800A6EA8
void fn_800A6EA8(JsonConverter* jc, JsonObject* obj){
	json_object_get(obj->GetJsonObjectStruct());
	fn_800A6EF4(&jc->mem, obj);
}

extern "C" void fn_800A6F1C(UnknownJsonConverterMember*, UnknownJsonConverterMember*);

// fn_800A6A24

// fn_800A6EF4
void fn_800A6EF4(UnknownJsonConverterMember* mem, JsonObject* obj){
	UnknownJsonConverterMember i;
	fn_800A6F1C(mem, &i);
}

extern "C" void fn_800A6FA4(UnknownJsonConverterMember*, unsigned short);
extern "C" void fn_800A6FB4(UnknownJsonConverterMember*, UnknownJsonConverterMember*);

// fn_800A6F1C
void fn_800A6F1C(UnknownJsonConverterMember* mem1, UnknownJsonConverterMember* mem2){
	if(mem1->unk4 != mem1->unk6){
		// A6A24
		fn_800A6FB4(mem1, mem2);
		fn_800A6FA4(mem1, 1);
	}
}

// fn_800A6FA4
void fn_800A6FA4(UnknownJsonConverterMember* mem, unsigned short i){
	mem->unk4 += i;
}

// fn_800A6FB4
void fn_800A6FB4(UnknownJsonConverterMember* mem1, UnknownJsonConverterMember* mem2){
	if(mem1 == 0) return;
	mem1->unk0 = mem2->unk0;
}

// ---------------------------------------------------------------

BinStream *BinStream::WriteEndian4(unsigned int i)
{
	WriteEndian(&i, 4);
	return this;
}

BinStream *BinStream::ReadEndian4(unsigned int *i)
{
	ReadEndian(i, 4);
	return this;
}

// fn_800A9C70
int BufStream::Tell()
{
	return fpos;
}

// fn_800A7730
BinStream *BinStream::ReadSingle(void *v)
{
	Read(v, 1);
	return this;
}

// fn_800A7764
BinStream *BinStream::ReadSingleIntoBool(bool *b)
{
	unsigned char c;
	ReadSingle(&c);
	*b = (c != 0);
	return this;
}

// fn_800A7844
MatchmakingSettings::~MatchmakingSettings()
{
}

// fn_800A71BC
void MatchmakingSettings::SetMode(Symbol s, int i)
{
	unk4 = s;
	unk8 = i;
}

// fn_800A7DE0
void MatchmakingSettings::SetRanked(bool b)
{
	unkc = b;
}

// fn_800A71FC
void MatchmakingSettings::AddCustomSetting(int i, int j)
{
}

// fn_800A75FC - WriteSingle
BinStream *BinStream::WriteSingle(char c)
{
	Write(&c, 1);
	return this;
}

// fn_800A7DE8
bool MemStream::Fail(){
	return failed;
}

extern char *lbl_808540E0; // RB2 marks this as gNullStr

// fn_800A7C40
Symbol::Symbol()
{
	m_string = lbl_808540E0;
}

// fn_800A7B30
MatchmakingSettings::MatchmakingSettings()
{
}