/*******************************************************************************
*
* FILE:           safer.c
*
* DESCRIPTION:    block-cipher algorithm SAFER (Secure And Fast Encryption
*                 Routine) in its four versions: SAFER K-64, SAFER K-128,
*                 SAFER SK-64 and SAFER SK-128.
*
* AUTHOR:         Richard De Moliner (demoliner@isi.ee.ethz.ch)
*                 Signal and Information Processing Laboratory
*                 Swiss Federal Institute of Technology
*                 CH-8092 Zuerich, Switzerland
*
* DATE:           September 9, 1995
*
* CHANGE HISTORY:
*
*******************************************************************************/

#include <mycrypt.h>

#ifdef SAFER

const struct _cipher_descriptor 
   safer_k64_desc = {
   "safer-k64", 
   8, 8, 8, 8, SAFER_K64_DEFAULT_NOF_ROUNDS,
   &safer_k64_setup,
   &safer_ecb_encrypt,
   &safer_ecb_decrypt,
   &safer_k64_test,
   &safer_64_keysize
   },

   safer_sk64_desc = {
   "safer-sk64",
   9, 8, 8, 8, SAFER_SK64_DEFAULT_NOF_ROUNDS,
   &safer_sk64_setup,
   &safer_ecb_encrypt,
   &safer_ecb_decrypt,
   &safer_sk64_test,
   &safer_64_keysize
   },

   safer_k128_desc = {
   "safer-k128",
   10, 16, 16, 8, SAFER_K128_DEFAULT_NOF_ROUNDS,
   &safer_k128_setup,
   &safer_ecb_encrypt,
   &safer_ecb_decrypt,
   &safer_sk128_test,
   &safer_128_keysize
   },

   safer_sk128_desc = {
   "safer-sk128",
   11, 16, 16, 8, SAFER_SK128_DEFAULT_NOF_ROUNDS,
   &safer_sk128_setup,
   &safer_ecb_encrypt,
   &safer_ecb_decrypt,
   &safer_sk128_test,
   &safer_128_keysize
   };

/******************* Constants ************************************************/
// #define TAB_LEN      256

/******************* Assertions ***********************************************/

/******************* Macros ***************************************************/
#define ROL8(x, n)   ((unsigned char)((unsigned int)(x) << (n)\
                                     |(unsigned int)((x) & 0xFF) >> (8 - (n))))
#define EXP(x)       safer_ebox[(x) & 0xFF]
#define LOG(x)       safer_lbox[(x) & 0xFF]
#define PHT(x, y)    { y += x; x += y; }
#define IPHT(x, y)   { x -= y; y -= x; }

/******************* Types ****************************************************/
extern const unsigned char safer_ebox[], safer_lbox[];

#ifdef CLEAN_STACK
static void _Safer_Expand_Userkey(const unsigned char *userkey_1,
                                 const unsigned char *userkey_2,
                                 unsigned int nof_rounds,
                                 int strengthened,
                                 safer_key_t key)
#else
static void Safer_Expand_Userkey(const unsigned char *userkey_1,
                                 const unsigned char *userkey_2,
                                 unsigned int nof_rounds,
                                 int strengthened,
                                 safer_key_t key)
#endif
{   unsigned int i, j;
    unsigned char ka[SAFER_BLOCK_LEN + 1];
    unsigned char kb[SAFER_BLOCK_LEN + 1];

    if (SAFER_MAX_NOF_ROUNDS < nof_rounds)
        nof_rounds = SAFER_MAX_NOF_ROUNDS;
    *key++ = (unsigned char)nof_rounds;
    ka[SAFER_BLOCK_LEN] = 0;
    kb[SAFER_BLOCK_LEN] = 0;
    for (j = 0; j < SAFER_BLOCK_LEN; j++)
    {
        ka[SAFER_BLOCK_LEN] ^= ka[j] = ROL8(userkey_1[j], 5);
        kb[SAFER_BLOCK_LEN] ^= kb[j] = *key++ = userkey_2[j];
    }
    for (i = 1; i <= nof_rounds; i++)
    {
        for (j = 0; j < SAFER_BLOCK_LEN + 1; j++)
        {
            ka[j] = ROL8(ka[j], 6);
            kb[j] = ROL8(kb[j], 6);
        }
        for (j = 0; j < SAFER_BLOCK_LEN; j++)
            if (strengthened)
                *key++ = (ka[(j + 2 * i - 1) % (SAFER_BLOCK_LEN + 1)]
                                + safer_ebox[safer_ebox[18 * i + j + 1]]) & 0xFF;
            else
                *key++ = (ka[j] + safer_ebox[safer_ebox[18 * i + j + 1]]) & 0xFF;
        for (j = 0; j < SAFER_BLOCK_LEN; j++)
            if (strengthened)
                *key++ = (kb[(j + 2 * i) % (SAFER_BLOCK_LEN + 1)]
                                + safer_ebox[safer_ebox[18 * i + j + 10]]) & 0xFF;
            else
                *key++ = (kb[j] + safer_ebox[safer_ebox[18 * i + j + 10]]) & 0xFF;
    }
    
#ifdef CLEAN_STACK
    zeromem(ka, sizeof(ka));
    zeromem(kb, sizeof(kb));
#endif
}

