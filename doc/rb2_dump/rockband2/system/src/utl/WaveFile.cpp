/*
    Compile unit: C:\rockband2\system\src\utl\WaveFile.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8062539C -> 0x8062571C
*/
// Range: 0x8062539C -> 0x806253BC
static unsigned char CompareCuePoints() {}

// Range: 0x806253BC -> 0x8062541C
void * WaveFile::WaveFile(class WaveFile * const this /* r31 */) {}

// Range: 0x8062541C -> 0x80625524
void * WaveFile::~WaveFile(class WaveFile * const this /* r30 */) {}

class vector : protected _Vector_base {
    // total size: 0xC
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
struct CuePoint {
    // total size: 0x8
    int mFrame; // offset 0x0, size 0x4
    int mID; // offset 0x4, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct CuePoint * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct CuePoint * _M_start; // offset 0x0, size 0x4
    struct CuePoint * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
struct Label {
    // total size: 0x10
    class String mName; // offset 0x0, size 0xC
    int mID; // offset 0xC, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Label * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Label * _M_start; // offset 0x0, size 0x4
    struct Label * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x80625524 -> 0x806255D0
void WaveFile::ReadNumSamples(class WaveFile * const this /* r30 */) {
    // Local variables
    const class ChunkHeader * chunk; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ChunkID kWaveDataChunkID;
}

// Range: 0x806255D0 -> 0x80625664
class IListChunk & WaveFile::PrepareToProvideData(class WaveFile * const this /* r31 */) {
    // Local variables
    const class ChunkHeader * chunk; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ChunkID kWaveDataChunkID;
}

// Range: 0x80625664 -> 0x806256C0
void * WaveFileData::WaveFileData(class WaveFileData * const this /* r30 */, class WaveFile & file /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12WaveFileData;
}

// Range: 0x806256C0 -> 0x8062571C
void * WaveFileData::~WaveFileData(class WaveFileData * const this /* r30 */) {}

struct {
    // total size: 0x2C
} __vt__12WaveFileData; // size: 0x2C, address: 0x8092F888
struct {
    // total size: 0x8
} __RTTI__12WaveFileData; // size: 0x8, address: 0x8092F8D8
struct {
    // total size: 0x8
} __RTTI__PQ222@unnamed@WaveFile_cpp@5Label; // size: 0x8, address: 0x8092F938
struct {
    // total size: 0x8
} __RTTI__PQ222@unnamed@WaveFile_cpp@8CuePoint; // size: 0x8, address: 0x8092F968
struct {
    // total size: 0x8
} __RTTI__P14WaveFileMarker; // size: 0x8, address: 0x8092F988

