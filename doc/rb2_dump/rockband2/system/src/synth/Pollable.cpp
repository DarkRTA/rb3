/*
    Compile unit: C:\rockband2\system\src\synth\Pollable.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805811A8 -> 0x80581440
*/
class list sPollables; // size: 0x8, address: 0x80983418
// Range: 0x805811A8 -> 0x805811D8
void * SynthPollable::SynthPollable() {
    // References
    // -> class list sPollables;
    // -> struct [anonymous] __vt__13SynthPollable;
}

// Range: 0x805811D8 -> 0x80581238
void * SynthPollable::~SynthPollable(class SynthPollable * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__13SynthPollable;
}

// Range: 0x80581238 -> 0x805812E4
void SynthPollable::StartPolling(class SynthPollable * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<P13SynthPollable>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sPollables;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<P13SynthPollable>; // size: 0x8, address: 0x8091DA40
// Range: 0x805812E4 -> 0x80581374
void SynthPollable::CancelPolling(class SynthPollable * const this /* r29 */) {
    // References
    // -> class list sPollables;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80581374 -> 0x805813E4
void SynthPollable::PollAll() {
    // Local variables
    struct _List_iterator itr; // r1+0x14

    // References
    // -> class list sPollables;
}

struct {
    // total size: 0x10
} __vt__13SynthPollable; // size: 0x10, address: 0x8091DA48
// Range: 0x805813E4 -> 0x80581440
static void __sinit_\Pollable_cpp() {
    // References
    // -> class list sPollables;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class SynthPollable * _M_data; // offset 0x8, size 0x4
};