#ifdef CLEAN_STACK
static void Safer_Expand_Userkey(const unsigned char *userkey_1,
                                 const unsigned char *userkey_2,
                                 unsigned int nof_rounds,
                                 int strengthened,
                                 safer_key_t key)
{
   _Safer_Expand_Userkey(userkey_1, userkey_2, nof_rounds, strengthened, key);
   burn_stack(sizeof(unsigned char) * (2 * (SAFER_BLOCK_LEN + 1)) + sizeof(unsigned int)*2);
}
#endif

int safer_k64_setup(const unsigned char *key, int keylen, int numrounds, symmetric_key *skey)
{
   _ARGCHK(key != NULL);
   _ARGCHK(skey != NULL);

   if (numrounds && (numrounds < 6 || numrounds > SAFER_MAX_NOF_ROUNDS)) {
      return CRYPT_INVALID_ROUNDS;
   }

   if (keylen != 8) {
      return CRYPT_INVALID_KEYSIZE;
   }

   Safer_Expand_Userkey(key, key, numrounds?numrounds:SAFER_K64_DEFAULT_NOF_ROUNDS, 0, skey->safer.key);
   return CRYPT_OK;
}
   
int safer_sk64_setup(const unsigned char *key, int keylen, int numrounds, symmetric_key *skey)
{
   _ARGCHK(key != NULL);
   _ARGCHK(skey != NULL);

   if (numrounds && (numrounds < 6 || numrounds > SAFER_MAX_NOF_ROUNDS)) {
      return CRYPT_INVALID_ROUNDS;
   }

   if (keylen != 8) {
      return CRYPT_INVALID_KEYSIZE;
   }

   Safer_Expand_Userkey(key, key, numrounds?numrounds:SAFER_SK64_DEFAULT_NOF_ROUNDS, 1, skey->safer.key);
   return CRYPT_OK;
}

int safer_k128_setup(const unsigned char *key, int keylen, int numrounds, symmetric_key *skey)
{
   _ARGCHK(key != NULL);
   _ARGCHK(skey != NULL);

   if (numrounds && (numrounds < 6 || numrounds > SAFER_MAX_NOF_ROUNDS)) {
      return CRYPT_INVALID_ROUNDS;
   }

   if (keylen != 16) {
      return CRYPT_INVALID_KEYSIZE;
   }

   Safer_Expand_Userkey(key, key+8, numrounds?numrounds:SAFER_K128_DEFAULT_NOF_ROUNDS, 0, skey->safer.key);
   return CRYPT_OK;
}

int safer_sk128_setup(const unsigned char *key, int keylen, int numrounds, symmetric_key *skey)
{
   _ARGCHK(key != NULL);
   _ARGCHK(skey != NULL);

   if (numrounds && (numrounds < 6 || numrounds > SAFER_MAX_NOF_ROUNDS)) {
      return CRYPT_INVALID_ROUNDS;
   }

   if (keylen != 16) {
      return CRYPT_INVALID_KEYSIZE;
   }

   Safer_Expand_Userkey(key, key+8, numrounds?numrounds:SAFER_SK128_DEFAULT_NOF_ROUNDS, 1, skey->safer.key);
   return CRYPT_OK;
}

#ifdef CLEAN_STACK
static void _safer_ecb_encrypt(const unsigned char *block_in,
                             unsigned char *block_out,
                             symmetric_key *skey)
