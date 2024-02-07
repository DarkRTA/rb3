/*
    Compile unit: C:\rockband2\band2\src\net_band\RBBotbDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8023137C -> 0x8023344C
*/
// Range: 0x8023137C -> 0x802315C8
unsigned char RBBotbClient::CallGetBattleById(class RBBotbClient * const this /* r27 */, class ProtocolCallContext * pContext /* r28 */, const unsigned int & battleID /* r29 */, const class String & localeName /* r30 */, class RBBotbBattleDetails * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r26

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x802315C8 -> 0x8023181C
unsigned char RBBotbClient::CallGetOpenBattles(class RBBotbClient * const this /* r26 */, class ProtocolCallContext * pContext /* r27 */, const class RBGuid & bandGuid /* r28 */, const class String & showIn /* r29 */, const class String & localeName /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r25

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8023181C -> 0x80231B20
unsigned char RBBotbClient::CallGetOpenBattleResultsByBand(class RBBotbClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const unsigned int & battleID /* r27 */, const class RBGuid & bandGuid /* r28 */, const class qList & principalIDs /* r29 */, class RBBotbBattleResultsByBandInfo * results /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80231B20 -> 0x80231E44
unsigned char RBBotbClient::CallGetBattlesByBand(class RBBotbClient * const this /* r23 */, class ProtocolCallContext * pContext /* r24 */, const class RBGuid & bandGuid /* r25 */, const unsigned int & howFarBack /* r26 */, const unsigned char & byQuantity /* r27 */, const class String & localeName /* r28 */, const class qList & principalIDs /* r29 */, class qList * results /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80231E44 -> 0x80232148
unsigned char RBBotbClient::CallPlayBattle(class RBBotbClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const unsigned int & battleID /* r27 */, const class RBGuid & bandGuid /* r28 */, const class qList & principalIDs /* r29 */, class RBBotbPlayBattleResponse * results /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80232148 -> 0x802323C4
unsigned char RBBotbClient::CallGetBattleResultsByBand(class RBBotbClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const unsigned int & battleID /* r27 */, const class RBGuid & bandGuid /* r28 */, const unsigned int & bandsAround /* r29 */, const unsigned int & offset /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r24

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x802323C4 -> 0x80232630
unsigned char RBBotbClient::CallGetBattleResultsByRankRange(class RBBotbClient * const this /* r26 */, class ProtocolCallContext * pContext /* r27 */, const unsigned int & battleID /* r28 */, const unsigned int & topRank /* r29 */, const unsigned int & bottomRank /* r30 */, class qList * results /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r25

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80232630 -> 0x80232934
unsigned char RBBotbClient::CallGetBattleResultsByFriends(class RBBotbClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const unsigned int & battleID /* r27 */, const class RBGuid & bandGuid /* r28 */, const class qList & principalIDs /* r29 */, class qList * results /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80232934 -> 0x80232C68
unsigned char RBBotbClient::CallRecordBattleScore(class RBBotbClient * const this /* r23 */, class ProtocolCallContext * pContext /* r24 */, const unsigned int & battleID /* r25 */, const class RBGuid & bandGuid /* r26 */, const unsigned int & score /* r27 */, const unsigned int & stars /* r28 */, const class qList & principalIDs /* r29 */, class RBBotbRecordBattleResponse * results /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80232C68 -> 0x80232FCC
unsigned char RBBotbClient::CallGetDailyNews(class RBBotbClient * const this /* r21 */, class ProtocolCallContext * pContext /* r22 */, const class RBGuid & bandGuid /* r23 */, const class String & localeName /* r24 */, const class DateTime & lastTime /* r25 */, const class qList & principalIDs /* r26 */, const class String & lastCookies /* r27 */, class DateTime * curTime /* r28 */, class String * newCookies /* r29 */, class qList * results /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x48
    class Message msgRequest; // r1+0x50
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80232FCC -> 0x802332B8
unsigned char RBBotbClient::CallUpdateFriendList(class RBBotbClient * const this /* r26 */, class ProtocolCallContext * pContext /* r27 */, const unsigned int & principalID /* r28 */, const class qList & friends /* r29 */, unsigned char * result /* r30 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x40
    class Message msgRequest; // r1+0x48
    class Message * pMsg; // r31

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x802332B8 -> 0x8023344C
void RBBotbClient::ExtractCallSpecificResults(class Message * pMessage /* r30 */, class ProtocolCallContext * pContext /* r31 */) {
    // Local variables
    unsigned short uiRMCID; // r3
}

struct {
    // total size: 0x64
} __vt__Q26Quazal12RBBotbClient; // size: 0x64, address: 0x808B0368
struct {
    // total size: 0x8
} __RTTI__Q26Quazal12RBBotbClient; // size: 0x8, address: 0x808B0410
struct {
    // total size: 0xC
} __vt__Q26Quazal14RBBotbNewsItem; // size: 0xC, address: 0x808B0418
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14RBBotbNewsItem; // size: 0x8, address: 0x808B0450
struct {
    // total size: 0xC
} __vt__Q26Quazal19_DDL_RBBotbNewsItem; // size: 0xC, address: 0x808B0458
struct {
    // total size: 0x8
} __RTTI__Q26Quazal19_DDL_RBBotbNewsItem; // size: 0x8, address: 0x808B0490
struct {
    // total size: 0xC
} __vt__Q26Quazal15RBBotbBattleRow; // size: 0xC, address: 0x808B0498
struct {
    // total size: 0x8
} __RTTI__Q26Quazal15RBBotbBattleRow; // size: 0x8, address: 0x808B04D8
struct {
    // total size: 0xC
} __vt__Q26Quazal20_DDL_RBBotbBattleRow; // size: 0xC, address: 0x808B04E0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal20_DDL_RBBotbBattleRow; // size: 0x8, address: 0x808B0518
struct {
    // total size: 0xC
} __vt__Q26Quazal20RBBotbCityWithBattle; // size: 0xC, address: 0x808B0520
struct {
    // total size: 0x8
} __RTTI__Q26Quazal20RBBotbCityWithBattle; // size: 0x8, address: 0x808B0560
struct {
    // total size: 0xC
} __vt__Q26Quazal25_DDL_RBBotbCityWithBattle; // size: 0xC, address: 0x808B0568
struct {
    // total size: 0x8
} __RTTI__Q26Quazal25_DDL_RBBotbCityWithBattle; // size: 0x8, address: 0x808B05A8
struct {
    // total size: 0xC
} __vt__Q26Quazal26RBBotbBattleParticipatedIn; // size: 0xC, address: 0x808B05B0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal26RBBotbBattleParticipatedIn; // size: 0x8, address: 0x808B05F8
struct {
    // total size: 0xC
} __vt__Q26Quazal31_DDL_RBBotbBattleParticipatedIn; // size: 0xC, address: 0x808B0600
struct {
    // total size: 0x8
} __RTTI__Q26Quazal31_DDL_RBBotbBattleParticipatedIn; // size: 0x8, address: 0x808B0648
struct {
    // total size: 0xC
} __vt__Q26Quazal20RBBotbOpenBattleInfo; // size: 0xC, address: 0x808B0650
struct {
    // total size: 0x8
} __RTTI__Q26Quazal20RBBotbOpenBattleInfo; // size: 0x8, address: 0x808B0690
struct {
    // total size: 0xC
} __vt__Q26Quazal25_DDL_RBBotbOpenBattleInfo; // size: 0xC, address: 0x808B0698
struct {
    // total size: 0x8
} __RTTI__Q26Quazal25_DDL_RBBotbOpenBattleInfo; // size: 0x8, address: 0x808B06D8

