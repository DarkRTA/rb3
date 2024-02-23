#ifndef UTL_SYMBOL_H
#define UTL_SYMBOL_H

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

    // methods found in RB2
    bool operator==(const Symbol & s) const {
        return mStr == s.mStr;
    }
    bool operator!=(const char *);
    // Symbol *operator=(const Symbol & s){
    //     mStr = s.mStr;
    // }
    const char *Str() const { return mStr; }
    static void PreInit(int, int);
    void Init();
    void Terminate();
    int GetIntVal(); // https://decomp.me/scratch/sxK01
    bool IsNull(){ return mStr == gNullStr; }
};

#endif
