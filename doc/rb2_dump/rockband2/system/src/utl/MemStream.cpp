/*
    Compile unit: C:\rockband2\system\src\utl\MemStream.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80619AA0 -> 0x80619D80
*/
// Range: 0x80619AA0 -> 0x80619B08
void * MemStream::MemStream(class MemStream * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__9MemStream;
}

// Range: 0x80619B08 -> 0x80619B88
void MemStream::ReadImpl(class MemStream * const this /* r30 */, int bytes /* r31 */) {}

// Range: 0x80619B88 -> 0x80619C8C
void MemStream::WriteImpl(class MemStream * const this /* r31 */, void * data /* r28 */, int bytes /* r29 */) {
    // Local variables
    int capacity; // r4
}

// Range: 0x80619C8C -> 0x80619D08
void MemStream::SeekImpl() {
    // Local variables
    int i; // r4
}

// Range: 0x80619D08 -> 0x80619D80
void MemStream::Compact(class MemStream * const this /* r30 */) {}

struct {
    // total size: 0x2C
} __vt__9MemStream; // size: 0x2C, address: 0x8092DFA0
struct {
    // total size: 0x8
} __RTTI__9MemStream; // size: 0x8, address: 0x8092DFE8

