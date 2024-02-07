/*
    Compile unit: C:\rockband2\system\src\beatmatch\SlotChannelMapping.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802F93D0 -> 0x802FA1F8
*/
// Range: 0x802F93D0 -> 0x802F9498
class SlotChannelMapping * NewSlotChannelMapping(class SubmixCollection * submixes /* r31 */, class DataArray * cfg /* r30 */) {}

class SingleSlotChannelMapping : public SlotChannelMapping {
    // total size: 0x8
    int mChannel; // offset 0x4, size 0x4
};
// Range: 0x802F9498 -> 0x802F94AC
void * SingleSlotChannelMapping::SingleSlotChannelMapping() {
    // References
    // -> struct [anonymous] __vt__24SingleSlotChannelMapping;
}

// Range: 0x802F94AC -> 0x802F9524
void SingleSlotChannelMapping::FillChannelList(const class SingleSlotChannelMapping * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x802F9524 -> 0x802F959C
void SingleSlotChannelMapping::FillChannelList(const class SingleSlotChannelMapping * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

class MassChannelMapping : public SlotChannelMapping {
    // total size: 0xC
    class list mChannels; // offset 0x4, size 0x8
};
// Range: 0x802F959C -> 0x802F9690
void * MassChannelMapping::MassChannelMapping(class MassChannelMapping * const this /* r28 */, class DataArray * cfg /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__18MassChannelMapping;
}

// Range: 0x802F9690 -> 0x802F97BC
void MassChannelMapping::FillChannelList() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x802F97BC -> 0x802F98E8
void MassChannelMapping::FillChannelList() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x802F98E8 -> 0x802F9948
int MassChannelMapping::ChannelBitfield() {
    // Local variables
    int val; // r6
    struct _List_iterator it; // r1+0x18
}

class MultiChannelMapping : public SlotChannelMapping {
    // total size: 0x10
    class vector mChannelsPerSlot; // offset 0x4, size 0xC
};
// Range: 0x802F9948 -> 0x802FA078
void * MultiChannelMapping::MultiChannelMapping(class MultiChannelMapping * const this /* r26 */, class SubmixCollection * submixes /* r24 */, class DataArray * cfg /* r27 */) {
    // Local variables
    int base_index; // [invalid]
    class Submix * submix; // r30
    int i; // r29
    class list & channels; // r0
    struct _List_iterator j; // r1+0xE0
    int i; // r28
    class DataNode & node; // r0
    class DataArray * channels; // r24
    int c; // r25

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__19MultiChannelMapping;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class list * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class list * _M_start; // offset 0x0, size 0x4
    class list * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x802FA078 -> 0x802FA1F8
void MultiChannelMapping::FillChannelList(const class MultiChannelMapping * const this /* r29 */, class list & channels /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x1C
} __vt__19MultiChannelMapping; // size: 0x1C, address: 0x808CD650
struct {
    // total size: 0x8
} __RTTI__19MultiChannelMapping; // size: 0x8, address: 0x808CD690
struct {
    // total size: 0x1C
} __vt__18MassChannelMapping; // size: 0x1C, address: 0x808CD698
struct {
    // total size: 0x8
} __RTTI__18MassChannelMapping; // size: 0x8, address: 0x808CD6D8
struct {
    // total size: 0x1C
} __vt__24SingleSlotChannelMapping; // size: 0x1C, address: 0x808CD6E0
struct {
    // total size: 0x8
} __RTTI__24SingleSlotChannelMapping; // size: 0x8, address: 0x808CD728
struct {
    // total size: 0x1C
} __vt__18SlotChannelMapping; // size: 0x1C, address: 0x808CD730
struct {
    // total size: 0x8
} __RTTI__18SlotChannelMapping; // size: 0x8, address: 0x808CD760
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std40list<i,Q211stlpmtx_std15StlNodeAlloc<i>>; // size: 0x8, address: 0x808CD7B0
struct _IsPOD {
    // total size: 0x1
};

