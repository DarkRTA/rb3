/*
    Compile unit: C:\rockband2\band2\src\net_band\RBConfigDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80219CF8 -> 0x8021A130
*/
class RBConfigClient : public ClientProtocol {
    // total size: 0x38
};
// Range: 0x80219CF8 -> 0x80219F44
unsigned char RBConfigClient::CallGetConfig(class RBConfigClient * const this /* r27 */, class ProtocolCallContext * pContext /* r28 */, const class String & inDTA /* r29 */, class String * sandboxVersion /* r30 */, class String * outDTA /* r31 */) {
    // Local variables
    class ScopedCS oCS; // r1+0x8
    class Message msgRequest; // r1+0x10
    class Message * pMsg; // r26

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x80219F44 -> 0x8021A0D0
void RBConfigClient::ExtractCallSpecificResults(class Message * pMessage /* r27 */, class ProtocolCallContext * pContext /* r28 */) {
    // Local variables
    unsigned short uiRMCID; // r4
}

struct {
    // total size: 0x64
} __vt__Q26Quazal14RBConfigClient; // size: 0x64, address: 0x808AE3E0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal14RBConfigClient; // size: 0x8, address: 0x808AE488

