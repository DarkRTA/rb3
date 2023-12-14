#include "mycrypt.h"

#ifdef SHA512

const struct _hash_descriptor sha512_desc =
{
    "sha512",
    5,
    64,
    128,
    &sha512_init,
    &sha512_process,
    &sha512_done,
    &sha512_test
};

/* the K array */
static const ulong64 K[80] = {
CONST64(0x428a2f98d728ae22), CONST64(0x7137449123ef65cd), 
CONST64(0xb5c0fbcfec4d3b2f), CONST64(0xe9b5dba58189dbbc),
CONST64(0x3956c25bf348b538), CONST64(0x59f111f1b605d019), 
CONST64(0x923f82a4af194f9b), CONST64(0xab1c5ed5da6d8118),
CONST64(0xd807aa98a3030242), CONST64(0x12835b0145706fbe), 
CONST64(0x243185be4ee4b28c), CONST64(0x550c7dc3d5ffb4e2),
CONST64(0x72be5d74f27b896f), CONST64(0x80deb1fe3b1696b1), 
CONST64(0x9bdc06a725c71235), CONST64(0xc19bf174cf692694),
CONST64(0xe49b69c19ef14ad2), CONST64(0xefbe4786384f25e3), 
CONST64(0x0fc19dc68b8cd5b5), CONST64(0x240ca1cc77ac9c65),
CONST64(0x2de92c6f592b0275), CONST64(0x4a7484aa6ea6e483), 
CONST64(0x5cb0a9dcbd41fbd4), CONST64(0x76f988da831153b5),
CONST64(0x983e5152ee66dfab), CONST64(0xa831c66d2db43210), 
CONST64(0xb00327c898fb213f), CONST64(0xbf597fc7beef0ee4),
CONST64(0xc6e00bf33da88fc2), CONST64(0xd5a79147930aa725), 
CONST64(0x06ca6351e003826f), CONST64(0x142929670a0e6e70),
CONST64(0x27b70a8546d22ffc), CONST64(0x2e1b21385c26c926), 
CONST64(0x4d2c6dfc5ac42aed), CONST64(0x53380d139d95b3df),
CONST64(0x650a73548baf63de), CONST64(0x766a0abb3c77b2a8), 
CONST64(0x81c2c92e47edaee6), CONST64(0x92722c851482353b),
CONST64(0xa2bfe8a14cf10364), CONST64(0xa81a664bbc423001),
CONST64(0xc24b8b70d0f89791), CONST64(0xc76c51a30654be30),
CONST64(0xd192e819d6ef5218), CONST64(0xd69906245565a910), 
CONST64(0xf40e35855771202a), CONST64(0x106aa07032bbd1b8),
CONST64(0x19a4c116b8d2d0c8), CONST64(0x1e376c085141ab53), 
CONST64(0x2748774cdf8eeb99), CONST64(0x34b0bcb5e19b48a8),
CONST64(0x391c0cb3c5c95a63), CONST64(0x4ed8aa4ae3418acb), 
CONST64(0x5b9cca4f7763e373), CONST64(0x682e6ff3d6b2b8a3),
CONST64(0x748f82ee5defb2fc), CONST64(0x78a5636f43172f60), 
CONST64(0x84c87814a1f0ab72), CONST64(0x8cc702081a6439ec),
CONST64(0x90befffa23631e28), CONST64(0xa4506cebde82bde9), 
CONST64(0xbef9a3f7b2c67915), CONST64(0xc67178f2e372532b),
CONST64(0xca273eceea26619c), CONST64(0xd186b8c721c0c207), 
CONST64(0xeada7dd6cde0eb1e), CONST64(0xf57d4f7fee6ed178),
CONST64(0x06f067aa72176fba), CONST64(0x0a637dc5a2c898a6), 
CONST64(0x113f9804bef90dae), CONST64(0x1b710b35131c471b),
CONST64(0x28db77f523047d84), CONST64(0x32caab7b40c72493), 
CONST64(0x3c9ebe0a15c9bebc), CONST64(0x431d67c49c100d4c),
CONST64(0x4cc5d4becb3e42b6), CONST64(0x597f299cfc657e2a), 
CONST64(0x5fcb6fab3ad6faec), CONST64(0x6c44198c4a475817)
};

