/*
    Compile unit: C:\rockband2\band2\src\net_band\RBEntitiesDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8021A490 -> 0x8021BAE4
*/
class RBEntitiesClient : public ClientProtocol {
    // total size: 0x38
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class RBBand : public _DDL_RBBand {
    // total size: 0x28
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class RBCharacter : public _DDL_RBCharacter {
    // total size: 0x28
};
class qList : public list, public RootObject {
    // total size: 0x8
};
// Range: 0x8021A490 -> 0x8021A704
unsigned char RBEntitiesClient::CallUpdateCharacter(class RBEntitiesClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const class RBGuid & charGuid /* r27 */, const class RBCharacter & charData /* r28 */, const signed char & checkFlags /* r29 */, signed char * returnCode /* r30 */, unsigned int * charID /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r24

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021A704 -> 0x8021A950
unsigned char RBEntitiesClient::CallUpdateCharSecData(class RBEntitiesClient * const this /* r27 */, class ProtocolCallContext * pContext /* r28 */, const class RBGuid & charGuid /* r29 */, const unsigned int & cash /* r30 */, unsigned int * charID /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r26

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021A950 -> 0x8021AD24
unsigned char RBEntitiesClient::CallUpdateBand(class RBEntitiesClient * const this /* r22 */, class ProtocolCallContext * pContext /* r23 */, const class RBGuid & bandGuid /* r24 */, const class RBBand & bandData /* r25 */, const signed char & checkFlags /* r26 */, const class qList & members /* r27 */, const class qList & topScores /* r28 */, signed char * returnCode /* r29 */, unsigned int * bandID /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x78
    class Message msgRequest; // r1+0x80
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021AD24 -> 0x8021AF70
unsigned char RBEntitiesClient::CallIsLegalCharacterName(class RBEntitiesClient * const this /* r27 */, class ProtocolCallContext * pContext /* r28 */, const class String & charName /* r29 */, const signed char & checkFlags /* r30 */, signed char * returnCode /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r26

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021AF70 -> 0x8021B1BC
unsigned char RBEntitiesClient::CallIsLegalBandName(class RBEntitiesClient * const this /* r27 */, class ProtocolCallContext * pContext /* r28 */, const class String & bandName /* r29 */, const signed char & checkFlags /* r30 */, signed char * returnCode /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r26

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021B1BC -> 0x8021B408
unsigned char RBEntitiesClient::CallIsLegalBandMotto(class RBEntitiesClient * const this /* r27 */, class ProtocolCallContext * pContext /* r28 */, const class String & motto /* r29 */, const signed char & checkFlags /* r30 */, signed char * returnCode /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r26

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021B408 -> 0x8021B6CC
unsigned char RBEntitiesClient::CallGetBand(class RBEntitiesClient * const this /* r22 */, class ProtocolCallContext * pContext /* r23 */, const class RBGuid & bandGuid /* r24 */, class RBBand * bandData /* r25 */, class DateTime * createDate /* r26 */, unsigned int * fans /* r27 */, unsigned int * careerScore /* r28 */, class RBPlatformGuid * ownerInfo /* r29 */, class qList * members /* r30 */, class qList * topScores /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r21

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021B6CC -> 0x8021B9A0
unsigned char RBEntitiesClient::CallGetPresenceInfo(class RBEntitiesClient * const this /* r28 */, class ProtocolCallContext * pContext /* r29 */, const class qList & memlist /* r30 */, class qList * onlinelist /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r27

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

class _List_node : public _List_node_base {
    // total size: 0x1C
public:
    class RBGuid _M_data; // offset 0x8, size 0x14
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
class RBBandTopScore : public _DDL_RBBandTopScore {
    // total size: 0x14
};
class _List_node : public _List_node_base {
    // total size: 0x1C
public:
    class RBBandTopScore _M_data; // offset 0x8, size 0x14
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
class RBBandMember : public _DDL_RBBandMember {
    // total size: 0x30
};
class _List_node : public _List_node_base {
    // total size: 0x38
public:
    class RBBandMember _M_data; // offset 0x8, size 0x30
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
class _List_node : public _List_node_base {
    // total size: 0x18
public:
    class RBPlatformGuid _M_data; // offset 0x8, size 0x10
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
// Range: 0x8021B9A0 -> 0x8021BAE4
void RBEntitiesClient::ExtractCallSpecificResults(class Message * pMessage /* r30 */, class ProtocolCallContext * pContext /* r31 */) {
    // Local variables
    unsigned short uiRMCID; // r3
}

struct {
    // total size: 0x64
} __vt__Q26Quazal16RBEntitiesClient; // size: 0x64, address: 0x808AE4BC
struct {
    // total size: 0x8
} __RTTI__Q26Quazal16RBEntitiesClient; // size: 0x8, address: 0x808AE568
struct {
    // total size: 0xC
} __vt__Q26Quazal14RBPresenceInfo; // size: 0xC, address: 0x808AE570
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14RBPresenceInfo; // size: 0x8, address: 0x808AE5A8
struct {
    // total size: 0xC
} __vt__Q26Quazal19_DDL_RBPresenceInfo; // size: 0xC, address: 0x808AE5B0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal19_DDL_RBPresenceInfo; // size: 0x8, address: 0x808AE5E8
struct {
    // total size: 0xC
} __vt__Q26Quazal12RBBandMember; // size: 0xC, address: 0x808AE5F0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal12RBBandMember; // size: 0x8, address: 0x808AE628
struct {
    // total size: 0xC
} __vt__Q26Quazal17_DDL_RBBandMember; // size: 0xC, address: 0x808AE630
struct {
    // total size: 0x8
} __RTTI__Q26Quazal17_DDL_RBBandMember; // size: 0x8, address: 0x808AE668
struct {
    // total size: 0xC
} __vt__Q26Quazal14RBBandTopScore; // size: 0xC, address: 0x808AE670
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14RBBandTopScore; // size: 0x8, address: 0x808AE6A8
struct {
    // total size: 0xC
} __vt__Q26Quazal19_DDL_RBBandTopScore; // size: 0xC, address: 0x808AE6B0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal19_DDL_RBBandTopScore; // size: 0x8, address: 0x808AE6E8
struct {
    // total size: 0xC
} __vt__Q26Quazal6RBBand; // size: 0xC, address: 0x808AE6F0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal6RBBand; // size: 0x8, address: 0x808AE720
struct {
    // total size: 0xC
} __vt__Q26Quazal11_DDL_RBBand; // size: 0xC, address: 0x808AE728
struct {
    // total size: 0x8
} __RTTI__Q26Quazal11_DDL_RBBand; // size: 0x8, address: 0x808AE758
struct {
    // total size: 0xC
} __vt__Q26Quazal11RBCharacter; // size: 0xC, address: 0x808AE760
struct {
    // total size: 0x8
} __RTTI__Q26Quazal11RBCharacter; // size: 0x8, address: 0x808AE798
struct {
    // total size: 0xC
} __vt__Q26Quazal16_DDL_RBCharacter; // size: 0xC, address: 0x808AE7A0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal16_DDL_RBCharacter; // size: 0x8, address: 0x808AE7D8
struct {
    // total size: 0xC
} __vt__Q26Quazal6RBGuid; // size: 0xC, address: 0x808AE7E0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal6RBGuid; // size: 0x8, address: 0x808AE810
struct {
    // total size: 0xC
} __vt__Q26Quazal11_DDL_RBGuid; // size: 0xC, address: 0x808AE818
struct {
    // total size: 0x8
} __RTTI__Q26Quazal11_DDL_RBGuid; // size: 0x8, address: 0x808AE848

