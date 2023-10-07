#include "string.hpp"
#include "textstream.hpp"
#include "binstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "symbol.hpp"

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
	unsigned int size = str.len;
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