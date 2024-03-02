/* Submitted by Dobes Vandermeer  (dobes@smartt.com) */
#include "mycrypt.h"

#ifdef MD4

const struct _hash_descriptor md4_desc =
{
    "md4",
    6,
    16,
    64,
    &md4_init,
    &md4_process,
    &md4_done,
    &md4_test
};

#define S11 3
#define S12 7
#define S13 11
#define S14 19
#define S21 3
#define S22 5
#define S23 9
#define S24 13
#define S31 3
#define S32 9
#define S33 11
#define S34 15

/* F, G and H are basic MD4 functions. */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))

/* ROTATE_LEFT rotates x left n bits. */
#define ROTATE_LEFT(x, n) ROL(x, n)

/* FF, GG and HH are transformations for rounds 1, 2 and 3 */ 
/* Rotation is separate from addition to prevent recomputation */ 

#define FF(a, b, c, d, x, s) { \
    (a) += F ((b), (c), (d)) + (x); \
    (a) = ROTATE_LEFT ((a), (s)); \
  }
#define GG(a, b, c, d, x, s) { \
    (a) += G ((b), (c), (d)) + (x) + 0x5a827999UL; \
    (a) = ROTATE_LEFT ((a), (s)); \
  }
#define HH(a, b, c, d, x, s) { \
    (a) += H ((b), (c), (d)) + (x) + 0x6ed9eba1UL; \
    (a) = ROTATE_LEFT ((a), (s)); \
  }

#ifdef CLEAN_STACK
static void _md4_compress(hash_state *md)
#else
static void md4_compress(hash_state *md)
#endif
{
    unsigned long x[16], a, b, c, d;
    int i;

    _ARGCHK(md != NULL);

    /* copy state */
    a = md->md4.state[0];
    b = md->md4.state[1];
    c = md->md4.state[2];
    d = md->md4.state[3];

    /* copy the state into 512-bits into W[0..15] */
    for (i = 0; i < 16; i++) {
        LOAD32L(x[i], md->md4.buf + (4*i));
    }
 
    /* Round 1 */ 
    FF (a, b, c, d, x[ 0], S11); /* 1 */ 
    FF (d, a, b, c, x[ 1], S12); /* 2 */ 
    FF (c, d, a, b, x[ 2], S13); /* 3 */ 
    FF (b, c, d, a, x[ 3], S14); /* 4 */ 
    FF (a, b, c, d, x[ 4], S11); /* 5 */ 
    FF (d, a, b, c, x[ 5], S12); /* 6 */ 
    FF (c, d, a, b, x[ 6], S13); /* 7 */ 
    FF (b, c, d, a, x[ 7], S14); /* 8 */ 
    FF (a, b, c, d, x[ 8], S11); /* 9 */ 
    FF (d, a, b, c, x[ 9], S12); /* 10 */
    FF (c, d, a, b, x[10], S13); /* 11 */ 
    FF (b, c, d, a, x[11], S14); /* 12 */
    FF (a, b, c, d, x[12], S11); /* 13 */
    FF (d, a, b, c, x[13], S12); /* 14 */ 
    FF (c, d, a, b, x[14], S13); /* 15 */ 
    FF (b, c, d, a, x[15], S14); /* 16 */ 
    
    /* Round 2 */ 
    GG (a, b, c, d, x[ 0], S21); /* 17 */ 
    GG (d, a, b, c, x[ 4], S22); /* 18 */ 
    GG (c, d, a, b, x[ 8], S23); /* 19 */ 
    GG (b, c, d, a, x[12], S24); /* 20 */ 
    GG (a, b, c, d, x[ 1], S21); /* 21 */ 
    GG (d, a, b, c, x[ 5], S22); /* 22 */ 
    GG (c, d, a, b, x[ 9], S23); /* 23 */ 
    GG (b, c, d, a, x[13], S24); /* 24 */ 
    GG (a, b, c, d, x[ 2], S21); /* 25 */ 
    GG (d, a, b, c, x[ 6], S22); /* 26 */ 
    GG (c, d, a, b, x[10], S23); /* 27 */ 
    GG (b, c, d, a, x[14], S24); /* 28 */ 
    GG (a, b, c, d, x[ 3], S21); /* 29 */ 
    GG (d, a, b, c, x[ 7], S22); /* 30 */ 
    GG (c, d, a, b, x[11], S23); /* 31 */ 
    GG (b, c, d, a, x[15], S24); /* 32 */ 
    
    /* Round 3 */
    HH (a, b, c, d, x[ 0], S31); /* 33 */ 
    HH (d, a, b, c, x[ 8], S32); /* 34 */ 
    HH (c, d, a, b, x[ 4], S33); /* 35 */ 
    HH (b, c, d, a, x[12], S34); /* 36 */ 
    HH (a, b, c, d, x[ 2], S31); /* 37 */ 
    HH (d, a, b, c, x[10], S32); /* 38 */ 
    HH (c, d, a, b, x[ 6], S33); /* 39 */ 
    HH (b, c, d, a, x[14], S34); /* 40 */ 
    HH (a, b, c, d, x[ 1], S31); /* 41 */ 
    HH (d, a, b, c, x[ 9], S32); /* 42 */ 
    HH (c, d, a, b, x[ 5], S33); /* 43 */ 
    HH (b, c, d, a, x[13], S34); /* 44 */ 
    HH (a, b, c, d, x[ 3], S31); /* 45 */ 
    HH (d, a, b, c, x[11], S32); /* 46 */ 
    HH (c, d, a, b, x[ 7], S33); /* 47 */ 
    HH (b, c, d, a, x[15], S34); /* 48 */ 
    

    /* Update our state */
    md->md4.state[0] = md->md4.state[0] + a;
    md->md4.state[1] = md->md4.state[1] + b;
    md->md4.state[2] = md->md4.state[2] + c;
    md->md4.state[3] = md->md4.state[3] + d;
}

