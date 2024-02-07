/*
    Compile unit: C:\rockband2\system\src\synth\MidiSynth.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8057EEB4 -> 0x8057F010
*/
class MidiSynth {
    // total size: 0xC
    class vector mChannels; // offset 0x0, size 0xC
};
// Range: 0x8057EEB4 -> 0x8057F010
void * MidiSynth::MidiSynth(class MidiSynth * const this /* r31 */) {}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class MidiChannel * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class MidiChannel * _M_start; // offset 0x0, size 0x4
    class MidiChannel * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct {
    // total size: 0x8
} __RTTI__P11MidiChannel; // size: 0x8, address: 0x8091D9B0

