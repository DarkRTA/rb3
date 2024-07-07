#include "meta/FixedSizeSaveableStream.h"

FixedSizeSaveableStream::FixedSizeSaveableStream(void* v, int i, bool b) : BufStream(v, i, b), m_iCurrentID(0), m_iTableOffset(0) {

}

FixedSizeSaveableStream::~FixedSizeSaveableStream(){

}

void FixedSizeSaveableStream::InitializeTable(){
    m_mapIDToSymbol.clear();
    m_mapSymbolToID.clear();
    m_iTableOffset = Tell();
}

std::map<Symbol, int>& FixedSizeSaveableStream::GetSymbolToIDMap(){
    return m_mapSymbolToID;
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