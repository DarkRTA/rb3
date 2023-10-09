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

// fn_800A6E18
// probably inline
unsigned int String::length() const
{
	return strlen(text);
}

// // fn_800A6BD0
// // also probably inline
// unsigned short String::GetTextLengthWithoutStrLen(){
// 	return len;
// }

// fn_800A6360
JsonObject::JsonObject()
{
	unk4 = 0;
}

extern void fn_800C6D4C(int);

// fn_800A6378
JsonObject::~JsonObject()
{
	fn_800C6D4C(unk4);
}

// fn_800A673C
JsonConverter::JsonConverter()
{
}

// fn_800A6AF0
JsonConverter::~JsonConverter()
{
}

extern void fn_800C7690();

// fn_800A63EC
JsonArray::JsonArray()
{
	fn_800C7690();
}

// fn_800A6430
JsonArray::~JsonArray()
{
}

extern void fn_800C74C8();

// fn_800A6520
JsonString::JsonString()
{
	fn_800C74C8();
}

// fn_800A6574
JsonString::~JsonString()
{
}

extern void fn_800C72E8(JsonDouble *);

// fn_800A6688
JsonDouble::JsonDouble()
{
	fn_800C72E8(this);
}

// fn_800A66DC
JsonDouble::~JsonDouble()
{
}

extern void fn_800C71D4(JsonInt *);

// fn_800A65D4
JsonInt::JsonInt()
{
	fn_800C71D4(this);
}

// fn_800A6628
JsonInt::~JsonInt()
{
}

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
bool MatchmakingSettings::GetRanked() const
{
	return unkc;
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