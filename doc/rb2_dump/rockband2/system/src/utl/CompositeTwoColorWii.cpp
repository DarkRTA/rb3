/*
    Compile unit: C:\rockband2\system\src\utl\CompositeTwoColorWii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80603BDC -> 0x806048D0
*/
// Range: 0x80603BDC -> 0x80603DEC
void DecompressPaletteDXT1(unsigned short * pCompressedPalette /* r29 */, unsigned char (* pDecompressedPalette)[4] /* r31 */) {
    // Local variables
    unsigned short iColor0; // r0
    unsigned short iColor1; // r10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80603DEC -> 0x80603F44
void DecompressTileDXT1(unsigned char * pCompressedTile /* r29 */, unsigned char * pDecompressedTile /* r30 */, unsigned char kbAsAlpha /* r31 */) {
    // Local variables
    unsigned char pPalette[4][4]; // r1+0x8
    unsigned int iCompressedIndices; // r6
    unsigned char iPixelIndex; // r7
    unsigned char kiPixelOffset; // r4
    unsigned char iPaletteIndex; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80603F44 -> 0x80604090
void DecompressMaskTile(class RndBitmap * pMaskBmp /* r23 */, unsigned char * pDecompressedTile /* r24 */, unsigned int kiX /* r25 */, unsigned int kiY /* r26 */, float kfScaleX /* f29 */, float kfScaleY /* f30 */) {
    // Local variables
    unsigned int iDecompressedIndex; // r29
    unsigned int iY; // r28
    unsigned int iX; // r27
    unsigned char r; // r1+0xB
    unsigned char g; // r1+0xA
    unsigned char b; // r1+0x9
    unsigned char a; // r1+0x8
    unsigned int kiPixelOffset; // r3
}

// Range: 0x80604090 -> 0x806043E4
void CompositeTwoColorTile(unsigned char * pCompositeTile /* r28 */, unsigned char * pMaskTile /* r29 */, class Color * pColor1 /* r30 */, class Color * pColor2 /* r31 */) {
    // Local variables
    unsigned int iPixelIndex; // r3
    unsigned char kiPixelOffset; // r8
    class Color base; // r1+0x30
    class Color blend; // r1+0x20
    class Color mask; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806043E4 -> 0x806048D0
void CompositeTwoColor(class RndBitmap * pBaseBmp /* r18 */, class RndBitmap * pMaskBmp /* r19 */, class Color * pColor1 /* r20 */, class Color * pColor2 /* r21 */, class RndBitmap * pCompositeBmp /* r22 */) {
    // Local variables
    unsigned char * pBaseDXTColorTile; // r30
    unsigned char * pBaseDXTAlphaTile; // r29
    float kfMaskScaleX; // f31
    float kfMaskScaleY; // f30
    unsigned char * pMaskDXTColorTile; // r28
    unsigned char pMaskRGBAColorTile[64]; // r1+0x10
    int iSrcX; // r27
    int iSrcY; // r26
    unsigned char half; // r1+0x8
    int kiDiffuseDXTTileCount; // r25
    unsigned int iDXTTileIndex; // r24
    unsigned char * pCompositeTile; // r23

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


