/*
    Compile unit: C:\rockband2\system\src\synth\tomcrypt\crypt.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8059CFE4 -> 0x8059D0EC
*/
struct _cipher_descriptor cipher_descriptor[32]; // size: 0x580, address: 0x80983730
struct Symmetric_CTR {
    // total size: 0x310
    int cipher; // offset 0x0, size 0x4
    int blocklen; // offset 0x4, size 0x4
    int padlen; // offset 0x8, size 0x4
    unsigned char ctr[128]; // offset 0xC, size 0x80
    unsigned char pad[128]; // offset 0x8C, size 0x80
    union Symmetric_key key; // offset 0x10C, size 0x204
};
// Range: 0x8059CFE4 -> 0x8059D0A8
int register_cipher(const struct _cipher_descriptor * cipher /* r30 */) {
    // Local variables
    int x; // r31

    // References
    // -> char * crypt_error;
    // -> struct _cipher_descriptor cipher_descriptor[32];
}

// Range: 0x8059D0A8 -> 0x8059D0EC
int cipher_is_valid() {
    // References
    // -> char * crypt_error;
    // -> struct _cipher_descriptor cipher_descriptor[32];
}

char * crypt_error; // size: 0x4, address: 0x80A54860

