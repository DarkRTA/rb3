#include "string.hpp"
#include "textstream.hpp"
#include "binstream.hpp"
#include "unknown.hpp"
#include "std/string.h"

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