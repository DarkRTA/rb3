#include "mycrypt.h"

#ifdef SHA1

const struct _hash_descriptor sha1_desc =
{
    "sha1",
    2,
    20,
    64,
    &sha1_init,
    &sha1_process,
    &sha1_done,
    &sha1_test
};

#define F0(x,y,z)  ( (x&y) | ((~x)&z) )
#define F1(x,y,z)  (x ^ y ^ z)
#define F2(x,y,z)  ((x & y) | (z & (x | y)))
#define F3(x,y,z)  (x ^ y ^ z)

#ifdef CLEAN_STACK
static void _sha1_compress(hash_state *md)
#else
static void sha1_compress(hash_state *md)
#endif
{
    unsigned long a,b,c,d,e,W[80],i,j;

    _ARGCHK(md != NULL);

    /* copy the state into 512-bits into W[0..15] */
    for (i = 0; i < 16; i++) {
        LOAD32H(W[i], md->sha1.buf + (4*i));
    }

    /* copy state */
    a = md->sha1.state[0];
    b = md->sha1.state[1];
    c = md->sha1.state[2];
    d = md->sha1.state[3];
    e = md->sha1.state[4];

    /* expand it */
    for (i = 16; i < 80; i++) {
        j = W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16]; 
        W[i] = ROL(j, 1);
    }

    /* compress */
    /* round one */
    for (i = 0;  i < 20; i++)  { 
        j = (ROL(a, 5) + F0(b,c,d) + e + W[i] + 0x5a827999UL); 
        e = d; 
        d = c; 
        c = ROL(b, 30); 
        b = a; 
        a = j; 
    }

    /* round two */
    for (i = 20; i < 40; i++)  { 
        j = (ROL(a, 5) + F1(b,c,d) + e + W[i] + 0x6ed9eba1UL); 
        e = d; 
        d = c; 
        c = ROL(b, 30); 
        b = a; 
        a = j; 
    }

    /* round three */
    for (i = 40; i < 60; i++)  { 
        j = (ROL(a, 5) + F2(b,c,d) + e + W[i] + 0x8f1bbcdcUL); 
        e = d; 
        d = c; 
        c = ROL(b, 30); 
        b = a; 
        a = j; 
    }

    /* round four */
    for (i = 60; i < 80; i++)  { 
        j = (ROL(a, 5) + F3(b,c,d) + e + W[i] + 0xca62c1d6UL);
        e = d;
        d = c;
        c = ROL(b, 30);
        b = a;
        a = j;
    }

    /* store */
    md->sha1.state[0] = md->sha1.state[0] + a;
    md->sha1.state[1] = md->sha1.state[1] + b;
    md->sha1.state[2] = md->sha1.state[2] + c;
    md->sha1.state[3] = md->sha1.state[3] + d;
    md->sha1.state[4] = md->sha1.state[4] + e;
}

#ifdef CLEAN_STACK
static void sha1_compress(hash_state *md)
{
   _sha1_compress(md);
   burn_stack(sizeof(unsigned long) * 87);
}
#endif

void sha1_init(hash_state * md)
{
   _ARGCHK(md != NULL);
   md->sha1.state[0] = 0x67452301UL;
   md->sha1.state[1] = 0xefcdab89UL;
   md->sha1.state[2] = 0x98badcfeUL;
   md->sha1.state[3] = 0x10325476UL;
   md->sha1.state[4] = 0xc3d2e1f0UL;
   md->sha1.curlen = 0;
   md->sha1.length = 0;
}

void sha1_process(hash_state * md, const unsigned char *buf, unsigned long len)
{
    unsigned long n;
    _ARGCHK(md != NULL);
    _ARGCHK(buf != NULL);

    while (len) {
        n = MIN(len, (64 - md->sha1.curlen));
        memcpy(md->sha1.buf + md->sha1.curlen, buf, n);
        md->sha1.curlen += n;
        buf             += n;
        len             -= n;

        /* is 64 bytes full? */
        if (md->sha1.curlen == 64) {
            sha1_compress(md);
            md->sha1.length += 512;
            md->sha1.curlen = 0;
        }
    }
}

void sha1_done(hash_state * md, unsigned char *hash)
{
    int i;

    _ARGCHK(md != NULL);
    _ARGCHK(hash != NULL);

    /* increase the length of the message */
    md->sha1.length += md->sha1.curlen * 8;

    /* append the '1' bit */
    md->sha1.buf[md->sha1.curlen++] = 0x80;

    /* if the length is currently above 56 bytes we append zeros
     * then compress.  Then we can fall back to padding zeros and length
     * encoding like normal.
     */
    if (md->sha1.curlen > 56) {
        while (md->sha1.curlen < 64) {
            md->sha1.buf[md->sha1.curlen++] = 0;
        }
        sha1_compress(md);
        md->sha1.curlen = 0;
    }

    /* pad upto 56 bytes of zeroes */
    while (md->sha1.curlen < 56) {
        md->sha1.buf[md->sha1.curlen++] = 0;
    }

    /* store length */
    STORE64H(md->sha1.length, md->sha1.buf+56);
    sha1_compress(md);

    /* copy output */
    for (i = 0; i < 5; i++) {
        STORE32H(md->sha1.state[i], hash+(4*i));
    }
#ifdef CLEAN_STACK
    zeromem(md, sizeof(hash_state));
#endif
}

int  sha1_test(void)
{
  static const struct {
      unsigned char *msg;
      unsigned char hash[20];
  } tests[] = {
    { "abc",
      { 0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a,
        0xba, 0x3e, 0x25, 0x71, 0x78, 0x50, 0xc2, 0x6c,
        0x9c, 0xd0, 0xd8, 0x9d }
    },
    { "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
      { 0x84, 0x98, 0x3E, 0x44, 0x1C, 0x3B, 0xD2, 0x6E,
        0xBA, 0xAE, 0x4A, 0xA1, 0xF9, 0x51, 0x29, 0xE5,
        0xE5, 0x46, 0x70, 0xF1 }
    }, 
    { NULL, { 0 }}
  };

  int failed, i;
  unsigned char tmp[20];
  hash_state md;

  for (failed = i = 0; tests[i].msg != NULL; i++) {
      sha1_init(&md);
      sha1_process(&md, tests[i].msg, strlen(tests[i].msg));
      sha1_done(&md, tmp);
      if (memcmp(tmp, tests[i].hash, 20)) {
#if 0
         int j;
         printf("\nSHA-1 Test %d failed\nGot (as a result): ", i);
         for (j = 0; j < 20; j++) {
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

#endif


