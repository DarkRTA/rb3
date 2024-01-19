#include "file.hpp"
#include "file_ops.hpp"
#include "arkfile.hpp"
#include "archive.hpp"
#include "blockmgr.hpp"
#include "asynctask.hpp"

int File::sOpenCount[4];


// fn_802E73DC
File::File() {
    sOpenCount[0]++;
}

// fn_802E738C
File::~File() {
    sOpenCount[0]--;
}


// fn_802E780C
String File::Filename() {
    return String();
}

// fn_802E7818
int File::V_Unk15(int *a) {
    *a = 0;
    return 1;
}

extern Archive *TheArchive;

// fn_802E72CC
ArkFile::ArkFile(const char *c, int a)
    : unk18(0), unk1c(0), fpos(0), unk24(0), unk2c(1), fname(c) {
    if (!TheArchive->GetFileInfo(
            FileMakePath(".", (char *)c, nullptr), unk4, unk8, size, size_uncompressed
        )
        || (a & 4)) {
        unk24 = 1;
    }
}

extern BlockMgr TheBlockMgr;

// fn_802E73FC
ArkFile::~ArkFile() {
    if (unk18 > 0) {
        TheBlockMgr.KillBlockRequests(this);
    }
}

// fn_802E748C
int ArkFile::Read(void *c, int a) {
    if (ReadAsync(c, a) == 0)
        return 0;
    int sp8 = -1;
    while (ReadDone(sp8) == 0)
        ;
    return sp8;
}

// fn_802E7500
bool ArkFile::ReadAsync(void *c, int a) {
    // this one's gross, i don't wanna do it
}

int ArkFile::V_Unk5(void *a, int b) {
    return 0;
}

unsigned int ArkFile::Seek(int offset, int mode) {
    switch (mode) {
    case 0:
        fpos = offset;
        break;
    case 1:
        fpos += offset;
        break;
    case 2:
        fpos = size + offset;
        break;
    default:
        break;
    }
    return fpos;
}

unsigned int ArkFile::Tell() {
    return fpos;
}

// void ArkFile::Flush(){ }

bool ArkFile::Eof() {
    return (size - fpos) == 0;
}

// fn_802E7810
String ArkFile::Filename() {
    return fname;
}

// fn_802E7748
bool ArkFile::Fail() {
    return (unk24 != 0);
}

// fn_802E7758
unsigned int ArkFile::Size() {
    return size;
}

// fn_802E7760
unsigned int ArkFile::UncompressedSize() {
    return size_uncompressed;
}

// fn_802E7790
int ArkFile::ReadDone(int &a) {
    TheBlockMgr.Poll();
    a = unk1c;
    return (unk18 == 0);
}

extern void fn_802EB6E4(int *, int, int, int);

// fn_802E77E4
int ArkFile::V_Unk16(int *a) {
    // fn_802EB6E4(a, unk4, unkc + fpos, unkc + fpos);
}

// fn_802E7768
void ArkFile::TaskDone(int a) {
    unk18--;
    unk1c += a;
    fpos += a;
}