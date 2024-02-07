#ifndef RB3_MAKESTRING_HPP
#define RB3_MAKESTRING_HPP
#include "string.hpp"
#include "Data.h"

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
