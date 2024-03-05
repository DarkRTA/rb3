#include "utl/StringTable.h"

StringTable::StringTable(int i) : mCurChar(0), mCurBuf(-1) {
    if(i != 0) AddBuf(i);
}

StringTable::~StringTable(){
    Clear();
}

void StringTable::Clear(){
    mBuffers.clear();
}