#ifdef CLEAN_STACK
static void md4_compress(hash_state *md)
{
   _md4_compress(md);
   burn_stack(sizeof(unsigned long) * 20 + sizeof(int));
}
#endif

void md4_init(hash_state * md)
{
   _ARGCHK(md != NULL);
   md->md4.state[0] = 0x67452301UL;
   md->md4.state[1] = 0xefcdab89UL;
   md->md4.state[2] = 0x98badcfeUL;
   md->md4.state[3] = 0x10325476UL;
   md->md4.length  = 0;
   md->md4.curlen = 0;
}

void md4_process(hash_state * md, const unsigned char *buf, unsigned long len)
{
    unsigned long n;
    _ARGCHK(md != NULL);
    _ARGCHK(buf != NULL);
    while (len) {
        n = MIN(len, (64 - md->md4.curlen));
        memcpy(md->md4.buf + md->md4.curlen, buf, n);
        md->md4.curlen += n;
        buf            += n;
        len            -= n;

        /* is 64 bytes full? */
        if (md->md4.curlen == 64) {
            md4_compress(md);
            md->md4.length += 512;
            md->md4.curlen = 0;
        }
    }
}

void md4_done(hash_state * md, unsigned char *hash)
{
    int i;

    _ARGCHK(md != NULL);
    _ARGCHK(hash != NULL);

    /* increase the length of the message */
    md->md4.length += md->md4.curlen * 8;

    /* append the '1' bit */
    md->md4.buf[md->md4.curlen++] = 0x80;

    /* if the length is currently above 56 bytes we append zeros
     * then compress.  Then we can fall back to padding zeros and length
     * encoding like normal.
     */
    if (md->md4.curlen > 56) {
        while (md->md4.curlen < 64) {
            md->md4.buf[md->md4.curlen++] = 0;
        }
        md4_compress(md);
        md->md4.curlen = 0;
    }

    /* pad upto 56 bytes of zeroes */
    while (md->md4.curlen < 56) {
        md->md4.buf[md->md4.curlen++] = 0;
    }

    /* store length */
    STORE64L(md->md4.length, md->md4.buf+56);
    md4_compress(md);

    /* copy output */
    for (i = 0; i < 4; i++) {
        STORE32L(md->md4.state[i], hash+(4*i));
    }
#ifdef CLEAN_STACK
    zeromem(md, sizeof(hash_state));
#endif
}

int md4_test(void)
{
    static const struct md4_test_case {
        int num;
        unsigned char input[128];
        int inputlen;
        unsigned char digest[16];
    } cases[] = {
        { 1, "", 0,
          {0x31, 0xd6, 0xcf, 0xe0, 0xd1, 0x6a, 0xe9, 0x31,
           0xb7, 0x3c, 0x59, 0xd7, 0xe0, 0xc0, 0x89, 0xc0} },
        { 2, "a", 1,
          {0xbd, 0xe5, 0x2c, 0xb3, 0x1d, 0xe3, 0x3e, 0x46,
           0x24, 0x5e, 0x05, 0xfb, 0xdb, 0xd6, 0xfb, 0x24} },
        { 3, "abc", 3, 
          {0xa4, 0x48, 0x01, 0x7a, 0xaf, 0x21, 0xd8, 0x52, 
           0x5f, 0xc1, 0x0a, 0xe8, 0x7a, 0xa6, 0x72, 0x9d} },
        { 4, "message digest", 14, 
          {0xd9, 0x13, 0x0a, 0x81, 0x64, 0x54, 0x9f, 0xe8, 
           0x18, 0x87, 0x48, 0x06, 0xe1, 0xc7, 0x01, 0x4b} },
        { 5, "abcdefghijklmnopqrstuvwxyz", 26, 
          {0xd7, 0x9e, 0x1c, 0x30, 0x8a, 0xa5, 0xbb, 0xcd, 
           0xee, 0xa8, 0xed, 0x63, 0xdf, 0x41, 0x2d, 0xa9} },
        { 6, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", 62, 
          {0x04, 0x3f, 0x85, 0x82, 0xf2, 0x41, 0xdb, 0x35, 
           0x1c, 0xe6, 0x27, 0xe1, 0x53, 0xe7, 0xf0, 0xe4} },
        { 7, "12345678901234567890123456789012345678901234567890123456789012345678901234567890", 80, 
          {0xe3, 0x3b, 0x4d, 0xdc, 0x9c, 0x38, 0xf2, 0x19, 
           0x9c, 0x3e, 0x7b, 0x16, 0x4f, 0xcc, 0x05, 0x36} },
    };
    int i, failed;
    hash_state md;
    unsigned char digest[16];

    failed = 0;
    for(i = 0; i < (int)(sizeof(cases) / sizeof(cases[0])); i++) {
        md4_init(&md);
        md4_process(&md, cases[i].input, cases[i].inputlen);
        md4_done(&md, digest);
        if(memcmp(digest, cases[i].digest, 16) != 0) {
#if 0
            int j;
            printf("\nMD4 test #%d failed\n", cases[i].num);
            printf(  "Result:  0x"); 
            for(j=0; j < 16; j++) {
               printf("%2x", digest[j]);
            }
            printf("\nCorrect: 0x");
            for(j=0; j < 16; j++) {
               printf("%2x", cases[i].digest[j]);
            }
            printf("\n");
#endif 
            failed++;
        } else {
/*            printf("MD4 test #%d succeeded.\n", cases[i].num); */
        }
    }

    if (failed) {
        return CRYPT_FAIL_TESTVECTOR;
    }

    return CRYPT_OK;
}

#endif


