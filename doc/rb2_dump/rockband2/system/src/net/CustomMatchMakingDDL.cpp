/*
    Compile unit: C:\rockband2\system\src\net\CustomMatchMakingDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805213C0 -> 0x80521A30
*/
class CustomMatchMakingClient : public ClientProtocol {
    // total size: 0x38
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
// Range: 0x805213C0 -> 0x805216EC
unsigned char CustomMatchMakingClient::CallCustomFind(class CustomMatchMakingClient * const this /* r23 */, class ProtocolCallContext * pContext /* r24 */, const int & queryID /* r25 */, const int & gameMode /* r26 */, const unsigned char & ranked /* r27 */, const class qList & props /* r28 */, const class ResultRange & resultRange /* r29 */, class qList * lstGatherings /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

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
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    class AnyObjectHolder _M_data; // offset 0x8, size 0x8
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
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x805216EC -> 0x80521A30
void CustomMatchMakingClient::ExtractCallSpecificResults(class Message * pMessage /* r29 */, class ProtocolCallContext * pContext /* r26 */) {
    // Local variables
    unsigned short uiRMCID; // r4

    // References
    // -> class AnyObjectAdapter * s_pAnyAdapter;
    // -> struct [anonymous] __vt__Q26Quazal53AnyObjectHolder<Q26Quazal9Gathering,Q26Quazal6String>;
}

class _DDL_Gathering : public RootObject {
    // total size: 0x28
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int m_idMyself; // offset 0x4, size 0x4
    unsigned int m_pidOwner; // offset 0x8, size 0x4
    unsigned int m_pidHost; // offset 0xC, size 0x4
    unsigned short m_uiMinParticipants; // offset 0x10, size 0x2
    unsigned short m_uiMaxParticipants; // offset 0x12, size 0x2
    unsigned int m_uiParticipationPolicy; // offset 0x14, size 0x4
    unsigned int m_uiPolicyArgument; // offset 0x18, size 0x4
    unsigned int m_uiFlags; // offset 0x1C, size 0x4
    unsigned int m_uiState; // offset 0x20, size 0x4
    class String m_strDescription; // offset 0x24, size 0x4
};
class Gathering : public _DDL_Gathering {
    // total size: 0x28
};
class Holder {
    // total size: 0x4
    class Gathering * m_ptr; // offset 0x0, size 0x4
};
class AnyObjectHolder : public Holder {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x4, size 0x4
};
struct {
    // total size: 0xC
} __vt__Q26Quazal53AnyObjectHolder<Q26Quazal9Gathering,Q26Quazal6String>; // size: 0xC, address: 0x80904978
struct {
    // total size: 0x8
} __RTTI__Q26Quazal53AnyObjectHolder<Q26Quazal9Gathering,Q26Quazal6String>; // size: 0x8, address: 0x809049D0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal27Holder<Q26Quazal9Gathering>; // size: 0x8, address: 0x80904A00
struct {
    // total size: 0x64
} __vt__Q26Quazal23CustomMatchMakingClient; // size: 0x64, address: 0x80904A08
struct {
    // total size: 0x8
} __RTTI__Q26Quazal23CustomMatchMakingClient; // size: 0x8, address: 0x80904AC0
struct {
    // total size: 0x14
} __vt__Q26Quazal11ResultRange; // size: 0x14, address: 0x80904AC8
struct {
    // total size: 0x8
} __RTTI__Q26Quazal11ResultRange; // size: 0x8, address: 0x80904B08
struct {
    // total size: 0x8
} __RTTI__Q26Quazal16_DDL_ResultRange; // size: 0x8, address: 0x80904B38
class AnyObjectAdapter {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class AnyObjectAdapter * s_pAnyAdapter; // size: 0x4, address: 0x80A53C60

