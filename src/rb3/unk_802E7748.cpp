#include "string.hpp"
#include "textstream.hpp"
#include "unknown.hpp"
#include "std/string.h"
#include "file.hpp"
#include "asyncfile.hpp"
#include "asyncfilewii.hpp"
#include "asyncfilecnt.hpp"

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
	Terminate();
}

extern int fn_807359C0();
extern bool fn_80735CD0(int, int*);

// fn_802E8BCC - _Open?
void AsyncFileWii::_Open(){
	size = 0;
	
	str.c_str();
	int ret = fn_807359C0(); // DVDConvertPathToEntrynum?
	failed = (ret + 1) == 0;
	if(failed == 0){
		if(fn_80735CD0(ret, &unk44) != 0){ // DVDFastOpen?
			size = unk78;
			unk40 = 1;
			return;
		}
		failed = 1;
	}
}

// fn_802E8C48
int AsyncFileWii::V_Unk19(){ return 1; }

// fn_802E8C50 - _Write --> returns 0
int AsyncFileWii::_Write(const void* c, int a){ }

// fn_802E8C54
int AsyncFileWii::V_Unk21(){ return 1; }

// fn_802E8C5C
void AsyncFileWii::V_Unk22(){
	while(_ReadDone() == 0);
	unk38 = Tell();
}

// fn_802E8CB8
// calls fn_80735FB0
void AsyncFileWii::V_Unk23(){
	unk3c = 1;
	// Tell();
}

// fn_802E8D28 - _ReadDone
int AsyncFileWii::_ReadDone(){
	return 0;
}

extern bool fn_80735E60(int);

// fn_802E8F1C - _Close
void AsyncFileWii::_Close(){
	if(unk40 > -1){
		while(_ReadDone() == 0);
		failed = (fn_80735E60(unk44) == 0);
	}
	unk40 = -1;
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
		str = temp_r30 + temp_r31;
		str.c_str();
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
    //     c_str__6StringCFv(arg0 + 0xC);
    //     arg0->unk9 = 1;
    // }
}

// fn_802E8B10
AsyncFileCNT::~AsyncFileCNT(){
	Terminate();
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
	if(Tell()){
		failed = 1;
	}
}

// fn_802E892C
void AsyncFileCNT::V_Unk23(){

}

// fn_802E89FC
int AsyncFileCNT::_ReadDone(){
	return 0;
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