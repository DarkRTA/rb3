/*
    Compile unit: C:\rockband2\system\src\net\HarmonixGameDDF.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80521DE0 -> 0x80521F40
*/
class DOHandle : public RootObject {
    // total size: 0x4
    unsigned int m_uiValue; // offset 0x0, size 0x4
};
class WKHandle : public DOHandle {
    // total size: 0xC
    unsigned char m_bInitialized; // offset 0x4, size 0x1
    unsigned char m_bInstanciated; // offset 0x5, size 0x1
    class WKHandle * m_phNext; // offset 0x8, size 0x4
};
class WKHandle gMessageBroker; // size: 0xC, address: 0x80981AB4
class WKHandle gVoiceChannel; // size: 0xC, address: 0x80981ACC
class HarmonixGameDDLDeclarations : public DDLDeclarations {
    // total size: 0x14
};
class HarmonixGameDDLDeclarations g_ddlHarmonixGame; // size: 0x14, address: 0x80981AE4
// Range: 0x80521DE0 -> 0x80521DEC
void HarmonixGameDDLDeclarations::Register() {
    // References
    // -> class HarmonixGameDDLDeclarations g_ddlHarmonixGame;
}

// Range: 0x80521DEC -> 0x80521E50
void HarmonixGameDDLDeclarations::Init() {
    // References
    // -> unsigned int s_uiClassID;
    // -> class WKHandle gVoiceChannel;
    // -> unsigned int s_uiClassID;
    // -> class WKHandle gMessageBroker;
    // -> unsigned int s_uiBaseClassID;
    // -> unsigned char LIB_CONFLICT_MUST_LINK_WITH_ANSI_LIBRARY;
    // -> unsigned char LIB_CONFLICT_MUST_LINK_WITH_RELEASE_LIBRARY;
    // -> unsigned char LIB_CONFLICT_MUST_LINK_WITH_SHIPPING_LIBRARY;
}

struct {
    // total size: 0x10
} __vt__Q26Quazal27HarmonixGameDDLDeclarations; // size: 0x10, address: 0x80904B40
struct {
    // total size: 0x8
} __RTTI__Q26Quazal27HarmonixGameDDLDeclarations; // size: 0x8, address: 0x80904B88
// Range: 0x80521EAC -> 0x80521F40
static void __sinit_\HarmonixGameDDF_cpp() {
    // References
    // -> struct [anonymous] __vt__Q26Quazal27HarmonixGameDDLDeclarations;
    // -> class HarmonixGameDDLDeclarations g_ddlHarmonixGame;
    // -> class WKHandle gVoiceChannel;
    // -> class WKHandle gMessageBroker;
}

unsigned int s_uiClassID; // size: 0x4, address: 0x80A56038

