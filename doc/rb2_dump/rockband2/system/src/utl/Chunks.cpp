/*
    Compile unit: C:\rockband2\system\src\utl\Chunks.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80606714 -> 0x8060736C
*/
// Range: 0x80606714 -> 0x80606818
void ChunkHeader::Read(class ChunkHeader * const this /* r30 */, class BinStream & iBinStream /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ChunkID kRiffChunkID;
    // -> class ChunkID kListChunkID;
}

// Range: 0x80606818 -> 0x80606974
void * IDataChunk::IDataChunk(class IDataChunk * const this /* r29 */, class IListChunk & iParent /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__10IDataChunk;
}

// Range: 0x80606974 -> 0x806069F8
void * IDataChunk::~IDataChunk(class IDataChunk * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10IDataChunk;
}

// Range: 0x806069F8 -> 0x80606B68
void IDataChunk::SeekImpl(class IDataChunk * const this /* r28 */, int iOffset /* r29 */, enum SeekType iSeekType /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80606B68 -> 0x80606BCC
int IDataChunk::Tell(class IDataChunk * const this /* r31 */) {
    // Local variables
    int absolute; // r0
}

// Range: 0x80606BCC -> 0x80606C58
void IDataChunk::ReadImpl(class IDataChunk * const this /* r29 */, void * oBuffer /* r30 */, int iLen /* r31 */) {
    // Local variables
    int curMarker; // r0
}

// Range: 0x80606C58 -> 0x80606DD4
void * IListChunk::IListChunk(class IListChunk * const this /* r26 */, class BinStream & iBaseBinStream /* r27 */, unsigned char iHasListHeader /* r28 */) {
    // Local variables
    int pos; // r28
    int len; // r0

    // References
    // -> class ChunkID kListChunkID;
}

// Range: 0x80606DD4 -> 0x80606EB4
void * IListChunk::IListChunk(class IListChunk * const this /* r30 */) {}

// Range: 0x80606EB4 -> 0x80606F1C
void * IListChunk::~IListChunk(class IListChunk * const this /* r30 */) {}

// Range: 0x80606F1C -> 0x80606FAC
void IListChunk::Init(class IListChunk * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80606FAC -> 0x80607034
void IListChunk::Reset(class IListChunk * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80607034 -> 0x806070AC
class ChunkHeader * IListChunk::CurSubChunkHeader(const class IListChunk * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806070AC -> 0x806071D4
class ChunkHeader * IListChunk::Next(class IListChunk * const this /* r31 */) {
    // Local variables
    int subLen; // r30

    // References
    // -> class ChunkID kMidiTrackChunkID;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806071D4 -> 0x8060729C
class ChunkHeader * IListChunk::Next(class IListChunk * const this /* r30 */, class ChunkID & iID /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060729C -> 0x80607304
void IListChunk::Lock(class IListChunk * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80607304 -> 0x8060736C
void IListChunk::UnLock(class IListChunk * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x2C
} __vt__10IDataChunk; // size: 0x2C, address: 0x8092BBD8
struct {
    // total size: 0x8
} __RTTI__10IDataChunk; // size: 0x8, address: 0x8092BC20

