#include "os/AsyncFile.h"

#include <string.h>

#include "os/File.h"
#include "utl/Str.h"

#include "unknown.hpp"

// fn_802E7B68
// AsyncFile's ctor
AsyncFile::AsyncFile(const char *arg1, int arg2)
    : unk4(arg2), failed(0), unk9(0), fname(arg1), fpos(0), unk1c(0), unk28(0), unk2c(0),
      unk30(0) {
}

// fn_802E8610
// AsyncFile's dtor
AsyncFile::~AsyncFile() {
}

// fn_802E8678
String AsyncFile::Filename() {
    return String(fname);
}

extern void fn_80354238(char *);

// fn_802E7E2C
void AsyncFile::Terminate() { // Terminate
    if (unk4 & 4) {
        Flush();
    }
    _Close();
    fn_80354238(unk28); // MemFree
}

// fn_802E7E8C - Read
int AsyncFile::Read(void *arg1, int arg2) {
    int sp8 = arg2;
    ReadAsync(arg1, arg2);
    if (failed != 0)
        return 0;
    while (ReadDone(sp8) == 0)
        ;
    return sp8;
}

// fn_802E7F7C - ReadAsync
bool AsyncFile::ReadAsync(void *arg1, int arg2) {
    int sp8;
    int temp_r6;
    unsigned int temp_r7;

    sp8 = arg2;
    if (failed != 0)
        return false;
    if (unk28 == 0) {
        _SeekToTell();
    } else {
        temp_r6 = fpos;
        temp_r7 = size;
        if (temp_r6 + arg2 > temp_r7) {
            sp8 = temp_r7 - temp_r6;
        }
        unk2c = (char *)arg1;
        unk30 = sp8;
        unk34 = 0;
        ReadDone(sp8);
    }
    return (failed == 0);
}

// fn_802E7F00
int AsyncFile::V_Unk5(void *arg1, int arg2) {
    int sp8;
    Write(arg1, arg2);
    if (failed != 0)
        return 0;
    while (V_Unk15(&sp8) == 0)
        ;
    return arg2;
}

extern int lbl_808517C8[]; // RB2 calls this "gBufferSize"

// fn_802E81D4 - Write
bool AsyncFile::Write(const void *arg1, int arg2) {
    if (failed != 0)
        return false;
    if (unk28 == 0) {
        _Write(arg1, arg2);
    } else {
        int r28 = arg2;
        char *r27 = (char *)arg1;
        while (unk1c + r28 > lbl_808517C8[0]) {
            int r26 = lbl_808517C8[0] - unk1c;
            memcpy(unk28 + unk1c, r27, r26);
            r28 -= r26;
            r27 += r26;
            unk1c = lbl_808517C8[0];
            fpos += r26;
            Flush();
            if (failed)
                return false;
        }
        memcpy(unk28 + unk1c, r27, r28);
        unk1c += r28;
        fpos += r28;
        if (fpos > size)
            size = fpos;
    }
    return (arg2 != 0);
}

extern long long lbl_808517D0;

// extern void fn_802E8438(int*, int*, int*);

bool fn_802E8438(long long *a, long long *b, long long *c) {
    if (*a < *b) {
        *a = *b;
        return true;
    }
    if (*a > *c) {
        *a = *c;
        return true;
    }
    return false;
}

// fn_802E8300 - Seek
unsigned int AsyncFile::Seek(int arg1, int arg2) {
    long long sp10;
    long long sp8;

    if (failed != 0)
        return fpos;
    if (unk4 & 4)
        Flush();

    sp10 = fpos;
    if (arg2 == 1)
        sp10 += arg1;
    else if (arg2 == 0)
        sp10 = arg1;
    else if (arg2 == 2)
        sp10 = size + arg1;

    sp8 = size;
    fn_802E8438(&sp10, &lbl_808517D0, &sp8);
    fpos = sp10;
    V_Unk21();
    if (unk28 != 0 && unk4 & 2) {
        unk1c = lbl_808517C8[0];
        FillBuffer(); // FillBuffer
    }
    return fpos;
}

// fn_802E84AC - Tell
unsigned int AsyncFile::Tell() {
    return fpos;
}

// fn_802E84B4 - Flush
void AsyncFile::Flush() {
    if (failed == 0 && unk4 & 4) {
        _Write(unk28, unk1c);
        while (V_Unk21() == 0)
            ;
        unk1c = 0;
    }
}

// fn_802E85E0 - Eof
bool AsyncFile::Eof() {
    return (fpos == size);
}

// fn_802E85F8 - Fail
bool AsyncFile::Fail() {
    return failed;
}

// fn_802E8600 - Size
unsigned int AsyncFile::Size() {
    return size;
}

// fn_802E8608 - UncompressedSize
unsigned int AsyncFile::UncompressedSize() {
    return size_uncompressed;
}

// fn_802E8030 - ReadDone
int AsyncFile::ReadDone(int &a) {
    int temp_r28;

    if (failed != 0) {
        a = 0;
        return 1;
    }
    if (unk28 != 0 && unk30 == 0) {
        a = unk34;
        return 1;
    }
    if (_ReadDone() == 0) {
        a = unk34;
        return 0;
    }

    if (unk28 == 0)
        return 1;

    if (unk1c + unk30 > lbl_808517C8[0]) {
        temp_r28 = lbl_808517C8[0] - unk1c;
        memcpy(unk2c, unk28 + unk1c, temp_r28);
        unk34 += temp_r28;
        unk1c = lbl_808517C8[0];
        fpos += temp_r28;
        unk30 -= temp_r28;
        unk2c += temp_r28;
        FillBuffer(); // FillBuffer
        a = unk34;
        return 0;
    }
    memcpy(unk2c, unk28 + unk1c, unk30);
    unk34 += unk30;
    unk1c += unk30;
    fpos += unk30;
    unk30 = 0;
    a = unk34;
    return 1;
}

// fn_802E81AC
int AsyncFile::V_Unk15(int *a) {
    if (unk28 != 0)
        return 1;
    return V_Unk21();
}


// fn_802E85D0
unsigned int Minimum(unsigned int a, unsigned int b) {
    return (b < a) ? b : a;
}


// FillBuffer
void AsyncFile::FillBuffer() {
    if ((failed == 0) && (unk4 & 2)) {
        if (unk1c != lbl_808517C8[0]) {
            V_Unk21();
        }
        Minimum((unsigned int)(fpos), (unsigned int)(lbl_808517C8[0]));
        _SeekToTell();
        unk1c = 0;
    }
}

// fn_802E7E10 - swaps endians for an int
unsigned int SwapDataWord(int i) {
    unsigned int ui = i;
    return ui >> 0x18 | ui << 0x18 | ui >> 8 & 0xFF00 | (ui & 0xFF00) << 8;
}
