#include "stringstream.hpp"
#include "specialarray.hpp"
#include "string.h"

Quazal::StringStream::StringStream() {
    unk0 = &unk_arr[0];
    unk4 = 0x100;
    unk8 = &unk_arr[0];
    unk_arr[0] = 0;
    unk10c = 0;
    unk10d = 1;
    unk10e = 1;
}

Quazal::StringStream::~StringStream() {
    FreeBuffer();
}

void Quazal::StringStream::FreeBuffer() {
    if (unk0 != &unk_arr[0]) {
        SpecialDeleteArray<char>(unk0);
    }
}

void Quazal::StringStream::ResizeBuffer(unsigned int ui) {
    char *ptr = unk0;
    // char* ptr2 = ptr - unk8;
    unk0 = SpecialNewArray<char>(ui, "StringStream.cpp", 0x6B);
    // memcpy(unk0, ptr);
}
