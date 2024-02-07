/*
    Compile unit: C:\rockband2\system\src\synth\FxSend.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80572D80 -> 0x805734F4
*/
// Range: 0x80572D80 -> 0x80572E6C
void FxSend::Replace(class FxSend * const this /* r30 */, class Object * to /* r31 */) {
    // References
    // -> struct [anonymous] __vt__31ObjOwnerPtr<6FxSend,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80572E6C -> 0x80572E70
void FxSend::Recreate() {}

// Range: 0x80572E70 -> 0x80572FF4
unsigned char FxSend::CheckChain(class FxSend * const this /* r29 */, int myStage /* r30 */) {
    // Local variables
    class FxSend * i; // r6
    struct _List_iterator i; // r1+0x18
    class FxSend * refSend; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6FxSend;
    // -> class Debug TheDebug;
}

// Range: 0x80572FF4 -> 0x80573038
void FxSend::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80573038 -> 0x80573238
void FxSend::Load(class FxSend * const this /* r28 */, class BinStream & d /* r27 */) {
    // Local variables
    int rev; // r1+0x14
    int oldStage; // r30
    enum SendChannels oldChans; // r29
    float pctWet; // r1+0x10
    int tmp; // r1+0xC

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80573238 -> 0x8057323C
void FxSend::UpdateMix() {}

// Range: 0x8057323C -> 0x8057332C
void FxSend::TestWithMic(class FxSend * const this /* r30 */) {
    // Local variables
    class Mic * mic; // r31

    // References
    // -> class Synth * TheSynth;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8057332C -> 0x80573330
void FxSend::OnParametersChanged() {}

// Range: 0x80573330 -> 0x805734B0
void FxSend::SetType(class FxSend * const this /* r29 */, class Symbol & FxSend /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x805734B0 -> 0x805734F4
class Symbol FxSend::ClassName() {
    // References
    // -> class Symbol name;
}


