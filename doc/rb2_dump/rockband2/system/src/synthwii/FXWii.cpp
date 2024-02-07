/*
    Compile unit: C:\rockband2\system\src\synthwii\FXWii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80561E28 -> 0x80562828
*/
static enum FXMode currentFX[3]; // size: 0xC, address: 0x80982A60
// Range: 0x80561E28 -> 0x80561E34
void * myMemAlloc() {}

// Range: 0x80561E34 -> 0x80561E38
void myMemFree() {}

// Range: 0x80561E38 -> 0x80561E4C
void myAuxAFXWrapper(void * data /* r0 */) {}

// Range: 0x80561E4C -> 0x80561E60
void myAuxBFXWrapper(void * data /* r0 */) {}

// Range: 0x80561E60 -> 0x80561E74
void myAuxCFXWrapper(void * data /* r0 */) {}

// Range: 0x80561E74 -> 0x80561EF4
void doWiiFX() {
    // References
    // -> static enum FXMode currentFX[3];
}

class WiiFX TheWiiFX; // size: 0x3B4, address: 0x80982A78
// Range: 0x80561EF4 -> 0x80562058
void * WiiFX::WiiFX(class WiiFX * const this /* r30 */) {
    // References
    // -> static enum FXMode currentFX[3];
}

// Range: 0x80562058 -> 0x805620F4
void * WiiFX::~WiiFX(class WiiFX * const this /* r30 */) {}

// Range: 0x805620F4 -> 0x80562158
void WiiFX::Init(class WiiFX * const this /* r30 */) {}

// Range: 0x80562158 -> 0x8056215C
void WiiFX::Terminate() {}

// Range: 0x8056215C -> 0x80562764
unsigned char WiiFX::SetFX(class WiiFX * const this /* r29 */, int auxNum /* r30 */) {
    // Local variables
    const char * name; // r0
    class DataArray * effect; // r31
    void * contextCallback; // r4

    // References
    // -> static enum FXMode currentFX[3];
}

// Range: 0x80562764 -> 0x805627BC
unsigned char WiiFX::SetReverb() {
    // References
    // -> static enum FXMode currentFX[3];
}

// Range: 0x805627BC -> 0x805627E0
unsigned char WiiFX::IsReverb() {
    // References
    // -> static enum FXMode currentFX[3];
}

// Range: 0x805627E0 -> 0x80562828
static void __sinit_\FXWii_cpp() {
    // References
    // -> class WiiFX TheWiiFX;
}


