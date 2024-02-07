/*
    Compile unit: C:\rockband2\system\src\math\Trig.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80631FF0 -> 0x806324C4
*/
static int gSinTableSize; // size: 0x4, address: 0x80A47C58
static float gSinTableConversion; // size: 0x4, address: 0x80A55540
static float * gSinTable; // size: 0x4, address: 0x80A55544
static float * gSinGradients; // size: 0x4, address: 0x80A55548
static float gBigSinTable[256]; // size: 0x400, address: 0x8098A930
static float gBigSinGradients[256]; // size: 0x400, address: 0x8098AD30
// Range: 0x80631FF0 -> 0x80632204
void TrigTableInit() {
    // Local variables
    float invConvert; // f31
    int i; // r31
    float x; // f1
    float sx; // f0
    float x; // f1

    // References
    // -> static float gBigSinGradients[256];
    // -> static float gBigSinTable[256];
    // -> static float * gSinGradients;
    // -> static float * gSinTable;
    // -> static float gSinTableConversion;
    // -> static int gSinTableSize;
}

// Range: 0x80632204 -> 0x8063223C
void TrigTableTerminate() {
    // References
    // -> static float * gSinTable;
    // -> static float * gSinGradients;
}

// Range: 0x8063223C -> 0x80632410
float Sine() {
    // Local variables
    int k; // r4
    float y; // f1
    float index; // f2

    // References
    // -> static int gSinTableSize;
    // -> static float * gSinTable;
    // -> static float * gSinGradients;
    // -> static float gSinTableConversion;
}

// Range: 0x80632410 -> 0x80632480
float FastSin() {
    // Local variables
    int index; // r0
    int index; // r0

    // References
    // -> static float gBigSinTable[256];
}

// Range: 0x80632480 -> 0x806324C4
static void __sinit_\Trig_cpp() {
    // References
    // -> static float gSinTableConversion;
    // -> static int gSinTableSize;
}


