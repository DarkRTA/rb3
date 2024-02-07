/*
    Compile unit: C:\rockband2\band2\src\net_band\RBBotbDDL.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8023344C -> 0x80235494
*/
// Range: 0x8023344C -> 0x802335F4
void RBBotbClient::ProtoReturn_GetBattleById(class Message * pMsg /* r29 */) {
    // Local variables
    int iArgIndex; // r0
    class RBBotbBattleDetails * pReturnLocation; // r0
    int i; // r30
    class RBBotbBattleDetails oDummyVar[1]; // r1+0x18
    int i; // r30

    // References
    // -> struct [anonymous] __vt__Q26Quazal19RBBotbBattleDetails;
    // -> struct [anonymous] __vt__Q26Quazal24_DDL_RBBotbBattleDetails;
}

// Range: 0x802335F4 -> 0x8023396C
void RBBotbClient::ProtoReturn_GetOpenBattles(class Message * pMsg /* r30 */) {
    // Local variables
    int iArgIndex; // r0
    class qList * pReturnLocation; // r0
    int i; // r31
    class qList oDummyVar[1]; // r1+0x28
    int i; // r27

    // References
    // -> struct [anonymous] __vt__Q26Quazal20RBBotbOpenBattleInfo;
    // -> struct [anonymous] __vt__Q26Quazal25_DDL_RBBotbOpenBattleInfo;
}

// Range: 0x8023396C -> 0x80233A3C
void RBBotbClient::ProtoReturn_GetOpenBattleResultsByBand(class Message * pMsg /* r29 */) {
    // Local variables
    int iArgIndex; // r0
    class RBBotbBattleResultsByBandInfo * pReturnLocation; // r0
    int i; // r30
    class RBBotbBattleResultsByBandInfo oDummyVar[1]; // r1+0x8
    int i; // r30

    // References
    // -> struct [anonymous] __vt__Q26Quazal29RBBotbBattleResultsByBandInfo;
    // -> struct [anonymous] __vt__Q26Quazal34_DDL_RBBotbBattleResultsByBandInfo;
}

// Range: 0x80233A3C -> 0x80233B0C
void RBBotbClient::ProtoReturn_GetClosedBattleResultsByBand(class Message * pMsg /* r29 */) {
    // Local variables
    int iArgIndex; // r0
    class RBBotbBattleResultsByBandInfo * pReturnLocation; // r0
    int i; // r30
    class RBBotbBattleResultsByBandInfo oDummyVar[1]; // r1+0x8
    int i; // r30

    // References
    // -> struct [anonymous] __vt__Q26Quazal29RBBotbBattleResultsByBandInfo;
    // -> struct [anonymous] __vt__Q26Quazal34_DDL_RBBotbBattleResultsByBandInfo;
}

// Range: 0x80233B0C -> 0x80233DE4
void RBBotbClient::ProtoReturn_GetBattlesByBand(class Message * pMsg /* r29 */) {
    // Local variables
    int iArgIndex; // r0
    class qList * pReturnLocation; // r0
    int i; // r30
    class qList oDummyVar[1]; // r1+0x28
    int i; // r30

    // References
    // -> struct [anonymous] __vt__Q26Quazal26RBBotbBattleParticipatedIn;
    // -> struct [anonymous] __vt__Q26Quazal31_DDL_RBBotbBattleParticipatedIn;
}

// Range: 0x80233DE4 -> 0x80234034
void RBBotbClient::ProtoReturn_GetCitiesWithOpenBattles(class Message * pMsg /* r31 */) {
    // Local variables
    int iArgIndex; // r0
    class qList * pReturnLocation; // r0
    int i; // r23
    class qList oDummyVar[1]; // r1+0x38
    int i; // r23

    // References
    // -> struct [anonymous] __vt__Q26Quazal20RBBotbCityWithBattle;
    // -> struct [anonymous] __vt__Q26Quazal25_DDL_RBBotbCityWithBattle;
}

// Range: 0x80234034 -> 0x80234148
void RBBotbClient::ProtoReturn_PlayBattle(class Message * pMsg /* r29 */) {
    // Local variables
    int iArgIndex; // r0
    class RBBotbPlayBattleResponse * pReturnLocation; // r0
    int i; // r30
    class RBBotbPlayBattleResponse oDummyVar[1]; // r1+0x8
    int i; // r30

    // References
    // -> struct [anonymous] __vt__Q26Quazal24RBBotbPlayBattleResponse;
    // -> struct [anonymous] __vt__Q26Quazal14RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal29_DDL_RBBotbPlayBattleResponse;
}

