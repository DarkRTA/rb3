#include "file.hpp"
#include "arkfile.hpp"

int File::sOpenCount[4];

// fn_802E73DC
File::File(){
	sOpenCount[0]++;
}

// fn_802E738C
File::~File(){
	sOpenCount[0]--;
}

extern void FileMakePath(char*, const char*, char*);
extern int lbl_80902234;
extern char* lbl_808517C0; // "."

// fn_802E72CC
ArkFile::ArkFile(const char* c, int a) : 
	unk18(0), unk1c(0), fpos(0), unk24(0), unk2c(1), str(c) {
		if(a & 4){
			unk24 = 1;
		}
}

extern int* lbl_80902278;
extern void fn_802E9888();

// fn_802E73FC
ArkFile::~ArkFile(){
	if(unk18 > 0){
		fn_802E9888();
	}
	fn_800E1114();
}

// fn_802E748C
int ArkFile::V_Unk3(char* c, int a){
	if(V_Unk4(c, a) == 0) return 0;
	int sp8 = -1;
	while(V_Unk14(&sp8) == 0);
	return sp8;
}

// fn_802E7500
bool ArkFile::V_Unk4(char* c, int a){
	// this one's gross, i don't wanna do it
}