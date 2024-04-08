#ifndef UTL_SYMBOL_H
#define UTL_SYMBOL_H
#include <string.h>

#define STR_TO_SYM(str) *reinterpret_cast<Symbol*>(&str)

extern const char* gNullStr;

class Symbol {
public:
    const char *mStr;
    Symbol() : mStr(gNullStr) { }
    Symbol(const char *); // ctor pulled from gdrb

    bool operator<(const Symbol& s) const {
        return mStr < s.mStr;
    }

    // found in GDRB
    bool operator==(const char* cc) const {
        if(cc) return strcmp(mStr, cc) == 0;
        else return cc == gNullStr;
    }

    // methods found in RB2
    bool operator==(const Symbol & s) const {
        return mStr == s.mStr;
    }
    bool operator!=(const Symbol & s);
    bool operator!=(const char *);
    // Symbol *operator=(const Symbol & s){
    //     mStr = s.mStr;
    // }
    const char *Str() const { return mStr; }
    static void PreInit(int, int);
    void Init();
    void Terminate();
    int GetIntVal(); // https://decomp.me/scratch/sxK01
    bool IsNull() const { return mStr == gNullStr; }
};

#endif
