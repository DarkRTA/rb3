/*
    Compile unit: C:\rockband2\system\src\utl\FileStream.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80608D70 -> 0x8060944C
*/
// Range: 0x80608D70 -> 0x80608E38
void * FileStream::FileStream(class FileStream * const this /* r29 */, const char * file /* r30 */, enum FileType t /* r31 */) {
    // Local variables
    int mode; // r31

    // References
    // -> struct [anonymous] __vt__10FileStream;
}

// Range: 0x80608E38 -> 0x80608EA0
void * FileStream::FileStream(class FileStream * const this /* r30 */, class File * file /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10FileStream;
}

// Range: 0x80608EA0 -> 0x80608F58
void * FileStream::~FileStream(class FileStream * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10FileStream;
}

// Range: 0x80608F58 -> 0x80608FE4
void FileStream::ReadImpl(class FileStream * const this /* r29 */, void * data /* r30 */, int bytes /* r31 */) {}

// Range: 0x80608FE4 -> 0x8060903C
void FileStream::WriteImpl(class FileStream * const this /* r30 */, int bytes /* r31 */) {}

// Range: 0x8060903C -> 0x806090B0
void FileStream::Flush(class FileStream * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806090B0 -> 0x80609178
void FileStream::SeekImpl(class FileStream * const this /* r29 */, int offset /* r30 */, enum SeekType t /* r31 */) {
    // Local variables
    int d[3]; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80609178 -> 0x806091EC
int FileStream::Tell(class FileStream * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806091EC -> 0x80609260
unsigned char FileStream::Eof(class FileStream * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80609260 -> 0x80609268
unsigned char FileStream::Fail() {}

// Range: 0x80609268 -> 0x806092C8
void FileStream::DeleteChecksum(class FileStream * const this /* r30 */) {}

// Range: 0x806092C8 -> 0x8060935C
void FileStream::StartChecksum(class FileStream * const this /* r30 */) {}

// Range: 0x8060935C -> 0x8060944C
unsigned char FileStream::ValidateChecksum(class FileStream * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x2C
} __vt__10FileStream; // size: 0x2C, address: 0x8092C13C
struct {
    // total size: 0x8
} __RTTI__10FileStream; // size: 0x8, address: 0x8092C180

