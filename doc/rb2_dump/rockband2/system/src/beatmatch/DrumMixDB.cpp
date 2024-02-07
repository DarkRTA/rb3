/*
    Compile unit: C:\rockband2\system\src\beatmatch\DrumMixDB.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802D94B0 -> 0x802D97A4
*/
class DrumMixDB {
    // total size: 0x20
    class vector mMixLists; // offset 0x0, size 0xC
    class vector mCopy; // offset 0xC, size 0x14
};
// Range: 0x802D94B0 -> 0x802D94D8
void * DrumMixDB::DrumMixDB() {}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TickedInfoCollection * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TickedInfoCollection * * _M_start; // offset 0x0, size 0x4
    class TickedInfoCollection * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x802D94D8 -> 0x802D9704
void * DrumMixDB::~DrumMixDB(class DrumMixDB * const this /* r28 */) {
    // Local variables
    int i; // r30
}

struct {
    // total size: 0x8
} __RTTI__PUi; // size: 0x8, address: 0x808CAC30
// Range: 0x802D9704 -> 0x802D97A4
class TickedInfoCollection & DrumMixDB::GetMixList(const class DrumMixDB * const this /* r30 */, int track /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__P19TickedInfo<6String>; // size: 0x8, address: 0x808CACA8
struct {
    // total size: 0x8
} __RTTI__PP29TickedInfoCollection<6String>; // size: 0x8, address: 0x808CACD0