// Range: 0x80234148 -> 0x80234488
void RBBotbClient::ProtoReturn_GetBattleResultsByBand(class Message * pMsg /* r25 */) {
    // Local variables
    int iArgIndex; // r0
    class qList * pReturnLocation; // r0
    int i; // r26
    class qList oDummyVar[1]; // r1+0x28
    int i; // r26

    // References
    // -> struct [anonymous] __vt__Q26Quazal11_DDL_RBGuid;
    // -> struct [anonymous] __vt__Q26Quazal15RBBotbBattleRow;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> struct [anonymous] __vt__Q26Quazal20_DDL_RBBotbBattleRow;
}

// Range: 0x80234488 -> 0x802347C8
void RBBotbClient::ProtoReturn_GetBattleResultsByRankRange(class Message * pMsg /* r25 */) {
    // Local variables
    int iArgIndex; // r0
    class qList * pReturnLocation; // r0
    int i; // r26
    class qList oDummyVar[1]; // r1+0x28
    int i; // r26

    // References
    // -> struct [anonymous] __vt__Q26Quazal11_DDL_RBGuid;
    // -> struct [anonymous] __vt__Q26Quazal15RBBotbBattleRow;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> struct [anonymous] __vt__Q26Quazal20_DDL_RBBotbBattleRow;
}

// Range: 0x802347C8 -> 0x80234B08
void RBBotbClient::ProtoReturn_GetBattleResultsByFriends(class Message * pMsg /* r25 */) {
    // Local variables
    int iArgIndex; // r0
    class qList * pReturnLocation; // r0
    int i; // r26
    class qList oDummyVar[1]; // r1+0x28
    int i; // r26

    // References
    // -> struct [anonymous] __vt__Q26Quazal11_DDL_RBGuid;
    // -> struct [anonymous] __vt__Q26Quazal15RBBotbBattleRow;
    // -> struct [anonymous] __vt__Q26Quazal6RBGuid;
    // -> struct [anonymous] __vt__Q26Quazal20_DDL_RBBotbBattleRow;
}

// Range: 0x80234B08 -> 0x80234C14
void RBBotbClient::ProtoReturn_RecordBattleScore(class Message * pMsg /* r29 */) {
    // Local variables
    int iArgIndex; // r0
    class RBBotbRecordBattleResponse * pReturnLocation; // r0
    int i; // r30
    class RBBotbRecordBattleResponse oDummyVar[1]; // r1+0x8
    int i; // r30

    // References
    // -> struct [anonymous] __vt__Q26Quazal26RBBotbRecordBattleResponse;
    // -> struct [anonymous] __vt__Q26Quazal31_DDL_RBBotbRecordBattleResponse;
}

// Range: 0x80234C14 -> 0x80234FF4
void RBBotbClient::ProtoReturn_GetDailyNews(class Message * pMsg /* r30 */, class ProtocolCallContext * pContext /* r31 */) {
    // Local variables
    int iArgIndex; // r24
    class DateTime * pReturnLocation; // r0
    int i; // r25
    class DateTime oDummyVar[1]; // r1+0x58
    int i; // r25
    class String * pReturnLocation; // r0
    int i; // r25
    class String oDummyVar[1]; // r1+0x18
    int i; // r25
    class qList * pReturnLocation; // r0
    int i; // r23
    class qList oDummyVar[1]; // r1+0x50
    int i; // r23

    // References
    // -> struct [anonymous] __vt__Q26Quazal14RBBotbNewsItem;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBBotbNewsItem;
}

// Range: 0x80234FF4 -> 0x802350AC
void RBBotbClient::ProtoReturn_GetDailyNewsCookies(class Message * pMsg /* r29 */) {
    // Local variables
    int iArgIndex; // r0
    class String * pReturnLocation; // r0
    int i; // r30
    class String oDummyVar[1]; // r1+0x8
    int i; // r30
}

// Range: 0x802350AC -> 0x80235344
void RBBotbClient::ProtoReturn_GetBattleNews(class Message * pMsg /* r31 */) {
    // Local variables
    int iArgIndex; // r0
    class qList * pReturnLocation; // r0
    int i; // r23
    class qList oDummyVar[1]; // r1+0x28
    int i; // r23

    // References
    // -> struct [anonymous] __vt__Q26Quazal14RBBotbNewsItem;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBBotbNewsItem;
}

// Range: 0x80235344 -> 0x802353FC
void RBBotbClient::ProtoReturn_UnitTestBotb(class Message * pMsg /* r29 */) {
    // Local variables
    int iArgIndex; // r0
    class String * pReturnLocation; // r0
    int i; // r30
    class String oDummyVar[1]; // r1+0x8
    int i; // r30
}

// Range: 0x802353FC -> 0x80235494
void RBBotbClient::ProtoReturn_UpdateFriendList(class Message * pMsg /* r29 */) {
    // Local variables
    int iArgIndex; // r0
    unsigned char * pReturnLocation; // r0
    int i; // r30
    unsigned char oDummyVar[1]; // r1+0x8
    int i; // r30
}


