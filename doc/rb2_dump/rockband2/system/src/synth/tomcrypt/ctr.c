/*
    Compile unit: C:\rockband2\system\src\synth\tomcrypt\ctr.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8059D0EC -> 0x8059D4E0
*/
// Range: 0x8059D0EC -> 0x8059D1EC
int ctr_start(int cipher /* r25 */, const unsigned char * count /* r26 */, const unsigned char * key /* r27 */, int keylen /* r28 */, int num_rounds /* r31 */, struct Symmetric_CTR * ctr /* r29 */) {
    // Local variables
    int x; // r4

    // References
    // -> struct _cipher_descriptor cipher_descriptor[32];
}

// Range: 0x8059D1EC -> 0x8059D27C
int ctr_reinit(const unsigned char * count /* r30 */, struct Symmetric_CTR * ctr /* r31 */) {
    // References
    // -> struct _cipher_descriptor cipher_descriptor[32];
}

// Range: 0x8059D27C -> 0x8059D380
static int ctr_encrypt_fast(unsigned long len /* r28 */, struct Symmetric_CTR * ctr /* r29 */) {
    // Local variables
    int x; // r5
    int * pti; // r31
    int * cti; // r30
    int x0; // r3
    int x1; // r4
    int x2; // r5
    int x3; // r6

    // References
    // -> struct _cipher_descriptor cipher_descriptor[32];
}

// Range: 0x8059D380 -> 0x8059D4DC
int ctr_encrypt(const unsigned char * pt /* r28 */, unsigned char * ct /* r29 */, unsigned long len /* r30 */, struct Symmetric_CTR * ctr /* r31 */) {
    // Local variables
    int x; // r5

    // References
    // -> struct _cipher_descriptor cipher_descriptor[32];
}

// Range: 0x8059D4DC -> 0x8059D4E0
int ctr_decrypt() {}


