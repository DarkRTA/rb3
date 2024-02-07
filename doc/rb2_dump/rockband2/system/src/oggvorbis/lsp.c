/*
    Compile unit: C:\rockband2\system\src\oggvorbis\lsp.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80543E10 -> 0x80544008
*/
static float COS_LOOKUP[129]; // size: 0x204, address: 0x80908FC0
static float INVSQ_LOOKUP[33]; // size: 0x84, address: 0x809091C4
static float INVSQ2EXP_LOOKUP[65]; // size: 0x104, address: 0x80909248
static float FROMdB_LOOKUP[35]; // size: 0x8C, address: 0x8090934C
static float FROMdB2_LOOKUP[32]; // size: 0x80, address: 0x809093D8
// Range: 0x80543E10 -> 0x80544008
void vorbis_lsp_to_curve(float * curve /* r27 */, int * map /* r28 */, int n /* r29 */, float * lsp /* r30 */, int m /* r31 */, float amp /* f27 */, float ampoffset /* f28 */) {
    // Local variables
    int i; // r25
    float wdel; // f31
    int k; // r26
    int qexp; // r1+0x8
    float p; // f30
    float q; // f29
    float w; // f0
    float * ftmp; // r3
    int c; // r0
}


