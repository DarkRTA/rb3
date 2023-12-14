/**********************************************************************\
* To commemorate the 1996 RSA Data Security Conference, the following  *
* code is released into the public domain by its author.  Prost!       *
*                                                                      *
* This cipher uses 16-bit words and little-endian byte ordering.       *
* I wonder which processor it was optimized for?                       *
*                                                                      *
* Thanks to CodeView, SoftIce, and D86 for helping bring this code to  *
* the public.                                                          *
\**********************************************************************/

#include <mycrypt.h>

#ifdef RC2

const struct _cipher_descriptor rc2_desc = {
   "rc2",
   12, 8, 128, 8, 16,
   &rc2_setup,
   &rc2_ecb_encrypt,
   &rc2_ecb_decrypt,
   &rc2_test,
   &rc2_keysize
};


/**********************************************************************\
* Expand a variable-length user key (between 1 and 128 bytes) to a     *
* 64-short working rc2 key, of at most "bits" effective key bits.      *
* The effective key bits parameter looks like an export control hack.  *
* For normal use, it should always be set to 1024.  For convenience,   *
* zero is accepted as an alias for 1024.                               *
\**********************************************************************/

   /* 256-entry permutation table, probably derived somehow from pi */
    static const unsigned char permute[256] = {
        217,120,249,196, 25,221,181,237, 40,233,253,121, 74,160,216,157,
        198,126, 55,131, 43,118, 83,142, 98, 76,100,136, 68,139,251,162,
         23,154, 89,245,135,179, 79, 19, 97, 69,109,141,  9,129,125, 50,
        189,143, 64,235,134,183,123, 11,240,149, 33, 34, 92,107, 78,130,
         84,214,101,147,206, 96,178, 28,115, 86,192, 20,167,140,241,220,
         18,117,202, 31, 59,190,228,209, 66, 61,212, 48,163, 60,182, 38,
        111,191, 14,218, 70,105,  7, 87, 39,242, 29,155,188,148, 67,  3,
        248, 17,199,246,144,239, 62,231,  6,195,213, 47,200,102, 30,215,
          8,232,234,222,128, 82,238,247,132,170,114,172, 53, 77,106, 42,
        150, 26,210,113, 90, 21, 73,116, 75,159,208, 94,  4, 24,164,236,
        194,224, 65,110, 15, 81,203,204, 36,145,175, 80,161,244,112, 57,
        153,124, 58,133, 35,184,180,122,252,  2, 54, 91, 37, 85,151, 49,
         45, 93,250,152,227,138,146,174,  5,223, 41, 16,103,108,186,201,
        211,  0,230,207,225,158,168, 44, 99, 22,  1, 63, 88,226,137,169,
         13, 56, 52, 27,171, 51,255,176,187, 72, 12, 95,185,177,205, 46,
        197,243,219, 71,229,165,156,119, 10,166, 32,104,254,127,193,173
    };

int rc2_setup(const unsigned char *key, int keylen, int rounds, symmetric_key *skey)
{
   unsigned *xkey = skey->rc2.xkey;
   unsigned char tmp[128];
   unsigned T8, TM;
   int i, bits;

   _ARGCHK(key != NULL);
   _ARGCHK(skey != NULL);

   if (keylen < 8 || keylen > 128) {
      return CRYPT_INVALID_KEYSIZE;
   }

   if (rounds && rounds != 16) {
      return CRYPT_INVALID_ROUNDS;
   }

   for (i = 0; i < keylen; i++) {
       tmp[i] = key[i];
   }

    /* Phase 1: Expand input key to 128 bytes */
    if (keylen < 128) {
        for (i = keylen; i < 128; i++) {
            tmp[i] = permute[(tmp[i - 1] + tmp[i - keylen]) & 255];
        }
    }
    
    /* Phase 2 - reduce effective key size to "bits" */
    bits = keylen*8;
    T8   = (bits+7)>>3;
    TM   = (255 >> (7 & -bits));
    tmp[128 - T8] = permute[tmp[128 - T8] & TM];
    for (i = 127 - T8; i >= 0; i--) {
        tmp[i] = permute[tmp[i + 1] ^ tmp[i + T8]];
    }

    /* Phase 3 - copy to xkey in little-endian order */
    i = 63;
    do {
        xkey[i] =  (unsigned)tmp[2*i] + ((unsigned)tmp[2*i+1] << 8);
    } while (i--);

#ifdef CLEAN_STACK
    zeromem(tmp, sizeof(tmp));
#endif
    
    return CRYPT_OK;
}

