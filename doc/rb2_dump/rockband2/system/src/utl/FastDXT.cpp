/*
    Compile unit: C:\rockband2\system\src\utl\FastDXT.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x806086D8 -> 0x80608C6C
*/
struct PaletteColor {
    // total size: 0x8
    unsigned char color[3]; // offset 0x0, size 0x3
    unsigned int weight; // offset 0x4, size 0x4
};
// Range: 0x806086D8 -> 0x806087B8
void FindPaletteColors() {
    // Local variables
    struct PaletteColor min; // r1+0x18
    struct PaletteColor max; // r1+0x10
    struct PaletteColor pixel; // r1+0x8
    int iColorIndex; // r11
}

// Range: 0x806087B8 -> 0x80608A80
void FitToPalette(unsigned char * pTile /* r21 */, unsigned char * pColor0 /* r22 */, unsigned char * pColor1 /* r23 */, unsigned int & iCompressedIndices /* r24 */) {
    // Local variables
    unsigned char pColor2[3]; // r1+0x10
    unsigned char pColor3[3]; // r1+0xC
    unsigned char pColor[3]; // r1+0x8
    int iColorIndex; // r26
    unsigned int iMinError; // r25
    unsigned char iPaletteIndex; // r3
}

// Range: 0x80608A80 -> 0x80608B6C
void CompressTile(unsigned char * pTile /* r29 */, unsigned int & iDXT1Palette /* r30 */, unsigned int & iDXT1Indices /* r31 */) {
    // Local variables
    unsigned char pColorMin[3]; // r1+0xC
    unsigned char pColorMax[3]; // r1+0x8
    unsigned short iColorMin; // r5
    unsigned short iColorMax; // r0
}

// Range: 0x80608B6C -> 0x80608C6C
void FastDXT1Compress(class RndBitmap & src /* r25 */) {
    // Local variables
    int kiTileCount; // r30
    int iSrcX; // r29
    int iSrcY; // r28
    unsigned int * pDXT1Palette; // r27
    unsigned int iTileIndex; // r26
    unsigned char half; // r1+0x8
    unsigned char * pTile; // r31
}


