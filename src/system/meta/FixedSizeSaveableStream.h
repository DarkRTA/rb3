#ifndef META_FIXEDSIZESAVEABLESTREAM_H
#define META_FIXEDSIZESAVEABLESTREAM_H
#include "utl/BufStream.h"
#include <unordered_map>

class FixedSizeSaveableStream : public BufStream {
public:
    FixedSizeSaveableStream(void*, int, bool);
    virtual ~FixedSizeSaveableStream();
    virtual void FinishWrite(){}
    virtual void FinishStream(){}

    bool HasSymbol(Symbol) const;
    int GetID(Symbol) const;
    int AddSymbol(Symbol);
    Symbol GetSymbol(int) const;

    std::unordered_map<Symbol, int> m_mapSymbolToID;
    std::unordered_map<int, Symbol> m_mapIDToSymbol;
    int m_iCurrentID;
    int m_iTableOffset;
};

#endif