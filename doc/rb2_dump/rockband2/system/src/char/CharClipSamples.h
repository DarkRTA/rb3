/*
    Compile unit: C:\rockband2\system\src\char\CharClipSamples.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803453F8 -> 0x80345D2C
*/
// Range: 0x803453F8 -> 0x8034546C
static unsigned char FacingBone() {}

// Range: 0x8034546C -> 0x803456CC
void CharClipUtl::CreateClip(class CharClipSamples * clip /* r28 */, int numSamples /* r29 */) {
    // Local variables
    class list bones; // r1+0x58
    class CharClipSet * clips; // r0
    class vector full; // r1+0x6C
    struct _List_iterator it; // r1+0x40
    class vector empty; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803456CC -> 0x80345804
void CharClipUtl::FinishClip(class CharClipSamples * clip /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80345804 -> 0x80345D2C
void CharClipUtl::BakeOutClipFacing(class CharClipSamples * clip /* r28 */) {
    // Local variables
    unsigned char bakeFacing; // r0
    unsigned char bakePos; // r0
    class ObjectDir * dude; // r30
    class CharUtlBoneSaver boneSaver; // r1+0x40
    class CharBonesMeshes bones; // r1+0xD0
    class CharBonesSamples & full; // r29
    int pelvisPosOffset; // r0
    int facingPosOffset; // r0
    int facingRotOffset; // r0
    int pelvisRotOffset; // r0
    class RndTransformable * pelvis; // r0
    int i; // r31
    float ang; // f30
    class Transform pelvis; // r1+0x90
    class Transform facing; // r1+0x50

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


