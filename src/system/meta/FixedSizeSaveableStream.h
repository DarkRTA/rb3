#ifndef META_FIXEDSIZESAVEABLESTREAM_H
#define META_FIXEDSIZESAVEABLESTREAM_H
#include "utl/BufStream.h"
#include <map>

class FixedSizeSaveableStream : public BufStream {
public:
    FixedSizeSaveableStream(void*, int, bool);
    virtual ~FixedSizeSaveableStream();
    virtual bool FinishWrite(){ return 0; }
    virtual bool FinishStream(){ return 0; }

    bool HasSymbol(Symbol) const;
    bool HasID(int) const;
    int GetID(Symbol) const;
    int AddSymbol(Symbol);
    Symbol GetSymbol(int) const;
    void InitializeTable();
    int ReadInt();
    float ReadFloat();
    void SetSymbolID(Symbol, int);
    void SaveTable();
    int GetSymbolTableSize(int);
    void LoadTable(int);

    std::map<Symbol, int>& GetSymbolToIDMap();

    std::map<Symbol, int> m_mapSymbolToID; // 0x30
    std::map<int, Symbol> m_mapIDToSymbol; // 0x48
    int m_iCurrentID; // 0x60
    int m_iTableOffset; // 0x64
};

#endif