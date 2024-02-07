/*
    Compile unit: C:\rockband2\system\src\os\AsyncFileHolmes.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CDBE0 -> 0x805CDD84
*/
class AsyncFileHolmes : public AsyncFile {
    // total size: 0x40
    int mFileHandle; // offset 0x3C, size 0x4
};
// Range: 0x805CDBE0 -> 0x805CDC24
void * AsyncFileHolmes::AsyncFileHolmes(class AsyncFileHolmes * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15AsyncFileHolmes;
}

// Range: 0x805CDC24 -> 0x805CDC7C
unsigned int AsyncFileHolmes::_Open(class AsyncFileHolmes * const this /* r31 */) {
    // Local variables
    unsigned int size; // r1+0x8
}

// Range: 0x805CDC7C -> 0x805CDD10
int AsyncFileHolmes::_Write(class AsyncFileHolmes * const this /* r29 */, void * buf /* r30 */, int bytes /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805CDD10 -> 0x805CDD54
void AsyncFileHolmes::_SeekToTell(class AsyncFileHolmes * const this /* r31 */) {}

// Range: 0x805CDD54 -> 0x805CDD68
void AsyncFileHolmes::_ReadAsync() {}

// Range: 0x805CDD68 -> 0x805CDD6C
unsigned char AsyncFileHolmes::_ReadDone() {}

// Range: 0x805CDD6C -> 0x805CDD84
void AsyncFileHolmes::_Close() {}

struct {
    // total size: 0x50
} __vt__15AsyncFileHolmes; // size: 0x50, address: 0x80926CF0
struct {
    // total size: 0x8
} __RTTI__15AsyncFileHolmes; // size: 0x8, address: 0x80926D68

