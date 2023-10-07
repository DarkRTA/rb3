#include "string.hpp"
#include "textstream.hpp"
#include "binstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "symbol.hpp"
#include "bufstream.hpp"

// fn_80342D18
// BinStream's ctor
BinStream::BinStream(bool b){
	unk04 = b;
	unk08 = 0;
}

// fn_80342D34
// BinStream's dtor
BinStream::~BinStream(){
	delete unk08;
}

extern char lbl_808567BC[]; //this label contains "<unnamed>"

const char* BinStream::Name() const {
	return "<unnamed>"; // lbl_808567BC
}

// fn_80342E44
void BinStream::DisableEncryption(){
	delete unk08;
	unk08 = 0;
}

// fn_80342AD8
BinStream* BinStream::operator<<(const char* c){
	unsigned int size = strlen(c);
	WriteEndian4(size);
	Write(c, size);
	return this;
}

// fn_80342B38
BinStream* BinStream::operator<<(const Symbol& s){
	char* str = s.m_string;
	unsigned int size = strlen(str);
	WriteEndian4(size);
	Write(str, size);
	return this;
}

// fn_80342B98
BinStream* BinStream::operator<<(const String& str){
	unsigned int size = str.length();
	WriteEndian4(size);
	Write(str.c_str(), size);
	return this;
}

// fn_80342C58
BinStream* BinStream::operator>>(Symbol& s){
	char why[0x200];
	ReadString(why, 0x200);
	s = Symbol(why);
	return this;
}

// fn_80342C00
void BinStream::ReadString(char* c, int i){
	unsigned int a;
	ReadEndian4(&a);
	Read(c, a);
	c[a] = 0;
}

// fn_80342CB4
BinStream* BinStream::operator>>(String& s){
	unsigned int a;
	ReadEndian4(&a);
	s.resize(a);
	Read((char*)s.c_str(), a);
	return this;
}

// fn_80342D98
void BinStream::EnableReadEncryption(){
	unsigned int a;
	ReadEndian4(&a);
	unk08 = new Rand2(a);
}

extern unsigned int fn_802DDCDC(BinStream*);

// fn_80342DE4
void BinStream::EnableWriteEncryption(int i){
	unsigned int a = fn_802DDCDC(this);
	WriteEndian4(a);
	unk08 = new Rand2(a);
}

// fn_80343058

extern void fn_80343114(void*, void*, int);

void BinStream::ReadEndian(void* v, int i){
	Read(v, i);
	if(unk04 != 0){
		fn_80343114(v, v, i);
	}
}

void BinStream::Read(void* v, int i){
	void* temp_r31;
	unsigned char* var_r30;

	var_r30 = (unsigned char*)v;
	if(Fail() != 0){
		Name();
		memset(var_r30, 0, i);
		return;
	}
	ReadImpl(var_r30, i);
	if(unk08 != nullptr){
		temp_r31 = var_r30 + i;
		while(var_r30 < temp_r31){
			*var_r30++ ^= unk08->Int();
		}
	}
}

// fn_803431F4
BufStream::BufStream(void* v, int i, bool b) : BinStream(b) {
	unk1c = 0;
	unk20 = 0;
	unkc = v;
	unk10 = (v == 0);
	fpos = 0;
	size = i;
}

// fn_80343270
BufStream::~BufStream(){
	DeleteChecksum();
}


// fn_803436BC
const char* BufStream::Name() const {
	if(!name.empty()){
		return name.c_str();
	}
	return BinStream::Name();
}

// fn_80343708
void BufStream::SetName(const char* c){
	name = c;
}

// fn_80343710
bool BufStream::Eof() {
	return (size - fpos == 0);
}