#ifndef UTL_MAKESTRING_H
#define UTL_MAKESTRING_H
#include "obj/Data.h"
#include "utl/Symbol.h"
#include "utl/Str.h"

class FormatString {
public:
    enum Type {
        kInt = 0,
        kStr = 1,
        kFloat = 2,
        kNone = 3,
    };
    char *mBuf;
    int mBufSize;
    char mFmtBuf[2048];
    char *mFmt;
    char *mFmtEnd;
    Type mType;

    FormatString();
    FormatString(const char *);
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