/**********************************************************************\
* Encrypt an 8-byte block of plaintext using the given key.            *
\**********************************************************************/
#ifdef CLEAN_STACK
static void _rc2_ecb_encrypt( const unsigned char *plain,
                            unsigned char *cipher,
                            symmetric_key *skey)
#else
void rc2_ecb_encrypt( const unsigned char *plain,
                            unsigned char *cipher,
                            symmetric_key *skey)
#endif
{
    unsigned *xkey = skey->rc2.xkey;
    unsigned x76, x54, x32, x10, i;

    _ARGCHK(plain != NULL);
    _ARGCHK(cipher != NULL);
    _ARGCHK(skey != NULL);

    x76 = ((unsigned)plain[7] << 8) + (unsigned)plain[6];
    x54 = ((unsigned)plain[5] << 8) + (unsigned)plain[4];
    x32 = ((unsigned)plain[3] << 8) + (unsigned)plain[2];
    x10 = ((unsigned)plain[1] << 8) + (unsigned)plain[0];

    for (i = 0; i < 16; i++) {
        x10 = (x10 + (x32 & ~x76) + (x54 & x76) + xkey[4*i+0]) & 0xFFFF;
        x10 = ((x10 << 1) | (x10 >> 15)) & 0xFFFF;

        x32 = (x32 + (x54 & ~x10) + (x76 & x10) + xkey[4*i+1]) & 0xFFFF;
        x32 = ((x32 << 2) | (x32 >> 14)) & 0xFFFF;

        x54 = (x54 + (x76 & ~x32) + (x10 & x32) + xkey[4*i+2]) & 0xFFFF;
        x54 = ((x54 << 3) | (x54 >> 13)) & 0xFFFF;

        x76 = (x76 + (x10 & ~x54) + (x32 & x54) + xkey[4*i+3]) & 0xFFFF;
        x76 = ((x76 << 5) | (x76 >> 11)) & 0xFFFF;

        if (i == 4 || i == 10) {
            x10 = (x10 + xkey[x76 & 63]) & 0xFFFF;
            x32 = (x32 + xkey[x10 & 63]) & 0xFFFF;
            x54 = (x54 + xkey[x32 & 63]) & 0xFFFF;
            x76 = (x76 + xkey[x54 & 63]) & 0xFFFF;
        }
    }

    cipher[0] = (unsigned char)x10;
    cipher[1] = (unsigned char)(x10 >> 8);
    cipher[2] = (unsigned char)x32;
    cipher[3] = (unsigned char)(x32 >> 8);
    cipher[4] = (unsigned char)x54;
    cipher[5] = (unsigned char)(x54 >> 8);
    cipher[6] = (unsigned char)x76;
    cipher[7] = (unsigned char)(x76 >> 8);
}

#ifdef CLEAN_STACK
void rc2_ecb_encrypt( const unsigned char *plain,
                            unsigned char *cipher,
                            symmetric_key *skey)
{
    _rc2_ecb_encrypt(plain, cipher, skey);
    burn_stack(sizeof(unsigned *) + sizeof(unsigned) * 5);
}
#endif

/**********************************************************************\
* Decrypt an 8-byte block of ciphertext using the given key.           *
\**********************************************************************/

#ifdef CLEAN_STACK
static void _rc2_ecb_decrypt( const unsigned char *cipher,
                            unsigned char *plain,
                            symmetric_key *skey)
#else
void rc2_ecb_decrypt( const unsigned char *cipher,
                            unsigned char *plain,
                            symmetric_key *skey)
