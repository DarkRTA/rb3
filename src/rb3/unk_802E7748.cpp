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

// fn_802E780C
String File::GetStringMember(){
	return String();
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
	fn_802E7E2C();
}

extern void fn_80354238(char*);

void AsyncFileWii::fn_802E7E2C(){
	if(unk4 & 4){
		V_Unk9();
	}
	V_Unk24();
	fn_80354238(unk28);
}

// fn_802E7818
int File::V_Unk15(int* a){
	*a = 0;
	return 1;
}

// fn_802E7E8C
int AsyncFile::V_Unk3(int arg1, int arg2){
	int sp8 = arg2;
	V_Unk4(arg1, arg2);
	if(unk8 != 0) return 0;
	while(V_Unk14(&sp8) == 0);
	return sp8;
}

// fn_802E7F7C
bool AsyncFile::V_Unk4(int arg1, int arg2){
	int sp8;
	int temp_r6;
	unsigned int temp_r7;

	sp8 = arg2;
	if(unk8 != 0) return false;
	if(unk28 == 0){
		V_Unk21();
	}
	else {
		temp_r6 = unk18;
		temp_r7 = unk20;
		if(temp_r6 + arg2 > temp_r7){
			sp8 = temp_r7 - temp_r6;
		}
		unk2c = arg1;
		unk30 = sp8;
		unk34 = 0;
		V_Unk14(&sp8);
	}
	return (unk8 == 0);
}

// fn_802E7F00
int AsyncFile::V_Unk5(char* arg1, int arg2){
	int sp8;
	V_Unk6(arg1, arg2);
	if(unk8 != 0) return 0;
	while(V_Unk15(&sp8) == 0);
	return arg2;
}

extern int lbl_808517C8[];

// fn_802E81D4
bool AsyncFile::V_Unk6(char* arg1, int arg2){
	if(unk8 != 0) return false;
	if(unk28 == 0){
		V_Unk18();
	}
	else {
		int r28 = arg2;
		char* r27 = arg1;
		while(unk1c + r28 > lbl_808517C8[0]){
			int r26 = lbl_808517C8[0] - unk1c;
			memcpy(unk28 + unk1c, r27, r26);
			r28 -= r26;
			r27 += r26;
			unk1c = lbl_808517C8[0];
			unk18 += r26;
			V_Unk9();
			if(unk8) return false;
		}
		memcpy(unk28 + unk1c, r27, r28);
		unk1c += r28;
		unk18 += r28;
		if(unk18 > unk20) unk20 = unk18;
	}
	return (arg2 != 0);
}

extern long long lbl_808517D0;

// extern void fn_802E8438(int*, int*, int*);

bool fn_802E8438(long long* a, long long* b, long long* c){
	if(*a < *b){
		*a = *b;
		return true;
	}
	if(*a > *c){
		*a = *c;
		return true;
	}
	return false;
}

// fn_802E8300
int AsyncFile::V_Unk7(int arg1, int arg2){
	long long sp10;
	long long sp8;

	if(unk8 != 0) return unk18;
	if(unk4 & 4) V_Unk9();

	sp10 = unk18;


	if(arg2 == 1) sp10 += arg1;
	else if(arg2 == 0) sp10 = arg1;
	else if(arg2 == 2) sp10 = unk20 + arg1;
	
	sp8 = unk20;
	fn_802E8438(&sp10, &lbl_808517D0, &sp8);
	unk18 = sp10;
	V_Unk20();
	if(unk28 != 0 && unk4 & 2){
		unk1c = lbl_808517C8[0];
		fn_802E8530();
	}
	return unk18;
}

extern int fn_807359C0();
extern bool fn_80735CD0(int*);

// fn_802E8BCC
void AsyncFileWii::V_Unk18(){
	bool temp_r0;
	unk20 = 0;
	unkc.GetText();
	temp_r0 = (fn_807359C0() + 1) == 0;
	unk8 = temp_r0;
	if(temp_r0 == 0){
		if(fn_80735CD0(&unk44) != 0){
			unk20 = unk78;
			unk40 = 1;
			return;
		}
		unk8 = 1;
	}
}

// // fn_802E8C48
// int AsyncFileWii::fn_802E8C48(){ return 1; }

// // fn_802E8C50
// void AsyncFileWii::fn_802E8C50(){ }

// // fn_802E8C54
// int AsyncFileWii::fn_802E8C54(){ return 1; }