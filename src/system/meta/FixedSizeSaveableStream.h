#ifndef META_FIXEDSIZESAVEABLESTREAM_H
#define META_FIXEDSIZESAVEABLESTREAM_H
#include "utl/BufStream.h"
#include <hash_map>

class FixedSizeSaveableStream : public BufStream {
public:
    FixedSizeSaveableStream(void*, int, bool);
    virtual ~FixedSizeSaveableStream();
    virtual bool FinishWrite(){ return 0; }
    virtual bool FinishStream(){ return 0; }

    bool HasSymbol(Symbol) const;
    int GetID(Symbol) const;
    int AddSymbol(Symbol);
    Symbol GetSymbol(int) const;

    std::hash_map<Symbol, int> m_mapSymbolToID;
    std::hash_map<int, Symbol> m_mapIDToSymbol;
    int m_iCurrentID;
    int m_iTableOffset;
};

#endif