/*
    Compile unit: C:\rockband2\band2\src\net_band\RBScoresDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80223758 -> 0x80223F98
*/
class RBScoresClient : public ClientProtocol {
    // total size: 0x38
};
// Range: 0x80223758 -> 0x802239EC
unsigned char RBScoresClient::CallRecordSoloScore(class RBScoresClient * const this /* r24 */, class ProtocolCallContext * pContext /* r25 */, const unsigned int & principalID /* r26 */, const signed char & roleID /* r27 */, const class String & songName /* r28 */, const unsigned int & songScore /* r29 */, const unsigned int & careerScore /* r30 */, const signed char & diffID /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r23

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x802239EC -> 0x80223C60
unsigned char RBScoresClient::CallRecordBandScore(class RBScoresClient * const this /* r25 */, class ProtocolCallContext * pContext /* r26 */, const class RBGuid & bandGuid /* r27 */, const class String & songName /* r28 */, const unsigned int & songScore /* r29 */, const unsigned int & careerScore /* r30 */, const unsigned int & fans /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r24

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80223C60 -> 0x80223E94
unsigned char RBScoresClient::CallRecordBandFans(class RBScoresClient * const this /* r28 */, class ProtocolCallContext * pContext /* r29 */, const class RBGuid & bandGuid /* r30 */, const unsigned int & fans /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r27

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80223E94 -> 0x80223F38
void RBScoresClient::ExtractCallSpecificResults() {
    // Local variables
    unsigned short uiRMCID; // r4
}

struct {
    // total size: 0x64
} __vt__Q26Quazal14RBScoresClient; // size: 0x64, address: 0x808AEAD0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14RBScoresClient; // size: 0x8, address: 0x808AEB78