/* Various logical functions */
#define Ch(x,y,z)       ((x & y) ^ (~x & z))
#define Maj(x,y,z)      ((x & y) ^ (x & z) ^ (y & z))
#define S(x, n)         ROR64((x),(n))
#define R(x, n)         (((x)&CONST64(0xFFFFFFFFFFFFFFFF))>>((ulong64)n))
#define Sigma0(x)       (S(x, 28) ^ S(x, 34) ^ S(x, 39))
#define Sigma1(x)       (S(x, 14) ^ S(x, 18) ^ S(x, 41))
#define Gamma0(x)       (S(x, 1) ^ S(x, 8) ^ R(x, 7))
#define Gamma1(x)       (S(x, 19) ^ S(x, 61) ^ R(x, 6))

/* compress 1024-bits */
#ifdef CLEAN_STACK
static void _sha512_compress(hash_state * md)
#else
static void sha512_compress(hash_state * md)
#endif
{
    ulong64 S[8], W[80], t0, t1;
    int i;

    _ARGCHK(md != NULL);

    /* copy state into S */
    for (i = 0; i < 8; i++)
        S[i] = md->sha512.state[i];

    /* copy the state into 1024-bits into W[0..15] */
    for (i = 0; i < 16; i++) {
        LOAD64H(W[i], md->sha512.buf + (8*i));
    }

    /* fill W[16..79] */
    for (i = 16; i < 80; i++)
        W[i] = Gamma1(W[i - 2]) + W[i - 7] + Gamma0(W[i - 15]) + W[i - 16];

    /* Compress */
    for (i = 0; i < 80; i++) {
        t0 = S[7] + Sigma1(S[4]) + Ch(S[4], S[5], S[6]) + K[i] + W[i];
        t1 = Sigma0(S[0]) + Maj(S[0], S[1], S[2]);
        S[7] = S[6];
        S[6] = S[5];
        S[5] = S[4];
        S[4] = S[3] + t0;
        S[3] = S[2];
        S[2] = S[1];
        S[1] = S[0];
        S[0] = t0 + t1;
    }

    /* feedback */
    for (i = 0; i < 8; i++) {
        md->sha512.state[i] = md->sha512.state[i] + S[i];
    }
}

/* compress 1024-bits */
#ifdef CLEAN_STACK
static void sha512_compress(hash_state * md)
{
    _sha512_compress(md);
    burn_stack(sizeof(ulong64) * 90 + sizeof(int));
}
#endif

/* init the sha512 state */
void sha512_init(hash_state * md)
{
    _ARGCHK(md != NULL);

    md->sha512.curlen = 0;
    md->sha512.length = 0;
    md->sha512.state[0] = CONST64(0x6a09e667f3bcc908);
    md->sha512.state[1] = CONST64(0xbb67ae8584caa73b);
    md->sha512.state[2] = CONST64(0x3c6ef372fe94f82b);
    md->sha512.state[3] = CONST64(0xa54ff53a5f1d36f1);
    md->sha512.state[4] = CONST64(0x510e527fade682d1);
    md->sha512.state[5] = CONST64(0x9b05688c2b3e6c1f);
    md->sha512.state[6] = CONST64(0x1f83d9abfb41bd6b);
    md->sha512.state[7] = CONST64(0x5be0cd19137e2179);
}

void sha512_process(hash_state * md, const unsigned char *buf, unsigned long len)
{
    unsigned long n;
    _ARGCHK(md != NULL);
    _ARGCHK(buf != NULL);
    while (len) {
        n = MIN(len, (128 - md->sha512.curlen));
        memcpy(md->sha512.buf + md->sha512.curlen, buf, n);
        md->sha512.curlen += n;
        buf               += n;
        len               -= n;

        /* is 64 bytes full? */
        if (md->sha512.curlen == 128) {
            sha512_compress(md);
            md->sha512.length += 1024;
            md->sha512.curlen = 0;
        }
    }
}

