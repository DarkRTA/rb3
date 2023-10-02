#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "file.hpp"
#include "asyncfile.hpp"
#include "asyncfilewii.hpp"

// fn_802E7B68
// AsyncFile's ctor
AsyncFile::AsyncFile(const char* arg1, int arg2) : 
	unk4(arg2), unk8(0), unk9(0), unkc(arg1),
	unk18(0), unk1c(0), unk28(0), 
	unk2c(0), unk30(0) { }

// fn_802E8610
// AsyncFile's dtor
AsyncFile::~AsyncFile(){

}

// fn_802E8678
// gets AsyncFile's String member
String AsyncFile::GetStringMember(){
	return String(unkc);
}

// fn_802E8B7C
// AsyncFileWii's ctor
AsyncFileWii::AsyncFileWii(const char* arg1, int arg2) : AsyncFile(arg1, arg2) {
	unk38 = 0;
	unk3c = 0;
	unk40 = -1;
}

// fn_802E8FC8
// AsyncFileWii's dtor
AsyncFileWii::~AsyncFileWii(){

}

// fn_802E780C
String File::GetStringMember(){
	return String();
}

extern int fn_807359C0();
extern bool fn_80735CD0(int);

// fn_802E8BCC
void AsyncFileWii::fn_802E8BCC(){
	bool temp_r0;
	unk20 = 0;
	unkc.GetText();
	temp_r0 = (fn_807359C0() + 1) == 0;
	unk8 = temp_r0;
	if(temp_r0 == 0){
		if(fn_80735CD0(unk44) != 0){
			unk20 = unk78;
			unk40 = 1;
			return;
		}
		unk8 = 1;
	}
}

// fn_802E8C48
int AsyncFileWii::fn_802E8C48(){ return 1; }

// fn_802E8C50
void AsyncFileWii::fn_802E8C50(){ }

// fn_802E8C54
int AsyncFileWii::fn_802E8C54(){ return 1; }