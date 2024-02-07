/*
    Compile unit: C:\rockband2\band2\src\net_band\LeaderboardResults.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80214E78 -> 0x80215BEC
*/
// Range: 0x80214E78 -> 0x80214EE8
void * LeaderboardResultList::~LeaderboardResultList(class LeaderboardResultList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__21LeaderboardResultList;
}

// Range: 0x80214EE8 -> 0x80214F90
void LeaderboardResultList::Clear(class LeaderboardResultList * const this /* r31 */) {}

class Plugin : public RootObject {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    void * m_hLibrary; // offset 0x4, size 0x4
};
class _DDL_RBSoloResults : public RootObject {
    // total size: 0x20
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mPlayerName; // offset 0x4, size 0x4
    long long mGuid; // offset 0x8, size 0x8
    unsigned int mPrincipalID; // offset 0x10, size 0x4
    signed char mDiffID; // offset 0x14, size 0x1
    unsigned int mRank; // offset 0x18, size 0x4
    unsigned int mScore; // offset 0x1C, size 0x4
};
class RBSoloResults : public _DDL_RBSoloResults {
    // total size: 0x20
};
class _DDL_RBGuid : public RootObject {
    // total size: 0x14
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int mGuid0; // offset 0x4, size 0x4
    unsigned int mGuid1; // offset 0x8, size 0x4
    unsigned int mGuid2; // offset 0xC, size 0x4
    unsigned int mGuid3; // offset 0x10, size 0x4
};
class RBGuid : public _DDL_RBGuid {
    // total size: 0x14
};
class _DDL_RBBandResults : public RootObject {
    // total size: 0x28
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mBandName; // offset 0x4, size 0x4
    class RBGuid mGuid; // offset 0x8, size 0x14
    unsigned int mBandID; // offset 0x1C, size 0x4
    unsigned int mRank; // offset 0x20, size 0x4
    unsigned int mScore; // offset 0x24, size 0x4
};
class RBBandResults : public _DDL_RBBandResults {
    // total size: 0x28
};
// Range: 0x80214F90 -> 0x80215078
void * BandResultRow::BandResultRow(class BandResultRow * const this /* r29 */, class RBBandResults * result /* r30 */) {
    // Local variables
    class HxGuid guid; // r1+0x18

    // References
    // -> struct [anonymous] __vt__13BandResultRow;
    // -> struct [anonymous] __vt__20LeaderboardResultRow;
}

// Range: 0x80215078 -> 0x80215144
void * BandResultRow::BandResultRow(class BandResultRow * const this /* r26 */, class String & bandName /* r27 */, unsigned long long score /* r29 */, const class HxGuid & guid /* r30 */) {
    // References
    // -> struct [anonymous] __vt__13BandResultRow;
    // -> struct [anonymous] __vt__20LeaderboardResultRow;
}

class qList : public list, public RootObject {
    // total size: 0x8
};
class RBPlayerResultQList {
    // total size: 0x8
public:
    class qList mData; // offset 0x0, size 0x8
};
// Range: 0x80215144 -> 0x802151FC
void * PlayerResultList::PlayerResultList(class PlayerResultList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__16PlayerResultList;
    // -> struct [anonymous] __vt__21LeaderboardResultList;
    // -> struct [anonymous] __vt__9Updatable;
}