#endif
{
    unsigned x76, x54, x32, x10;
    unsigned *xkey = skey->rc2.xkey;
    int i;

    _ARGCHK(plain != NULL);
    _ARGCHK(cipher != NULL);
    _ARGCHK(skey != NULL);

    x76 = ((unsigned)cipher[7] << 8) + (unsigned)cipher[6];
    x54 = ((unsigned)cipher[5] << 8) + (unsigned)cipher[4];
    x32 = ((unsigned)cipher[3] << 8) + (unsigned)cipher[2];
    x10 = ((unsigned)cipher[1] << 8) + (unsigned)cipher[0];

    for (i = 15; i >= 0; i--) {
        if (i == 4 || i == 10) {
            x76 = (x76 - xkey[x54 & 63]) & 0xFFFF;
            x54 = (x54 - xkey[x32 & 63]) & 0xFFFF;
            x32 = (x32 - xkey[x10 & 63]) & 0xFFFF;
            x10 = (x10 - xkey[x76 & 63]) & 0xFFFF;
        }

        x76 = ((x76 << 11) | (x76 >> 5)) & 0xFFFF;
        x76 = (x76 - ((x10 & ~x54) + (x32 & x54) + xkey[4*i+3])) & 0xFFFF;

        x54 = ((x54 << 13) | (x54 >> 3)) & 0xFFFF;
        x54 = (x54 - ((x76 & ~x32) + (x10 & x32) + xkey[4*i+2])) & 0xFFFF;

        x32 = ((x32 << 14) | (x32 >> 2)) & 0xFFFF;
        x32 = (x32 - ((x54 & ~x10) + (x76 & x10) + xkey[4*i+1])) & 0xFFFF;

        x10 = ((x10 << 15) | (x10 >> 1)) & 0xFFFF;
        x10 = (x10 - ((x32 & ~x76) + (x54 & x76) + xkey[4*i+0])) & 0xFFFF;
    }

    plain[0] = (unsigned char)x10;
    plain[1] = (unsigned char)(x10 >> 8);
    plain[2] = (unsigned char)x32;
    plain[3] = (unsigned char)(x32 >> 8);
    plain[4] = (unsigned char)x54;
    plain[5] = (unsigned char)(x54 >> 8);
    plain[6] = (unsigned char)x76;
    plain[7] = (unsigned char)(x76 >> 8);
}

#ifdef CLEAN_STACK
void rc2_ecb_decrypt( const unsigned char *cipher,
                            unsigned char *plain,
                            symmetric_key *skey)
{
    _rc2_ecb_decrypt(cipher, plain, skey);
    burn_stack(sizeof(unsigned *) + sizeof(unsigned) * 4 + sizeof(int));
}
#endif

int rc2_test(void)
{
   static const struct {
        int keylen;
        unsigned char key[16], pt[8], ct[8];
   } tests[] = {

   { 8,
     { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
     { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },
     { 0x30, 0x64, 0x9e, 0xdf, 0x9b, 0xe7, 0xd2, 0xc2 }

   },
   { 16,
     { 0x88, 0xbc, 0xa9, 0x0e, 0x90, 0x87, 0x5a, 0x7f,
       0x0f, 0x79, 0xc3, 0x84, 0x62, 0x7b, 0xaf, 0xb2 },
     { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
     { 0x22, 0x69, 0x55, 0x2a, 0xb0, 0xf8, 0x5c, 0xa6 }
   }
  };
    int x, failed, errno;
    symmetric_key skey;
    unsigned char buf[2][8];

    failed = 0;
    for (x = 0; x < (int)(sizeof(tests) / sizeof(tests[0])); x++) {
        zeromem(buf, sizeof(buf));
        if ((errno = rc2_setup(tests[x].key, tests[x].keylen, 0, &skey)) != CRYPT_OK) {
           return errno;
        }
        
        rc2_ecb_encrypt(tests[x].pt, buf[0], &skey);
        rc2_ecb_decrypt(buf[0], buf[1], &skey);
        
        if (memcmp(buf[0], tests[x].ct, 8)) {
#if 0
           int y;
           printf("\nTest %d failed to encrypt\n", x);
           for (y = 0; y < 8; y++) {
               printf("%02x ", buf[0][y]);
           }
           printf("\n");
#endif 
           failed = 1;
        }

        if (memcmp(buf[1], tests[x].pt, 8)) {
#if 0
           int y;
           printf("\nTest %d failed to decrypt\n", x);
           for (y = 0; y < 8; y++) {
               printf("%02x ", buf[1][y]);
           }
           printf("\n");
#endif
           failed = 1;
        }
    }
    
    if (failed == 1) {
        return CRYPT_FAIL_TESTVECTOR;
    } else {
        return CRYPT_OK;
    }
}

int rc2_keysize(int *keysize)
{
   _ARGCHK(keysize != NULL);
   if (*keysize < 8) {
       return CRYPT_INVALID_KEYSIZE;
   } else if (*keysize > 128) {
       *keysize = 128;
   }
   return CRYPT_OK;
}

#endif



