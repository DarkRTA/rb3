/*
    Compile unit: C:\rockband2\system\src\synth\Sequence.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8058715C -> 0x80587C8C
*/
// Range: 0x8058715C -> 0x80587160
void SeqInst::Poll() {}

// Range: 0x80587160 -> 0x805871A4
void Sequence::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805871A4 -> 0x80587280
void Sequence::Load(class Sequence * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80587280 -> 0x805872B0
class Object * SfxSeq::NewObject() {}

// Range: 0x805872B0 -> 0x805872E0
class Object * WaitSeq::NewObject() {}

// Range: 0x805872E0 -> 0x80587310
class Object * RandomGroupSeq::NewObject() {}

// Range: 0x80587310 -> 0x80587364
class Object * SerialGroupSeq::NewObject() {
    // References
    // -> struct [anonymous] __vt__14SerialGroupSeq;
}

// Range: 0x80587364 -> 0x805873B8
class Object * ParallelGroupSeq::NewObject() {
    // References
    // -> struct [anonymous] __vt__16ParallelGroupSeq;
}

// Range: 0x805873B8 -> 0x80587538
void SfxSeq::SetType(class SfxSeq * const this /* r29 */, class Symbol & SfxSeq /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x80587538 -> 0x8058757C
class Symbol SfxSeq::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x8058757C -> 0x805876FC
void ParallelGroupSeq::SetType(class ParallelGroupSeq * const this /* r29 */, class Symbol & ParallelGroupSeq /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x805876FC -> 0x80587740
class Symbol ParallelGroupSeq::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x80587740 -> 0x805878C0
void SerialGroupSeq::SetType(class SerialGroupSeq * const this /* r29 */, class Symbol & SerialGroupSeq /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x805878C0 -> 0x80587904
class Symbol SerialGroupSeq::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x80587904 -> 0x80587A84
void RandomGroupSeq::SetType(class RandomGroupSeq * const this /* r29 */, class Symbol & RandomGroupSeq /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x80587A84 -> 0x80587AC8
class Symbol RandomGroupSeq::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x80587AC8 -> 0x80587C48
void WaitSeq::SetType(class WaitSeq * const this /* r29 */, class Symbol & WaitSeq /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x80587C48 -> 0x80587C8C
class Symbol WaitSeq::ClassName() {
    // References
    // -> class Symbol name;
}


