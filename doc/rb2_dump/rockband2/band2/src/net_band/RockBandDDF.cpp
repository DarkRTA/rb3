/*
    Compile unit: C:\rockband2\band2\src\net_band\RockBandDDF.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802240C4 -> 0x80224214
*/
class DDLDeclarations : public RootObject {
    // total size: 0x14
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    int m_iUseRefCount; // offset 0x4, size 0x4
    unsigned char m_bRegistered; // offset 0x8, size 0x1
    class DDLDeclarations * m_pNextDDLDecl; // offset 0xC, size 0x4
    unsigned char m_bCoreDDLDeclarations; // offset 0x10, size 0x1
};
class RockBandDDLDeclarations : public DDLDeclarations {
    // total size: 0x14
};
class RockBandDDLDeclarations g_ddlRockBand; // size: 0x14, address: 0x8097CA2C
// Range: 0x802240C4 -> 0x802240D0
void RockBandDDLDeclarations::Register() {
    // References
    // -> class RockBandDDLDeclarations g_ddlRockBand;
}

// Range: 0x802240D0 -> 0x80224108
void RockBandDDLDeclarations::Init() {
    // References
    // -> unsigned int s_uiBaseClassID;
    // -> unsigned char LIB_CONFLICT_MUST_LINK_WITH_ANSI_LIBRARY;
    // -> unsigned char LIB_CONFLICT_MUST_LINK_WITH_RELEASE_LIBRARY;
    // -> unsigned char LIB_CONFLICT_MUST_LINK_WITH_SHIPPING_LIBRARY;
}

// Range: 0x80224108 -> 0x80224114
void RegisterProductKeys() {}

// Range: 0x80224114 -> 0x80224160
void InitDOClasses() {}

struct {
    // total size: 0x10
} __vt__Q26Quazal23RockBandDDLDeclarations; // size: 0x10, address: 0x808AEBA8
struct {
    // total size: 0x8
} __RTTI__Q26Quazal23RockBandDDLDeclarations; // size: 0x8, address: 0x808AEBF0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal15DDLDeclarations; // size: 0x8, address: 0x808AEC20
// Range: 0x802241BC -> 0x80224214
static void __sinit_\RockBandDDF_cpp() {
    // References
    // -> struct [anonymous] __vt__Q26Quazal23RockBandDDLDeclarations;
    // -> class RockBandDDLDeclarations g_ddlRockBand;
}

unsigned int s_uiBaseClassID; // size: 0x4, address: 0x80A489D0
unsigned char LIB_CONFLICT_MUST_LINK_WITH_ANSI_LIBRARY; // size: 0x1, address: 0x80A489B1
unsigned char LIB_CONFLICT_MUST_LINK_WITH_RELEASE_LIBRARY; // size: 0x1, address: 0x80A489B0
unsigned char LIB_CONFLICT_MUST_LINK_WITH_SHIPPING_LIBRARY; // size: 0x1, address: 0x80A489B2

