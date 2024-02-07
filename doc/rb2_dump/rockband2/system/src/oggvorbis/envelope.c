/*
    Compile unit: C:\rockband2\system\src\oggvorbis\envelope.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8053FF98 -> 0x8054001C
*/
// Range: 0x8053FF98 -> 0x8054001C
void _ve_envelope_clear(struct {
    // total size: 0xB8
    int ch; // offset 0x0, size 0x4
    int winlength; // offset 0x4, size 0x4
    int searchstep; // offset 0x8, size 0x4
    float minenergy; // offset 0xC, size 0x4
    struct {
        // total size: 0x18
        int n; // offset 0x0, size 0x4
        int log2n; // offset 0x4, size 0x4
        float * trig; // offset 0x8, size 0x4
        float * trig2; // offset 0xC, size 0x4
        int * bitrev; // offset 0x10, size 0x4
        float scale; // offset 0x14, size 0x4
    } mdct; // offset 0x10, size 0x18
    float * mdct_win; // offset 0x28, size 0x4
    struct {
        // total size: 0x10
        int begin; // offset 0x0, size 0x4
        int end; // offset 0x4, size 0x4
        float * window; // offset 0x8, size 0x4
        float total; // offset 0xC, size 0x4
    } band[7]; // offset 0x2C, size 0x70
    struct {
        // total size: 0x90
        float ampbuf[17]; // offset 0x0, size 0x44
        int ampptr; // offset 0x44, size 0x4
        float nearDC[15]; // offset 0x48, size 0x3C
        float nearDC_acc; // offset 0x84, size 0x4
        float nearDC_partialacc; // offset 0x88, size 0x4
        int nearptr; // offset 0x8C, size 0x4
    } * filter; // offset 0x9C, size 0x4
    int stretch; // offset 0xA0, size 0x4
    int * mark; // offset 0xA4, size 0x4
    long storage; // offset 0xA8, size 0x4
    long current; // offset 0xAC, size 0x4
    long curmark; // offset 0xB0, size 0x4
    long cursor; // offset 0xB4, size 0x4
} * e /* r30 */) {
    // Local variables
    int i; // r31
}


