#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "file.hpp"
#include "asyncfile.hpp"
#include "asyncfilewii.hpp"
#include "asyncfilecnt.hpp"
#include "arkfile.hpp"

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

void AsyncFile::fn_802E7E2C(){
	if(unk4 & 4){
		V_Unk9();
	}
	V_Unk25();
	fn_80354238(unk28);
}

// fn_802E7818
int File::V_Unk15(int* a){
	*a = 0;
	return 1;
}

// fn_802E7E8C
int AsyncFile::V_Unk3(char* arg1, int arg2){
	int sp8 = arg2;
	V_Unk4(arg1, arg2);
	if(unk8 != 0) return 0;
	while(V_Unk14(&sp8) == 0);
	return sp8;
}

// fn_802E7F7C
bool AsyncFile::V_Unk4(char* arg1, int arg2){
	int sp8;
	int temp_r6;
	unsigned int temp_r7;

	sp8 = arg2;
	if(unk8 != 0) return false;
	if(unk28 == 0){
		V_Unk23();
	}
	else {
		temp_r6 = unk18;
		temp_r7 = filesize;
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
		V_Unk20(arg1, arg2);
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
		if(unk18 > filesize) filesize = unk18;
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
unsigned int AsyncFile::V_Unk7(int arg1, int arg2){
	long long sp10;
	long long sp8;

	if(unk8 != 0) return unk18;
	if(unk4 & 4) V_Unk9();

	sp10 = unk18;
	if(arg2 == 1) sp10 += arg1;
	else if(arg2 == 0) sp10 = arg1;
	else if(arg2 == 2) sp10 = filesize + arg1;
	
	sp8 = filesize;
	fn_802E8438(&sp10, &lbl_808517D0, &sp8);
	unk18 = sp10;
	V_Unk22();
	if(unk28 != 0 && unk4 & 2){
		unk1c = lbl_808517C8[0];
		fn_802E8530();
	}
	return unk18;
}

// fn_802E84AC
unsigned int AsyncFile::V_Unk8(){
	return unk18;
}

// fn_802E84B4
void AsyncFile::V_Unk9(){
	if(unk8 == 0 && unk4 & 4){
		V_Unk20(unk28, unk1c);
		while(V_Unk21() == 0);
		unk1c = 0;
	}
}

// fn_802E85E0
bool AsyncFile::V_Unk10(){
	return (unk18 == filesize);
}

// fn_802E85F8
bool AsyncFile::V_Unk11(){
	return unk8;
}

// fn_802E8600
unsigned int AsyncFile::GetFileSize(){
	return filesize;
}

// fn_802E8608
int AsyncFile::V_Unk13(){
	return unk24;
}

// fn_802E8030
int AsyncFile::V_Unk14(int* a){
	int temp_r28;

	if(unk8 != 0){
		*a = 0;
		return 1;
	}
	if(unk28 != 0 && unk30 == 0){
		*a = unk34;
		return 1;
	}
	if(V_Unk24() == 0){
		*a = unk34;
		return 0;
	}
	
	if(unk28 == 0) return 1;
	
	if(unk1c + unk30 > lbl_808517C8[0]){
		temp_r28 = lbl_808517C8[0] - unk1c;
		memcpy(unk2c, unk28 + unk1c, temp_r28);
		unk34 += temp_r28;
		unk1c = lbl_808517C8[0];
		unk18 += temp_r28;
		unk30 -= temp_r28;
		unk2c += temp_r28;
		fn_802E8530();
		*a = unk34;
		return 0;
	}
	memcpy(unk2c, unk28 + unk1c, unk30);
	unk34 += unk30;
	unk1c += unk30;
	unk18 += unk30;
    unk30 = 0;
	*a = unk34;
	return 1;
}

// fn_802E81AC
int AsyncFile::V_Unk15(int* a){
	if(unk28 != 0) return 1;
	return V_Unk21();
}

extern int fn_807359C0();
extern bool fn_80735CD0(int, int*);

// fn_802E8BCC
void AsyncFileWii::V_Unk18(char* a, int b){
	filesize = 0;
	
	unkc.GetText();
	int ret = fn_807359C0();
	unk8 = (ret + 1) == 0;
	if(unk8 == 0){
		if(fn_80735CD0(ret, &unk44) != 0){
			filesize = unk78;
			unk40 = 1;
			return;
		}
		unk8 = 1;
	}
}

// fn_802E8C48
int AsyncFileWii::V_Unk19(){ return 1; }

// fn_802E8C50
int AsyncFileWii::V_Unk20(char* c, int a){ }

// fn_802E8C54
int AsyncFileWii::V_Unk21(){ return 1; }

// fn_802E8C5C
void AsyncFileWii::V_Unk22(){
	while(V_Unk24() == 0);
	unk38 = V_Unk8();
}

// fn_802E8CB8
// calls fn_80735FB0
void AsyncFileWii::V_Unk23(){
	unk3c = 1;
	// V_Unk8();
}

// fn_802E8D28
int AsyncFileWii::V_Unk24(){

}

extern bool fn_80735E60(int);

// fn_802E8F1C
void AsyncFileWii::V_Unk25(){
	if(unk40 > -1){
		while(V_Unk24() == 0);
		unk8 = (fn_80735E60(unk44) == 0);
	}
	unk40 = -1;
}

unsigned int fn_802E85D0(unsigned int a, unsigned int b){
	if (b < a) return b;
	return a;
}

// fn_802E8530
void AsyncFile::fn_802E8530(){
	if((unk8 == 0) && (unk4 & 2)){
		if(unk1c != lbl_808517C8[0]){
			V_Unk22();
		}
		fn_802E85D0(unk18, lbl_808517C8[0]);
		V_Unk23();
		unk1c = 0;
	}
}

// fn_802E7810
String ArkFile::GetStringMember(){
	return str;
}

// fn_802E7748
bool ArkFile::V_Unk11(){
	return unk24 != 0;
}

// fn_802E7758
unsigned int ArkFile::GetFileSize(){
	return filesize;
}

// fn_802E7760
int ArkFile::V_Unk13(){
	return unk14;
}

extern void fn_802EA488(int*, int*);
extern int lbl_80902278;

// fn_802E7790
int ArkFile::V_Unk14(int* a){
	fn_802EA488(&lbl_80902278, a);
    *a = unk1c;
    return (unk18 == 0);
}

extern void fn_802EB6E4(int*, int, int, int);

// fn_802E77E4
int ArkFile::V_Unk16(int* a){
	fn_802EB6E4(a, unk4, unk8 + fpos, unkc + fpos);
}

// fn_802E7768
void ArkFile::fn_802E7768(int a){
	unk18--;
	unk1c += a;
	fpos += a;
}

extern char fn_802FB54C(const char*, int);

// fn_802E8680
AsyncFileCNT::AsyncFileCNT(const char* c, int a) : AsyncFile(c, a) {
	char* temp_r30;
    int temp_r31;
    char* temp_r3_2;
    char* temp_r3_3;
    char* var_r31;
	char temp_r3;
	unk38 = 0;
	unk3c = 0;
	unk44 = -1;
	unk48 = 0;
	temp_r3 = fn_802FB54C(c, 0);
	if(temp_r3 != 0){
		temp_r30 = (char*)c + 4;
		temp_r3_2 = strchr(temp_r30, 0x2F);
		if(temp_r3_2 != 0){
			var_r31 = temp_r3_2 + 1;
			temp_r3_3 = strchr(var_r31, 0x2F);
			if(temp_r3_3 != 0){
				var_r31 = temp_r3_3;
			}
		}
		else {
			var_r31 = temp_r30 + strlen(temp_r30);
		}
		temp_r31 = var_r31 - temp_r30;
		// strncpy(arg0 + 0x4A, temp_r30, temp_r31);
        // (arg0 + temp_r31)->unk4A = 0;
		unkc = temp_r30 + temp_r31;
		unkc.GetText();
		unk9 = 1;
	}

	//  if (temp_r3 != 0) {
    //     temp_r30 = arg1 + 4;
    //     temp_r3_2 = strchr(temp_r30, 0x2F);
    //     if (temp_r3_2 != 0) {
    //         var_r31 = temp_r3_2 + 1;
    //         temp_r3_3 = strchr(var_r31, 0x2F);
    //         if (temp_r3_3 != 0) {
    //             var_r31 = temp_r3_3;
    //         }
    //     } else {
    //         var_r31 = temp_r30 + strlen(temp_r30);
    //     }
    //     temp_r31 = var_r31 - temp_r30;
    //     strncpy(arg0 + 0x4A, temp_r30, temp_r31);
    //     (arg0 + temp_r31)->unk4A = 0;
    //     __as__6StringFPCc(arg0 + 0xC, temp_r30 + temp_r31);
    //     GetText__6StringCFv(arg0 + 0xC);
    //     arg0->unk9 = 1;
    // }
}

// fn_802E8B10
AsyncFileCNT::~AsyncFileCNT(){
	fn_802E7E2C();
}

// fn_802E8774
int AsyncFileCNT::V_Unk16(int* a){
	*a = 0;
	return 0;
}

// fn_802E8784
void AsyncFileCNT::V_Unk18(char* c, int a){

}

// fn_802E88C0
int AsyncFileCNT::V_Unk19(){
	return 1;
}

// fn_802E88C8
int AsyncFileCNT::V_Unk20(char*, int){

}

// fn_802E88CC
int AsyncFileCNT::V_Unk21(){
	return 1;
}

// fn_802E88D4
void AsyncFileCNT::V_Unk22(){
	if(V_Unk8()){
		unk8 = 1;
	}
}

// fn_802E892C
void AsyncFileCNT::V_Unk23(){

}

// fn_802E89FC
int AsyncFileCNT::V_Unk24(){

}

// fn_802E8AA4
void AsyncFileCNT::V_Unk25(){

}

extern unsigned char lbl_808E3018;

// fn_802E8F88
bool fn_802E8F88(){
	if(lbl_808E3018 != 0){
		return (fn_807359C0() + 1) != 0;
	}
    return 0;
}