void sha512_done(hash_state * md, unsigned char *hash)
{
    int i;

    _ARGCHK(md != NULL);
    _ARGCHK(hash != NULL);

    /* increase the length of the message */
    md->sha512.length += md->sha512.curlen * CONST64(8);

    /* append the '1' bit */
    md->sha512.buf[md->sha512.curlen++] = 0x80;

    /* if the length is currently above 112 bytes we append zeros
     * then compress.  Then we can fall back to padding zeros and length
     * encoding like normal.
     */
    if (md->sha512.curlen > 112) {
        while (md->sha512.curlen < 128) {
            md->sha512.buf[md->sha512.curlen++] = 0;
        }
        sha512_compress(md);
        md->sha512.curlen = 0;
    }

    /* pad upto 120 bytes of zeroes 
     * note: that from 112 to 120 is the 64 MSB of the length.  We assume that you won't hash
     * > 2^64 bits of data... :-)
     */
    while (md->sha512.curlen < 120) {
        md->sha512.buf[md->sha512.curlen++] = 0;
    }

    /* store length */
    STORE64H(md->sha512.length, md->sha512.buf+120);
    sha512_compress(md);

    /* copy output */
    for (i = 0; i < 8; i++) {
        STORE64H(md->sha512.state[i], hash+(8*i));
    }
#ifdef CLEAN_STACK
    zeromem(md, sizeof(hash_state));
#endif
}

int  sha512_test(void)
{
  static const struct {
      unsigned char *msg;
      unsigned char hash[64];
  } tests[] = {
    { "abc",
     { 0xdd, 0xaf, 0x35, 0xa1, 0x93, 0x61, 0x7a, 0xba,
       0xcc, 0x41, 0x73, 0x49, 0xae, 0x20, 0x41, 0x31,
       0x12, 0xe6, 0xfa, 0x4e, 0x89, 0xa9, 0x7e, 0xa2,
       0x0a, 0x9e, 0xee, 0xe6, 0x4b, 0x55, 0xd3, 0x9a,
       0x21, 0x92, 0x99, 0x2a, 0x27, 0x4f, 0xc1, 0xa8,
       0x36, 0xba, 0x3c, 0x23, 0xa3, 0xfe, 0xeb, 0xbd,
       0x45, 0x4d, 0x44, 0x23, 0x64, 0x3c, 0xe8, 0x0e,
       0x2a, 0x9a, 0xc9, 0x4f, 0xa5, 0x4c, 0xa4, 0x9f }
    },
    { "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
     { 0x8e, 0x95, 0x9b, 0x75, 0xda, 0xe3, 0x13, 0xda,
       0x8c, 0xf4, 0xf7, 0x28, 0x14, 0xfc, 0x14, 0x3f,
       0x8f, 0x77, 0x79, 0xc6, 0xeb, 0x9f, 0x7f, 0xa1,
       0x72, 0x99, 0xae, 0xad, 0xb6, 0x88, 0x90, 0x18,
       0x50, 0x1d, 0x28, 0x9e, 0x49, 0x00, 0xf7, 0xe4,
       0x33, 0x1b, 0x99, 0xde, 0xc4, 0xb5, 0x43, 0x3a,
       0xc7, 0xd3, 0x29, 0xee, 0xb6, 0xdd, 0x26, 0x54,
       0x5e, 0x96, 0xe5, 0x5b, 0x87, 0x4b, 0xe9, 0x09 }
    },
    { NULL, { 0 }}
  };

  int failed, i;
  unsigned char tmp[64];
  hash_state md;

  for (failed = i = 0; tests[i].msg != NULL; i++) {
      sha512_init(&md);
      sha512_process(&md, tests[i].msg, strlen(tests[i].msg));
      sha512_done(&md, tmp);
      if (memcmp(tmp, tests[i].hash, 64)) {
#if 0
         int j;
         printf("\nSHA-512 Test %d failed\nGot (as a result): ", i);
         for (j = 0; j < 64; j++) {
             printf("%02x ", tmp[j]);
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

#ifdef SHA384
   #include "sha384.c"
#endif

#endif



