/*
    Compile unit: C:\rockband2\system\src\synth\StreamNull.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80590F9C -> 0x80591288
*/
class StreamNull : public Stream {
    // total size: 0x70
    class VarTimer mTimer; // offset 0x8, size 0x40
    class FaderGroup mFaders; // offset 0x48, size 0x18
    class vector mChannelFaders; // offset 0x60, size 0xC
};
// Range: 0x80590F9C -> 0x805910C0
void * StreamNull::StreamNull(class StreamNull * const this /* r30 */, float startMs /* f31 */) {
    // Local variables
    class FaderGroup * * itr; // r31

    // References
    // -> struct [anonymous] __vt__10StreamNull;
}

class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class FaderGroup * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class FaderGroup * * _M_start; // offset 0x0, size 0x4
    class FaderGroup * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x805910C0 -> 0x805911F0
void * StreamNull::~StreamNull(class StreamNull * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10StreamNull;
}

// Range: 0x805911F0 -> 0x805911F8
void StreamNull::Play() {}

// Range: 0x805911F8 -> 0x80591200
void StreamNull::Stop() {}

// Range: 0x80591200 -> 0x80591214
unsigned char StreamNull::IsPlaying() {}

// Range: 0x80591214 -> 0x80591228
unsigned char StreamNull::IsFinished() {}

// Range: 0x80591228 -> 0x80591270
void StreamNull::Resync(class StreamNull * const this /* r31 */, float startMs /* f31 */) {}

// Range: 0x80591270 -> 0x80591278
float StreamNull::GetTime() {}

// Range: 0x80591278 -> 0x80591280
void StreamNull::SetSpeed() {}

// Range: 0x80591280 -> 0x80591288
float StreamNull::GetSpeed() {}

struct {
    // total size: 0xA8
} __vt__10StreamNull; // size: 0xA8, address: 0x8091FA40
struct {
    // total size: 0x8
} __RTTI__10StreamNull; // size: 0x8, address: 0x8091FB00
struct {
    // total size: 0x8
} __RTTI__PP10FaderGroup; // size: 0x8, address: 0x8091FB18
struct _OKToMemCpy {
    // total size: 0x1
};

