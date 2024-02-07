/*
    Compile unit: C:\rockband2\system\src\synth\tomcrypt\aes.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8059A8F4 -> 0x8059CA50
*/
struct _cipher_descriptor {
    // total size: 0x2C
    char * name; // offset 0x0, size 0x4
    unsigned char ID; // offset 0x4, size 0x1
    unsigned long min_key_length; // offset 0x8, size 0x4
    unsigned long max_key_length; // offset 0xC, size 0x4
    unsigned long block_length; // offset 0x10, size 0x4
    unsigned long default_rounds; // offset 0x14, size 0x4
    int (* setup)(unsigned char *, int, int, union Symmetric_key *); // offset 0x18, size 0x4
    void (* ecb_encrypt)(unsigned char *, unsigned char *, union Symmetric_key *); // offset 0x1C, size 0x4
    void (* ecb_decrypt)(unsigned char *, unsigned char *, union Symmetric_key *); // offset 0x20, size 0x4
    int (* test)(); // offset 0x24, size 0x4
    int (* keysize)(int *); // offset 0x28, size 0x4
};
struct _cipher_descriptor rijndael_desc; // size: 0x2C, address: 0x8084A588
static unsigned long ft_tab[4][256]; // size: 0x1000, address: 0x8084A5B8
static unsigned long it_tab[4][256]; // size: 0x1000, address: 0x8084B5B8
static unsigned long fl_tab[4][256]; // size: 0x1000, address: 0x8084C5B8
static unsigned long il_tab[4][256]; // size: 0x1000, address: 0x8084D5B8
static unsigned long rco_tab[10]; // size: 0x28, address: 0x8084E5B8
// Range: 0x8059A8F4 -> 0x8059B870
void rijndael_ecb_encrypt() {
    // Local variables
    unsigned long * kp; // r12

    // References
    // -> static unsigned long fl_tab[4][256];
    // -> static unsigned long ft_tab[4][256];
}

// Range: 0x8059B870 -> 0x8059C800
void rijndael_ecb_decrypt() {
    // Local variables
    unsigned long * kp; // r12

    // References
    // -> static unsigned long il_tab[4][256];
    // -> static unsigned long it_tab[4][256];
}

static unsigned char pt128[16]; // size: 0x10, address: 0x8084E5E0
static unsigned char key128[16]; // size: 0x10, address: 0x8084E5F0
static unsigned char ct128[16]; // size: 0x10, address: 0x8084E600
static unsigned char key192[24]; // size: 0x18, address: 0x8084E610
static unsigned char ct192[16]; // size: 0x10, address: 0x8084E628
static unsigned char key256[32]; // size: 0x20, address: 0x8084E638
static unsigned char ct256[16]; // size: 0x10, address: 0x8084E658
struct rijndael_key {
    // total size: 0x204
    unsigned long eK[64]; // offset 0x0, size 0x100
    unsigned long dK[64]; // offset 0x100, size 0x100
    unsigned long k_len; // offset 0x200, size 0x4
};
union Symmetric_key {
    struct rijndael_key rijndael; // offset 0x0, size 0x204
};
// Range: 0x8059C800 -> 0x8059C9FC
int rijndael_test() {
    // Local variables
    union Symmetric_key key; // r1+0x28
    unsigned char tmp[2][16]; // r1+0x8

    // References
    // -> static unsigned char ct256[16];
    // -> static unsigned char key256[32];
    // -> static unsigned char ct192[16];
    // -> static unsigned char key192[24];
    // -> char * crypt_error;
    // -> static unsigned char ct128[16];
    // -> static unsigned char pt128[16];
    // -> static unsigned char key128[16];
}

// Range: 0x8059C9FC -> 0x8059CA50
int rijndael_keysize() {}


