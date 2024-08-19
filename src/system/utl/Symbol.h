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
        else return Null();
    }

    // methods found in RB2
    bool operator==(const Symbol & s) const {
        return mStr == s.mStr;
    }

    bool operator!=(const Symbol & s) const {
        return mStr != s.mStr;
    }

    bool operator!=(const char * cc) const {
        return !(*this == cc);
    }

    // Symbol *operator=(const Symbol & s){
    //     mStr = s.mStr;
    // }
    const char *Str() const { return mStr; }

    static void UploadDebugStats();
    static void PreInit(int, int);
    static void Init();
    static void Terminate();

    int GetIntVal(); // https://decomp.me/scratch/sxK01
    RETAIL_DONT_INLINE_CLASS bool Null() const { return mStr == gNullStr; }
};

const char* SymbolCacheLookup(const char*);

inline void Interp(const Symbol& s1, const Symbol& s2, float f, Symbol& s3){
    s3 = (f < 1.0f) ? s1 : s2;
}

#endif