#else
void safer_ecb_encrypt(const unsigned char *block_in,
                             unsigned char *block_out,
                             symmetric_key *skey)
#endif
{   unsigned char a, b, c, d, e, f, g, h, t;
    unsigned int round;
    unsigned char *key;

    _ARGCHK(block_in != NULL);
    _ARGCHK(block_out != NULL);
    _ARGCHK(skey != NULL);

    key = skey->safer.key;
    a = block_in[0]; b = block_in[1]; c = block_in[2]; d = block_in[3];
    e = block_in[4]; f = block_in[5]; g = block_in[6]; h = block_in[7];
    if (SAFER_MAX_NOF_ROUNDS < (round = *key)) round = SAFER_MAX_NOF_ROUNDS;
    while(round--)
    {
        a ^= *++key; b += *++key; c += *++key; d ^= *++key;
        e ^= *++key; f += *++key; g += *++key; h ^= *++key;
        a = EXP(a) + *++key; b = LOG(b) ^ *++key;
        c = LOG(c) ^ *++key; d = EXP(d) + *++key;
        e = EXP(e) + *++key; f = LOG(f) ^ *++key;
        g = LOG(g) ^ *++key; h = EXP(h) + *++key;
        PHT(a, b); PHT(c, d); PHT(e, f); PHT(g, h);
        PHT(a, c); PHT(e, g); PHT(b, d); PHT(f, h);
        PHT(a, e); PHT(b, f); PHT(c, g); PHT(d, h);
        t = b; b = e; e = c; c = t; t = d; d = f; f = g; g = t;
    }
    a ^= *++key; b += *++key; c += *++key; d ^= *++key;
    e ^= *++key; f += *++key; g += *++key; h ^= *++key;
    block_out[0] = a & 0xFF; block_out[1] = b & 0xFF;
    block_out[2] = c & 0xFF; block_out[3] = d & 0xFF;
    block_out[4] = e & 0xFF; block_out[5] = f & 0xFF;
    block_out[6] = g & 0xFF; block_out[7] = h & 0xFF;
}

#ifdef CLEAN_STACK
void safer_ecb_encrypt(const unsigned char *block_in,
                             unsigned char *block_out,
                             symmetric_key *skey)
{
    _safer_ecb_encrypt(block_in, block_out, skey);
    burn_stack(sizeof(unsigned char) * 9 + sizeof(unsigned int) + sizeof(unsigned char *));
}
#endif

#ifdef CLEAN_STACK
static void _safer_ecb_decrypt(const unsigned char *block_in,
                             unsigned char *block_out,
                             symmetric_key *skey)
#else
void safer_ecb_decrypt(const unsigned char *block_in,
                             unsigned char *block_out,
                             symmetric_key *skey)
#endif
{   unsigned char a, b, c, d, e, f, g, h, t;
    unsigned int round;
    unsigned char *key;

    _ARGCHK(block_in != NULL);
    _ARGCHK(block_out != NULL);
    _ARGCHK(skey != NULL);

    key = skey->safer.key;
    a = block_in[0]; b = block_in[1]; c = block_in[2]; d = block_in[3];
    e = block_in[4]; f = block_in[5]; g = block_in[6]; h = block_in[7];
    if (SAFER_MAX_NOF_ROUNDS < (round = *key)) round = SAFER_MAX_NOF_ROUNDS;
    key += SAFER_BLOCK_LEN * (1 + 2 * round);
    h ^= *key; g -= *--key; f -= *--key; e ^= *--key;
    d ^= *--key; c -= *--key; b -= *--key; a ^= *--key;
    while (round--)
    {
        t = e; e = b; b = c; c = t; t = f; f = d; d = g; g = t;
        IPHT(a, e); IPHT(b, f); IPHT(c, g); IPHT(d, h);
        IPHT(a, c); IPHT(e, g); IPHT(b, d); IPHT(f, h);
        IPHT(a, b); IPHT(c, d); IPHT(e, f); IPHT(g, h);
        h -= *--key; g ^= *--key; f ^= *--key; e -= *--key;
        d -= *--key; c ^= *--key; b ^= *--key; a -= *--key;
        h = LOG(h) ^ *--key; g = EXP(g) - *--key;
        f = EXP(f) - *--key; e = LOG(e) ^ *--key;
        d = LOG(d) ^ *--key; c = EXP(c) - *--key;
        b = EXP(b) - *--key; a = LOG(a) ^ *--key;
    }
    block_out[0] = a & 0xFF; block_out[1] = b & 0xFF;
    block_out[2] = c & 0xFF; block_out[3] = d & 0xFF;
    block_out[4] = e & 0xFF; block_out[5] = f & 0xFF;
    block_out[6] = g & 0xFF; block_out[7] = h & 0xFF;
}

