#include "stringstream.hpp"
#include "specialarray.hpp"

Quazal::StringStream::StringStream(){
    unk0 = &unk_arr[0];
    unk4 = 0x100;
    unk8 = &unk_arr[0];
    unk_arr[0] = 0;
    unk10c = 0;
    unk10d = 1;
    unk10e = 1;
}

Quazal::StringStream::~StringStream(){
    FreeBuffer(unk0);
}

void Quazal::StringStream::FreeBuffer(char* c){
    if(unk0 != &unk_arr[0]){
        SpecialDeleteArray<char>(c);
    }
}