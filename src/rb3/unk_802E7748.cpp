#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "asyncfile.hpp"
#include "asyncfilewii.hpp"

// fn_802E7B68
// AsyncFile's ctor
AsyncFile::AsyncFile(const char* arg1, int arg2) : 
	unk4_async(arg2), unk8_async(0), unk9_async(0), unkc_async(arg1),
	unk18_async(0), unk1c_async(0), unk28_async(0), 
	unk2c_async(0), unk30_async(0) { }

// fn_802E8610
// AsyncFile's dtor
AsyncFile::~AsyncFile(){

}

// fn_802E8678
// gets AsyncFile's String member
String AsyncFile::fn_802E8678(){
	return String(unkc_async);
}

// fn_802E8B7C
// AsyncFileWii's ctor
AsyncFileWii::AsyncFileWii(const char* arg1, int arg2) : AsyncFile(arg1, arg2) {
	unk38_asyncwii = 0;
	unk3c_asyncwii = 0;
	unk40_asyncwii = -1;
}

// fn_802E8FC8
// AsyncFileWii's dtor
AsyncFileWii::~AsyncFileWii(){
	
}