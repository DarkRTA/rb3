#include "string.hpp"
#include "textstream.hpp"
#include "binstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "symbol.hpp"
#include "bufstream.hpp"
#include "bufstreamnand.hpp"
#include "idatachunk.hpp"
#include "cacheid.hpp"
#include "cacheidwii.hpp"

#pragma dont_inline on
// fn_80342D18
// BinStream's ctor
BinStream::BinStream(bool b)
{
	unk04 = b;
	unk08 = 0;
}
#pragma dont_inline reset

// fn_80342D34
// BinStream's dtor
BinStream::~BinStream()
{
	delete unk08;
}

#pragma dont_inline on
// fn_80343114
void SwapData(const void* v1, void* v2, int num_bytes){
	switch(num_bytes){
		case 2:
			unsigned short* s1 = (unsigned short*)v1;
			short* s2 = (short*)v2;
			*s2 = SwapDataHalfWord(*s1); 
			break;
		case 4:
			int* i1 = (int*)v1;
			int* i2 = (int*)v2;
			*i2 = SwapDataWord(*i1); 
			break;
		case 8: 
			long long* l1 = (long long*)v1;
			long long* l2 = (long long*)v2;
			*l2 = SwapDataDoubleWord(*l1);
			break;
		default: break;
	}
}
#pragma dont_inline reset

extern char lbl_808567BC[]; //this label contains "<unnamed>"

const char *BinStream::Name() const
{
	return "<unnamed>"; // lbl_808567BC
}

// fn_80342E44
void BinStream::DisableEncryption()
{
	delete unk08;
	unk08 = 0;
}

// fn_80342AD8
BinStream *BinStream::operator<<(const char *c)
{
	unsigned int size = strlen(c);
	WriteWord(size);
	Write(c, size);
	return this;
}

// fn_80342B38
BinStream *BinStream::operator<<(const Symbol &s)
{
	char *str = s.m_string;
	unsigned int size = strlen(str);
	WriteWord(size);
	Write(str, size);
	return this;
}

// fn_80342B98
BinStream *BinStream::operator<<(const String &str)
{
	unsigned int size = str.length();
	WriteWord(size);
	Write(str.c_str(), size);
	return this;
}

// fn_80342C58
BinStream *BinStream::operator>>(Symbol &s)
{
	char why[0x200];
	ReadString(why, 0x200);
	s = Symbol(why);
	return this;
}

// fn_80342C00
void BinStream::ReadString(char *c, int i)
{
	unsigned int a;
	ReadWord(&a);
	Read(c, a);
	c[a] = 0;
}

// fn_80342CB4
BinStream *BinStream::operator>>(String &s)
{
	unsigned int a;
	ReadWord(&a);
	s.resize(a);
	Read((char *)s.c_str(), a);
	return this;
}

// fn_80342D98
void BinStream::EnableReadEncryption()
{
	unsigned int a;
	ReadWord(&a);
	unk08 = new Rand2(a);
}

extern unsigned int fn_802DDCDC(BinStream *);

// fn_80342DE4
void BinStream::EnableWriteEncryption(int i)
{
	unsigned int a = fn_802DDCDC(this);
	WriteWord(a);
	unk08 = new Rand2(a);
}

// fn_80343058
void BinStream::ReadEndian(void *v, int i)
{
	Read(v, i);
	if (unk04 != 0) {
		SwapData(v, v, i);
	}
}

void BinStream::Read(void *v, int i)
{
	void *temp_r31;
	unsigned char *var_r30;

	var_r30 = (unsigned char *)v;
	if (Fail() != 0) {
		Name();
		memset(var_r30, 0, i);
		return;
	}
	ReadImpl(var_r30, i);
	if (unk08 != nullptr) {
		temp_r31 = var_r30 + i;
		while (var_r30 < temp_r31) {
			*var_r30++ ^= unk08->Int();
		}
	}
}

void BinStream::Write(const void *v, int i)
{
	unsigned char sp8[512];
	if (Fail() != 0) {
		Name();
		return;
	}
	if (unk08 == nullptr) {
		WriteImpl((void *)v, i);
		return;
	}
	while (i > 0) {
		int temp_r29 = Minimum(0x200, i);
		for (int j = 0; j < temp_r29; j++) {
			unsigned char x = (unsigned char)unk08->Int();
			sp8[j] = x ^ ((const char *)v)[j];
		}
		WriteImpl(&sp8, temp_r29);
		i -= 0x200;
		(char *)v += 0x200;
	}
}

// fn_80343058 - Seek
void BinStream::Seek(int i, SeekType s)
{
	Fail();
	SeekImpl(i, s);
}

void BinStream::WriteEndian(const void *v, int i)
{
	char sp8;
	if (unk04 != 0) {
		SwapData((void *)v, &sp8, i);
		Write(&sp8, i);
	} else
		Write(v, i);
}