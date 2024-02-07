/*
    Compile unit: C:\rockband2\system\src\synth\MidiChannel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8057ED70 -> 0x8057EDB8
*/
class MidiChannel {
    // total size: 0x1C
    int mInst; // offset 0x0, size 0x4
    int mBank; // offset 0x4, size 0x4
    float mVolume; // offset 0x8, size 0x4
    float mPan; // offset 0xC, size 0x4
    float mTranspose; // offset 0x10, size 0x4
    class list mPlayingNotes; // offset 0x14, size 0x8
};
// Range: 0x8057ED70 -> 0x8057EDB8
void * MidiChannel::MidiChannel() {}

class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0x28
public:
    struct Note _M_data; // offset 0x8, size 0x20
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct Note {
    // total size: 0x20
    int mNoteNum; // offset 0x0, size 0x4
    float mVolume; // offset 0x4, size 0x4
    class vector mSamples; // offset 0x8, size 0xC
    class vector mTransposes; // offset 0x14, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
struct DummySample {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct DummySample * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct DummySample * * _M_start; // offset 0x0, size 0x4
    struct DummySample * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PPQ211MidiChannel11DummySample; // size: 0x8, address: 0x8091D960
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std32_List_node<Q211MidiChannel4Note>; // size: 0x8, address: 0x8091D998
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};