#ifdef CLEAN_STACK
void safer_ecb_decrypt(const unsigned char *block_in,
                             unsigned char *block_out,
                             symmetric_key *skey)
{
    _safer_ecb_decrypt(block_in, block_out, skey);
    burn_stack(sizeof(unsigned char) * 9 + sizeof(unsigned int) + sizeof(unsigned char *));
}
#endif

int safer_64_keysize(int *keysize)
{
   _ARGCHK(keysize != NULL);
   if (*keysize < 8) {
      return CRYPT_INVALID_KEYSIZE;
   } else {
      *keysize = 8;
      return CRYPT_OK;
   }
}

int safer_128_keysize(int *keysize)
{
   _ARGCHK(keysize != NULL);
   if (*keysize < 16) {
      return CRYPT_INVALID_KEYSIZE;
   } else {
      *keysize = 16;
      return CRYPT_OK;
   }
}

int safer_k64_test(void)
{
   static const unsigned char k64_pt[]  = { 1, 2, 3, 4, 5, 6, 7, 8 },
                              k64_key[] = { 8, 7, 6, 5, 4, 3, 2, 1 },
                              k64_ct[]  = { 200, 242, 156, 221, 135, 120, 62, 217 };

   symmetric_key skey;
   unsigned char buf[2][8];
   int errno;

   /* test K64 */
   if ((errno = safer_k64_setup(k64_key, 8, 6, &skey)) != CRYPT_OK) {
      return errno;
   }
   safer_ecb_encrypt(k64_pt, buf[0], &skey);
   safer_ecb_decrypt(buf[0], buf[1], &skey);

   if (memcmp(buf[0], k64_ct, 8) || memcmp(buf[1], k64_pt, 8)) {
      return CRYPT_FAIL_TESTVECTOR;
   }

   return CRYPT_OK;
}


int safer_sk64_test(void)
{
   static const unsigned char sk64_pt[]  = { 1, 2, 3, 4, 5, 6, 7, 8 },
                              sk64_key[] = { 1, 2, 3, 4, 5, 6, 7, 8 },
                              sk64_ct[]  = { 95, 206, 155, 162, 5, 132, 56, 199 };

   symmetric_key skey;
   unsigned char buf[2][8];
   int errno;

   /* test SK64 */
   if ((errno = safer_sk64_setup(sk64_key, 8, 6, &skey)) != CRYPT_OK) {
      return errno;
   }

   safer_ecb_encrypt(sk64_pt, buf[0], &skey);
   safer_ecb_decrypt(buf[0], buf[1], &skey);

   if (memcmp(buf[0], sk64_ct, 8) || memcmp(buf[1], sk64_pt, 8)) {
      return CRYPT_FAIL_TESTVECTOR;
   }

   return CRYPT_OK;
}

int safer_sk128_test(void)
{
   static const unsigned char sk128_pt[]  = { 1, 2, 3, 4, 5, 6, 7, 8 },
                              sk128_key[] = { 1, 2, 3, 4, 5, 6, 7, 8,
                                              0, 0, 0, 0, 0, 0, 0, 0 },
                              sk128_ct[]  = { 255, 120, 17, 228, 179, 167, 46, 113 };

   symmetric_key skey;
   unsigned char buf[2][8];
   int errno;

   /* test SK128 */
   if ((errno = safer_sk128_setup(sk128_key, 16, 0, &skey)) != CRYPT_OK) {
      return errno;
   }
   safer_ecb_encrypt(sk128_pt, buf[0], &skey);
   safer_ecb_decrypt(buf[0], buf[1], &skey);

   if (memcmp(buf[0], sk128_ct, 8) || memcmp(buf[1], sk128_pt, 8)) {
      return CRYPT_FAIL_TESTVECTOR;
   }


   return CRYPT_OK;
}

#endif