class _List_node : public _List_node_base {
    // total size: 0x28
public:
    class RBSoloResults _M_data; // offset 0x8, size 0x20
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
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
// Range: 0x802151FC -> 0x802152A4
void * PlayerResultList::~PlayerResultList(class PlayerResultList * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__16PlayerResultList;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x802152A4 -> 0x802153A8
void PlayerResultList::Update(class PlayerResultList * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std35_List_node<P20LeaderboardResultRow>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std35_List_node<P20LeaderboardResultRow>; // size: 0x8, address: 0x808ADB38
// Range: 0x802153A8 -> 0x80215458
void PlayerResultList::Update(class PlayerResultList * const this /* r29 */, class vector & data /* r30 */) {
    // Local variables
    class PlayerResultRow * * it; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std35_List_node<P20LeaderboardResultRow>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80215458 -> 0x80215490
void PlayerResultList::SpecializedClear(class PlayerResultList * const this /* r31 */) {}

// Range: 0x80215490 -> 0x80215590
unsigned char RowHasHigherScore(const class LeaderboardResultRow * lhs /* r28 */, const class LeaderboardResultRow * rhs /* r29 */) {}

class qList : public list, public RootObject {
    // total size: 0x8
};
class RBBandResultQList {
    // total size: 0x8
public:
    class qList mData; // offset 0x0, size 0x8
};
// Range: 0x80215590 -> 0x80215648
void * BandResultList::BandResultList(class BandResultList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__14BandResultList;
    // -> struct [anonymous] __vt__21LeaderboardResultList;
    // -> struct [anonymous] __vt__9Updatable;
}

class _List_node : public _List_node_base {
    // total size: 0x30
public:
    class RBBandResults _M_data; // offset 0x8, size 0x28
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
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
// Range: 0x80215648 -> 0x802156EC
void * BandResultList::~BandResultList(class BandResultList * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__14BandResultList;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x802156EC -> 0x802157F0
void BandResultList::Update(class BandResultList * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std35_List_node<P20LeaderboardResultRow>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x802157F0 -> 0x802158A0
void BandResultList::Update(class BandResultList * const this /* r29 */, class vector & data /* r30 */) {
    // Local variables
    class BandResultRow * * it; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std35_List_node<P20LeaderboardResultRow>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x802158A0 -> 0x802158D8
void BandResultList::SpecializedClear(class BandResultList * const this /* r31 */) {}

class _DDL_RBPlatformGuid : public RootObject {
    // total size: 0x10
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mName; // offset 0x4, size 0x4
    long long mGuid; // offset 0x8, size 0x8
};
class RBPlatformGuid : public _DDL_RBPlatformGuid {
    // total size: 0x10
};
class _DDL_RBPresenceInfo : public RootObject {
    // total size: 0x20
public:
    void * __vptr$; // offset 0x0, size 0x4
    class RBPlatformGuid mPlatformGuid; // offset 0x8, size 0x10
    unsigned char mOnline; // offset 0x18, size 0x1
};
class RBPresenceInfo : public _DDL_RBPresenceInfo {
    // total size: 0x20
};
// Range: 0x802158D8 -> 0x8021593C
void * PresenceResultRow::PresenceResultRow(class PresenceResultRow * const this /* r30 */, class RBPresenceInfo * result /* r31 */) {}

class qList : public list, public RootObject {
    // total size: 0x8
};
class RBPresenceResultQList {
    // total size: 0x8
public:
    class qList mData; // offset 0x0, size 0x8
};
// Range: 0x8021593C -> 0x802159D4
void * PresenceResultList::PresenceResultList(class PresenceResultList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__18PresenceResultList;
}

class _List_node : public _List_node_base {
    // total size: 0x28
public:
    class RBPresenceInfo _M_data; // offset 0x8, size 0x20
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
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
// Range: 0x802159D4 -> 0x80215A70
void * PresenceResultList::~PresenceResultList(class PresenceResultList * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__18PresenceResultList;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80215A70 -> 0x80215BAC
void PresenceResultList::Update(class PresenceResultList * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std31_List_node<17PresenceResultRow>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80215BAC -> 0x80215BEC
void PresenceResultList::Clear(class PresenceResultList * const this /* r31 */) {}

struct {
    // total size: 0x14
} __vt__18PresenceResultList; // size: 0x14, address: 0x808ADB64
struct {
    // total size: 0x8
} __RTTI__18PresenceResultList; // size: 0x8, address: 0x808ADB98
struct {
    // total size: 0x30
} __vt__14BandResultList; // size: 0x30, address: 0x808ADBA0
struct {
    // total size: 0x8
} __RTTI__14BandResultList; // size: 0x8, address: 0x808ADBF8
struct {
    // total size: 0x1C
} __vt__13BandResultRow; // size: 0x1C, address: 0x808ADC00
struct {
    // total size: 0x8
} __RTTI__13BandResultRow; // size: 0x8, address: 0x808ADC38
struct {
    // total size: 0x34
} __vt__16PlayerResultList; // size: 0x34, address: 0x808ADC40
struct {
    // total size: 0x8
} __RTTI__16PlayerResultList; // size: 0x8, address: 0x808ADCA0
struct {
    // total size: 0x14
} __vt__21LeaderboardResultList; // size: 0x14, address: 0x808ADCA8
struct {
    // total size: 0x8
} __RTTI__21LeaderboardResultList; // size: 0x8, address: 0x808ADCD8
struct {
    // total size: 0x14
} __vt__9Updatable; // size: 0x14, address: 0x808ADCE0
struct {
    // total size: 0x8
} __RTTI__9Updatable; // size: 0x8, address: 0x808ADD00

