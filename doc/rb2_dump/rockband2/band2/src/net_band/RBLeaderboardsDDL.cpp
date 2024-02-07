/*
    Compile unit: C:\rockband2\band2\src\net_band\RBLeaderboardsDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8021D8D8 -> 0x80220148
*/
class RBLeaderboardsClient : public ClientProtocol {
    // total size: 0x38
};
// Range: 0x8021D8D8 -> 0x8021DB6C
unsigned char RBLeaderboardsClient::CallGetSoloHighScoresByPlayer(class RBLeaderboardsClient * const this /* r24 */, class ProtocolCallContext * pContext /* r25 */, const unsigned int & principalID /* r26 */, const signed char & roleID /* r27 */, const class String & songName /* r28 */, const signed short & playersAround /* r29 */, const signed short & offset /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r23

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021DB6C -> 0x8021DDE8
unsigned char RBLeaderboardsClient::CallGetSoloHighScoresByRankRange(class RBLeaderboardsClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const signed char & roleID /* r27 */, const class String & songName /* r28 */, const unsigned int & topRank /* r29 */, const unsigned int & bottomRank /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r24

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021DDE8 -> 0x8021E0E4
unsigned char RBLeaderboardsClient::CallGetSoloHighScoresByFriends(class RBLeaderboardsClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const class qList & friends /* r27 */, const signed char & roleID /* r28 */, const class String & songName /* r29 */, class qList * results /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021E0E4 -> 0x8021E368
unsigned char RBLeaderboardsClient::CallGetSoloCareerHighScoresByPlayer(class RBLeaderboardsClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const unsigned int & principalID /* r27 */, const signed char & roleID /* r28 */, const signed short & playersAround /* r29 */, const signed short & offset /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r24

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021E368 -> 0x8021E5D4
unsigned char RBLeaderboardsClient::CallGetSoloCareerHighScoresByRankRange(class RBLeaderboardsClient * const this /* r26 */, class ProtocolCallContext * pContext /* r27 */, const signed char & roleID /* r28 */, const unsigned int & topRank /* r29 */, const unsigned int & bottomRank /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r25

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021E5D4 -> 0x8021E8C0
unsigned char RBLeaderboardsClient::CallGetSoloCareerHighScoresByFriends(class RBLeaderboardsClient * const this /* r26 */, class ProtocolCallContext * pContext /* r27 */, const class qList & friends /* r28 */, const signed char & roleID /* r29 */, class qList * results /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021E8C0 -> 0x8021EB34
unsigned char RBLeaderboardsClient::CallGetBandHighScoresByBand(class RBLeaderboardsClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const class RBGuid & bandGuid /* r27 */, const class String & songName /* r28 */, const signed short & playersAround /* r29 */, const signed short & offset /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r24

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021EB34 -> 0x8021ED98
unsigned char RBLeaderboardsClient::CallGetBandHighScoresByRankRange(class RBLeaderboardsClient * const this /* r26 */, class ProtocolCallContext * pContext /* r27 */, const class String & songName /* r28 */, const unsigned int & topRank /* r29 */, const unsigned int & bottomRank /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r25

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021ED98 -> 0x8021F07C
unsigned char RBLeaderboardsClient::CallGetBandHighScoresByFriends(class RBLeaderboardsClient * const this /* r26 */, class ProtocolCallContext * pContext /* r27 */, const class qList & friends /* r28 */, const class String & songName /* r29 */, class qList * results /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021F07C -> 0x8021F2E0
unsigned char RBLeaderboardsClient::CallGetBandCareerHighScoresByBand(class RBLeaderboardsClient * const this /* r26 */, class ProtocolCallContext * pContext /* r27 */, const class RBGuid & bandGuid /* r28 */, const signed short & playersAround /* r29 */, const signed short & offset /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r25

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021F2E0 -> 0x8021F534
unsigned char RBLeaderboardsClient::CallGetBandCareerHighScoresByRankRange(class RBLeaderboardsClient * const this /* r27 */, class ProtocolCallContext * pContext /* r28 */, const unsigned int & topRank /* r29 */, const unsigned int & bottomRank /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r26

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021F534 -> 0x8021F808
unsigned char RBLeaderboardsClient::CallGetBandCareerHighScoresByFriends(class RBLeaderboardsClient * const this /* r28 */, class ProtocolCallContext * pContext /* r29 */, const class qList & friends /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r27

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021F808 -> 0x8021FA6C
unsigned char RBLeaderboardsClient::CallGetBandFansByBand(class RBLeaderboardsClient * const this /* r26 */, class ProtocolCallContext * pContext /* r27 */, const class RBGuid & bandGuid /* r28 */, const signed short & playersAround /* r29 */, const signed short & offset /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r25

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021FA6C -> 0x8021FCC0
unsigned char RBLeaderboardsClient::CallGetBandFansByRankRange(class RBLeaderboardsClient * const this /* r27 */, class ProtocolCallContext * pContext /* r28 */, const unsigned int & topRank /* r29 */, const unsigned int & bottomRank /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r26

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8021FCC0 -> 0x8021FF94
unsigned char RBLeaderboardsClient::CallGetBandFansByFriends(class RBLeaderboardsClient * const this /* r28 */, class ProtocolCallContext * pContext /* r29 */, const class qList & friends /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r27

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

class qList : public list, public RootObject {
    // total size: 0x8
};
class RBSkillResults : public _DDL_RBSkillResults {
    // total size: 0x20
};
class _List_node : public _List_node_base {
    // total size: 0x28
public:
    class RBSkillResults _M_data; // offset 0x8, size 0x20
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
// Range: 0x8021FF94 -> 0x80220148
void RBLeaderboardsClient::ExtractCallSpecificResults(class Message * pMessage /* r30 */, class ProtocolCallContext * pContext /* r31 */) {
    // Local variables
    unsigned short uiRMCID; // r3
}

class _DDL_RBSkillResults : public RootObject {
    // total size: 0x20
public:
    void * __vptr$; // offset 0x0, size 0x4
    class String mPlayerName; // offset 0x4, size 0x4
    long long mGuid; // offset 0x8, size 0x8
    unsigned int mPrincipalID; // offset 0x10, size 0x4
    unsigned int mRank; // offset 0x14, size 0x4
    unsigned int mSkill; // offset 0x18, size 0x4
};
struct {
    // total size: 0x64
} __vt__Q26Quazal20RBLeaderboardsClient; // size: 0x64, address: 0x808AE898
struct {
    // total size: 0x8
} __RTTI__Q26Quazal20RBLeaderboardsClient; // size: 0x8, address: 0x808AE948
struct {
    // total size: 0xC
} __vt__Q26Quazal14RBSkillResults; // size: 0xC, address: 0x808AE950
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14RBSkillResults; // size: 0x8, address: 0x808AE988
struct {
    // total size: 0xC
} __vt__Q26Quazal19_DDL_RBSkillResults; // size: 0xC, address: 0x808AE990
struct {
    // total size: 0x8
} __RTTI__Q26Quazal19_DDL_RBSkillResults; // size: 0x8, address: 0x808AE9C8
struct {
    // total size: 0xC
} __vt__Q26Quazal13RBBandResults; // size: 0xC, address: 0x808AE9D0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal13RBBandResults; // size: 0x8, address: 0x808AEA08
struct {
    // total size: 0xC
} __vt__Q26Quazal18_DDL_RBBandResults; // size: 0xC, address: 0x808AEA10
struct {
    // total size: 0x8
} __RTTI__Q26Quazal18_DDL_RBBandResults; // size: 0x8, address: 0x808AEA48
struct {
    // total size: 0xC
} __vt__Q26Quazal13RBSoloResults; // size: 0xC, address: 0x808AEA50
struct {
    // total size: 0x8
} __RTTI__Q26Quazal13RBSoloResults; // size: 0x8, address: 0x808AEA88
struct {
    // total size: 0xC
} __vt__Q26Quazal18_DDL_RBSoloResults; // size: 0xC, address: 0x808AEA90
struct {
    // total size: 0x8
} __RTTI__Q26Quazal18_DDL_RBSoloResults; // size: 0x8, address: 0x808AEAC8

