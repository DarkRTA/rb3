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
    char* mBuf;
    char* mNextBuf;
    int mBufSize;
    char mFmtBuf[2048];
    char *mFmt;
    Type mType;
    char *mFmtEnd;

    FormatString();
    FormatString(const char *);
    void InitializeWithFmt(const char*, bool);
    void UpdateType();
    
    FormatString &operator<<(void*);
    FormatString &operator<<(unsigned int);
    FormatString &operator<<(unsigned long);
    FormatString &operator<<(long);
    FormatString &operator<<(unsigned long long);
    FormatString &operator<<(int);
    FormatString &operator<<(const DataNode &);
    FormatString &operator<<(const char *);
    FormatString &operator<<(float);
    FormatString &operator<<(double);
    FormatString &operator<<(const String &);
    FormatString &operator<<(Symbol);

    const char *Str();
};

void InitMakeString();
bool MakeStringInitted();
void TerminateMakeString();

inline const char *MakeString(const char * c){
    FormatString fs(c);
    return fs.Str();
}

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

template <class T1, class T2, class T3, class T4>
const char *MakeString(const char *c, T1 t1, T2 t2, T3 t3, T4 t4) {
    FormatString fs(c);
    fs << t1 << t2 << t3 << t4;
    return fs.Str();
}

template <class T1, class T2, class T3, class T4, class T5>
const char *MakeString(const char *c, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) {
    FormatString fs(c);
    fs << t1 << t2 << t3 << t4 << t5;
    return fs.Str();
}

#endif
