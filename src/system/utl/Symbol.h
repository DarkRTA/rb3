#ifndef UTL_SYMBOL_H
#define UTL_SYMBOL_H

#define STR_TO_SYM(str) *reinterpret_cast<Symbol*>(&str)

extern const char* gNullStr;

class Symbol {
public:
    const char *mStr;
    Symbol() : mStr(gNullStr) { }
    Symbol(const char *); // ctor pulled from gdrb

    // methods found in RB2
    bool operator==(const Symbol &); // fn_8000FCA4
    bool operator!=(const char *);
    // Symbol *operator=(const Symbol & s){
    //     mStr = s.mStr;
    // }
    char *Str() const;
    static void PreInit(int, int);
    void Init();
    void Terminate();
    int GetIntVal(); // https://decomp.me/scratch/sxK01
    bool IsNull(); // fn_800103CC
};

#endif
