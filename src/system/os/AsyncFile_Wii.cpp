#include "Str.h"
#include "TextStream.h"
#include "unknown.hpp"
#include "string.h"
#include "file.hpp"
#include "AsyncFile.h"
#include "AsyncFileCNT.h"
#include "AsyncFile_Wii.h"

// fn_802E8B7C
// AsyncFileWii's ctor
AsyncFileWii::AsyncFileWii(const char *arg1, int arg2) : AsyncFile(arg1, arg2) {
    unk38 = 0;
    unk3c = 0;
    unk40 = -1;
}

// fn_802E8FC8
// AsyncFileWii's dtor
AsyncFileWii::~AsyncFileWii() {
    Terminate();
}

extern int fn_807359C0();
extern bool fn_80735CD0(int, int *);

// fn_802E8BCC - _Open?
void AsyncFileWii::_Open() {
    size = 0;

    fname.c_str();
    int ret = fn_807359C0(); // DVDConvertPathToEntrynum?
    failed = (ret + 1) == 0;
    if (failed == 0) {
        if (fn_80735CD0(ret, &unk44) != 0) { // DVDFastOpen?
            size = unk78;
            unk40 = 1;
            return;
        }
        failed = 1;
    }
}

// fn_802E8C48
int AsyncFileWii::V_Unk19() {
    return 1;
}

// fn_802E8C50 - _Write --> returns 0
int AsyncFileWii::_Write(const void *c, int a) {
}

// fn_802E8C54
int AsyncFileWii::V_Unk21() {
    return 1;
}

// fn_802E8C5C
void AsyncFileWii::_SeekToTell() {
    while (_ReadDone() == 0)
        ;
    unk38 = Tell();
}

// fn_802E8CB8
// calls fn_80735FB0
void AsyncFileWii::_ReadAsync(void *a, int b) {
    unk3c = 1;
    // Tell();
}

// fn_802E8D28 - _ReadDone
int AsyncFileWii::_ReadDone() {
    return 0;
}

extern bool fn_80735E60(int);

// fn_802E8F1C - _Close
void AsyncFileWii::_Close() {
    if (unk40 > -1) {
        while (_ReadDone() == 0)
            ;
        failed = (fn_80735E60(unk44) == 0);
    }
    unk40 = -1;
}

extern unsigned char lbl_808E3018;

// fn_802E8F88
bool fn_802E8F88() {
    if (lbl_808E3018 != 0) {
        return (fn_807359C0() + 1) != 0;
    }
    return 0;
}
