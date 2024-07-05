#include "utl/StringTable.h"
#include "os/Debug.h"

StringTable::StringTable(int i) : mCurChar(0), mCurBuf(-1) {
    if(i != 0) AddBuf(i);
}

void StringTable::AddBuf(int i){
    Buf buf;
    buf.size = i;
    buf.chars = (char*)_MemAlloc(i, 0);
    mCurChar = buf.chars;
    MILO_ASSERT(mCurChar, 0x1F);
    mCurBuf = mBuffers.size();
    mBuffers.push_back(buf);
}

StringTable::~StringTable(){
    Clear();
}

void StringTable::Clear(){
    int i = 0;
    int size = mBuffers.size();
    for(; i < size; i++){
        _MemFree(mBuffers[i].chars);
    }
    mBuffers.clear();
}

void StringTable::Reserve(int i){
    int size = Size();
    if(size < i){
        if(mCurBuf < 0){
            AddBuf(i);
        }
        else {
            Buf buf;
            buf.size = (i - size) + 0x40;
            buf.chars = (char*)_MemAlloc(buf.size, 0);
            mBuffers.push_back(buf);
        }
    }
}

const char* StringTable::Add(const char*){
    
}

int StringTable::UsedSize() const {
    int size = 0;
    for(int i = 0; i < mBuffers.size(); i++){
        if(i == mCurBuf) break;
        if(mBuffers[i].size != 0){
            size += mBuffers[i].size;
        }
    }
    return size;
}

int StringTable::Size() const {
    int size = 0;
    for(int i = 0; i < mBuffers.size(); i++){
        size += mBuffers[i].size;
    }
    return size;
}
