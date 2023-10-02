#include "string.hpp"
#include "textstream.hpp"
#include "filestream.hpp"
#include "binstream.hpp"
#include "unknown.hpp"
#include "std/string.h"

extern AsyncFileWii NewFile(const char*, int);

// fn_8034C9F8
// ctor
FileStream::FileStream(char c, char* arg1, int arg2) : BinStream(c) {
	int var_r31;
	// AsyncFileWii temp_r3;
	unk20 = 0;
	unk24 = 0;
	if(arg2 == 0){
		var_r31 = 2;
	}
	else if(arg2 == 2){
		var_r31 = 0x10002;
	}
	else{
		var_r31 = 0xA04;
		if(arg2 == 3){
			var_r31 = 0x304;
		}
	}

	str = arg1;
	unk1c = var_r31;
	// temp_r3 = NewFile(arg1, var_r31);
	// unkC = temp_r3;
	// unk1C = (char) (temp_r3 == 0)

}

// fn_8034CAB8
// ctor
FileStream::FileStream(char c) : BinStream(c) {
	unk20 = 0;
	unk24 = 0;
	unk1c = 0;
}

extern bool fn_8000EC3C(FileStream*);
extern void fn_8034CD84(FileStream*);

// fn_8034CB20
// dtor
FileStream::~FileStream(){
	if(fn_8000EC3C(this) == 0){

	}
	fn_8034CD84(this);
	// fn_800E1114
}