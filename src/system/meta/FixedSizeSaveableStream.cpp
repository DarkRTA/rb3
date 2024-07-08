#include "meta/FixedSizeSaveableStream.h"
#include "meta/FixedSizeSaveable.h"

FixedSizeSaveableStream::FixedSizeSaveableStream(void* v, int i, bool b) : BufStream(v, i, b), m_iCurrentID(0), m_iTableOffset(0) {

}

FixedSizeSaveableStream::~FixedSizeSaveableStream(){

}

// fn_8050FAFC
void FixedSizeSaveableStream::InitializeTable(){
    m_mapIDToSymbol.clear();
    m_mapSymbolToID.clear();
    m_iTableOffset = Tell();
    FixedSizeSaveable::SaveSymbolTable(*this, FixedSizeSaveable::GetMaxSymbols(), 0x36);
}

void FixedSizeSaveableStream::SaveTable(){
    int start = Tell();
    Seek(m_iTableOffset, BinStream::kSeekBegin);
    FixedSizeSaveable::SaveSymbolTable(*this, FixedSizeSaveable::GetMaxSymbols(), 0x36);
    Seek(start, BinStream::kSeekBegin);
}

int FixedSizeSaveableStream::GetSymbolTableSize(int){
    return FixedSizeSaveable::GetMaxSymbols() * 0x36 + 4;
}

void FixedSizeSaveableStream::LoadTable(int){
    m_mapIDToSymbol.clear();
    m_mapSymbolToID.clear();
    FixedSizeSaveable::LoadSymbolTable(*this, FixedSizeSaveable::GetMaxSymbols(), 0x36);
}

std::map<Symbol, int>& FixedSizeSaveableStream::GetSymbolToIDMap(){
    return m_mapSymbolToID;
}

bool FixedSizeSaveableStream::HasSymbol(Symbol s) const {
    return GetID(s) != -1;
}

// fn_8050FC70
bool FixedSizeSaveableStream::HasID(int i) const {
    Symbol s = GetSymbol(i);
    return s != "";
}

int FixedSizeSaveableStream::GetID(Symbol s) const {
    std::map<Symbol, int>::const_iterator it = m_mapSymbolToID.find(s);
    if(it != m_mapSymbolToID.end()) return it->second;
    else return -1;
}

Symbol FixedSizeSaveableStream::GetSymbol(int i) const {
    std::map<int, Symbol>::const_iterator it = m_mapIDToSymbol.find(i);
    if(it != m_mapIDToSymbol.end()) return it->second;
    else return "";
}

int FixedSizeSaveableStream::AddSymbol(Symbol i_symSymbol){
    MILO_ASSERT(!HasSymbol( i_symSymbol ), 0x83);
    m_iCurrentID++;
    MILO_ASSERT(!HasID( m_iCurrentID ), 0x86);
    m_mapSymbolToID[i_symSymbol] = m_iCurrentID;
    m_mapIDToSymbol[m_iCurrentID] = i_symSymbol;
    return m_iCurrentID;
}

void FixedSizeSaveableStream::SetSymbolID(Symbol s, int i){
    m_mapSymbolToID[s] = i;
    m_mapIDToSymbol[i] = s;
}

int FixedSizeSaveableStream::ReadInt(){
    int i = 0;
    *this >> i;
    return i;
}

float FixedSizeSaveableStream::ReadFloat(){
    float f = 0.0f;
    *this >> f;
    return f;
}