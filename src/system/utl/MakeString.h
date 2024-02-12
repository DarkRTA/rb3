#ifndef UTL_MAKESTRING_H
#define UTL_MAKESTRING_H
#include "obj/Data.h"
#include "utl/Str.h"

class FormatString {
public:
    char *format;
    char *unk4;
    int unk8;
    char unk_arr[0x800];
    char *unk80c;
    int formatType; // 0 = integer, 1 = string, 2 = float, 3 = unknown

    FormatString();
    FormatString(const char *);
    void InitArray(const char *, bool);
    void UpdateType();
    char *Str();
    FormatString &operator<<(unsigned int);
    FormatString &operator<<(int);
    FormatString &operator<<(const String &);
    FormatString &operator<<(const DataNode &);
    FormatString &operator<<(float);
    FormatString &operator<<(const char *);
    FormatString &operator<<(Symbol);
};

const char *MakeString(const char *);

template <class T> const char *MakeString(const char *c, T t) {
    FormatString fs(c);
    fs << t;
    return fs.Str();
}

template <class T1, class T2> const char *MakeString(const char *c, T1 t1, T2 t2) {
    FormatString fs(c);
    fs << t1 << t2;
    return fs.Str();
}

template <class T1, class T2, class T3>
const char *MakeString(const char *c, T1 t1, T2 t2, T3 t3) {
    FormatString fs(c);
    fs << t1 << t2 << t3;
    return fs.Str();
}

#endif

// enum Type {
//     kInt = 0,
//     kStr = 1,
//     kFloat = 2,
//     kNone = 3,
// };
// class FormatString {
//     // total size: 0x814
//     char * mBuf; // offset 0x0, size 0x4
//     int mBufSize; // offset 0x4, size 0x4
//     char mFmtBuf[2048]; // offset 0x8, size 0x800
//     char * mFmt; // offset 0x808, size 0x4
//     char * mFmtEnd; // offset 0x80C, size 0x4
//     enum Type mType; // offset 0x810, size 0x4
// };
