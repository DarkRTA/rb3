/* DES code submitted by Dobes Vandermeer */
#include "mycrypt.h"

#ifdef DES

#define EN0 0 
#define DE1 1

const struct _cipher_descriptor des_desc =
{
    "des",
    13,
    8, 8, 8, 16,
    &des_setup,
    &des_ecb_encrypt,
    &des_ecb_decrypt,
    &des_test,
    &des_keysize
};

const struct _cipher_descriptor des3_desc =
{
    "3des",
    14,
    24, 24, 8, 16,
    &des3_setup,
    &des3_ecb_encrypt,
    &des3_ecb_decrypt,
    &des3_test,
    &des3_keysize
};

static const unsigned char Df_Key[24] =
{
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
    0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67 
};

static const unsigned short bytebit[8] =
{
    0200, 0100, 040, 020, 010, 04, 02, 01 
};

static const unsigned long bigbyte[24] =
{
    0x800000L,  0x400000L,  0x200000L,  0x100000L,
    0x80000L,   0x40000L,   0x20000L,   0x10000L,
    0x8000L,    0x4000L,    0x2000L,    0x1000L,
    0x800L,     0x400L,     0x200L,     0x100L,
    0x80L,      0x40L,      0x20L,      0x10L,
    0x8L,       0x4L,       0x2L,       0x1L 
};

/* Use the key schedule specific in the standard (ANSI X3.92-1981) */

static const unsigned char pc1[56] = {
    56, 48, 40, 32, 24, 16,  8,  0, 57, 49, 41, 33, 25, 17,  
     9,  1, 58, 50, 42, 34, 26, 18, 10,  2, 59, 51, 43, 35, 
    62, 54, 46, 38, 30, 22, 14,  6, 61, 53, 45, 37, 29, 21,
    13,  5, 60, 52, 44, 36, 28, 20, 12,  4, 27, 19, 11,  3 
};

static const unsigned char totrot[16] = {
    1,   2,  4,  6,
    8,  10, 12, 14, 
    15, 17, 19, 21, 
    23, 25, 27, 28
};

static const unsigned char pc2[48] = {
    13, 16, 10, 23,  0,  4,      2, 27, 14,  5, 20,  9,
    22, 18, 11,  3, 25,  7,     15,  6, 26, 19, 12,  1,
    40, 51, 30, 36, 46, 54,     29, 39, 50, 44, 32, 47,
    43, 48, 38, 55, 33, 52,     45, 41, 49, 35, 28, 31
};


static const unsigned long SP1[64] =
{
    0x01010400L, 0x00000000L, 0x00010000L, 0x01010404L,
    0x01010004L, 0x00010404L, 0x00000004L, 0x00010000L,
    0x00000400L, 0x01010400L, 0x01010404L, 0x00000400L,
    0x01000404L, 0x01010004L, 0x01000000L, 0x00000004L,
    0x00000404L, 0x01000400L, 0x01000400L, 0x00010400L,
    0x00010400L, 0x01010000L, 0x01010000L, 0x01000404L,
    0x00010004L, 0x01000004L, 0x01000004L, 0x00010004L,
    0x00000000L, 0x00000404L, 0x00010404L, 0x01000000L,
    0x00010000L, 0x01010404L, 0x00000004L, 0x01010000L,
    0x01010400L, 0x01000000L, 0x01000000L, 0x00000400L,
    0x01010004L, 0x00010000L, 0x00010400L, 0x01000004L,
    0x00000400L, 0x00000004L, 0x01000404L, 0x00010404L,
    0x01010404L, 0x00010004L, 0x01010000L, 0x01000404L,
    0x01000004L, 0x00000404L, 0x00010404L, 0x01010400L,
    0x00000404L, 0x01000400L, 0x01000400L, 0x00000000L,
    0x00010004L, 0x00010400L, 0x00000000L, 0x01010004
};

static const unsigned long SP2[64] =
{
    0x80108020L, 0x80008000L, 0x00008000L, 0x00108020L,
    0x00100000L, 0x00000020L, 0x80100020L, 0x80008020L,
    0x80000020L, 0x80108020L, 0x80108000L, 0x80000000L,
    0x80008000L, 0x00100000L, 0x00000020L, 0x80100020L,
    0x00108000L, 0x00100020L, 0x80008020L, 0x00000000L,
    0x80000000L, 0x00008000L, 0x00108020L, 0x80100000L,
    0x00100020L, 0x80000020L, 0x00000000L, 0x00108000L,
    0x00008020L, 0x80108000L, 0x80100000L, 0x00008020L,
    0x00000000L, 0x00108020L, 0x80100020L, 0x00100000L,
    0x80008020L, 0x80100000L, 0x80108000L, 0x00008000L,
    0x80100000L, 0x80008000L, 0x00000020L, 0x80108020L,
    0x00108020L, 0x00000020L, 0x00008000L, 0x80000000L,
    0x00008020L, 0x80108000L, 0x00100000L, 0x80000020L,
    0x00100020L, 0x80008020L, 0x80000020L, 0x00100020L,
    0x00108000L, 0x00000000L, 0x80008000L, 0x00008020L,
    0x80000000L, 0x80100020L, 0x80108020L, 0x00108000
};

static const unsigned long SP3[64] =
{
    0x00000208L, 0x08020200L, 0x00000000L, 0x08020008L,
    0x08000200L, 0x00000000L, 0x00020208L, 0x08000200L,
    0x00020008L, 0x08000008L, 0x08000008L, 0x00020000L,
    0x08020208L, 0x00020008L, 0x08020000L, 0x00000208L,
    0x08000000L, 0x00000008L, 0x08020200L, 0x00000200L,
    0x00020200L, 0x08020000L, 0x08020008L, 0x00020208L,
    0x08000208L, 0x00020200L, 0x00020000L, 0x08000208L,
    0x00000008L, 0x08020208L, 0x00000200L, 0x08000000L,
    0x08020200L, 0x08000000L, 0x00020008L, 0x00000208L,
    0x00020000L, 0x08020200L, 0x08000200L, 0x00000000L,
    0x00000200L, 0x00020008L, 0x08020208L, 0x08000200L,
    0x08000008L, 0x00000200L, 0x00000000L, 0x08020008L,
    0x08000208L, 0x00020000L, 0x08000000L, 0x08020208L,
    0x00000008L, 0x00020208L, 0x00020200L, 0x08000008L,
    0x08020000L, 0x08000208L, 0x00000208L, 0x08020000L,
    0x00020208L, 0x00000008L, 0x08020008L, 0x00020200
};

static const unsigned long SP4[64] =
{
    0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
    0x00802080L, 0x00800081L, 0x00800001L, 0x00002001L,
    0x00000000L, 0x00802000L, 0x00802000L, 0x00802081L,
    0x00000081L, 0x00000000L, 0x00800080L, 0x00800001L,
    0x00000001L, 0x00002000L, 0x00800000L, 0x00802001L,
    0x00000080L, 0x00800000L, 0x00002001L, 0x00002080L,
    0x00800081L, 0x00000001L, 0x00002080L, 0x00800080L,
    0x00002000L, 0x00802080L, 0x00802081L, 0x00000081L,
    0x00800080L, 0x00800001L, 0x00802000L, 0x00802081L,
    0x00000081L, 0x00000000L, 0x00000000L, 0x00802000L,
    0x00002080L, 0x00800080L, 0x00800081L, 0x00000001L,
    0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
    0x00802081L, 0x00000081L, 0x00000001L, 0x00002000L,
    0x00800001L, 0x00002001L, 0x00802080L, 0x00800081L,
    0x00002001L, 0x00002080L, 0x00800000L, 0x00802001L,
    0x00000080L, 0x00800000L, 0x00002000L, 0x00802080
};

static const unsigned long SP5[64] =
{
    0x00000100L, 0x02080100L, 0x02080000L, 0x42000100L,
    0x00080000L, 0x00000100L, 0x40000000L, 0x02080000L,
    0x40080100L, 0x00080000L, 0x02000100L, 0x40080100L,
    0x42000100L, 0x42080000L, 0x00080100L, 0x40000000L,
    0x02000000L, 0x40080000L, 0x40080000L, 0x00000000L,
    0x40000100L, 0x42080100L, 0x42080100L, 0x02000100L,
    0x42080000L, 0x40000100L, 0x00000000L, 0x42000000L,
    0x02080100L, 0x02000000L, 0x42000000L, 0x00080100L,
    0x00080000L, 0x42000100L, 0x00000100L, 0x02000000L,
    0x40000000L, 0x02080000L, 0x42000100L, 0x40080100L,
    0x02000100L, 0x40000000L, 0x42080000L, 0x02080100L,
    0x40080100L, 0x00000100L, 0x02000000L, 0x42080000L,
    0x42080100L, 0x00080100L, 0x42000000L, 0x42080100L,
    0x02080000L, 0x00000000L, 0x40080000L, 0x42000000L,
    0x00080100L, 0x02000100L, 0x40000100L, 0x00080000L,
    0x00000000L, 0x40080000L, 0x02080100L, 0x40000100
};

static const unsigned long SP6[64] =
{
    0x20000010L, 0x20400000L, 0x00004000L, 0x20404010L,
    0x20400000L, 0x00000010L, 0x20404010L, 0x00400000L,
    0x20004000L, 0x00404010L, 0x00400000L, 0x20000010L,
    0x00400010L, 0x20004000L, 0x20000000L, 0x00004010L,
    0x00000000L, 0x00400010L, 0x20004010L, 0x00004000L,
    0x00404000L, 0x20004010L, 0x00000010L, 0x20400010L,
    0x20400010L, 0x00000000L, 0x00404010L, 0x20404000L,
    0x00004010L, 0x00404000L, 0x20404000L, 0x20000000L,
    0x20004000L, 0x00000010L, 0x20400010L, 0x00404000L,
    0x20404010L, 0x00400000L, 0x00004010L, 0x20000010L,
    0x00400000L, 0x20004000L, 0x20000000L, 0x00004010L,
    0x20000010L, 0x20404010L, 0x00404000L, 0x20400000L,
    0x00404010L, 0x20404000L, 0x00000000L, 0x20400010L,
    0x00000010L, 0x00004000L, 0x20400000L, 0x00404010L,
    0x00004000L, 0x00400010L, 0x20004010L, 0x00000000L,
    0x20404000L, 0x20000000L, 0x00400010L, 0x20004010
};

static const unsigned long SP7[64] =
{
    0x00200000L, 0x04200002L, 0x04000802L, 0x00000000L,
    0x00000800L, 0x04000802L, 0x00200802L, 0x04200800L,
    0x04200802L, 0x00200000L, 0x00000000L, 0x04000002L,
    0x00000002L, 0x04000000L, 0x04200002L, 0x00000802L,
    0x04000800L, 0x00200802L, 0x00200002L, 0x04000800L,
    0x04000002L, 0x04200000L, 0x04200800L, 0x00200002L,
    0x04200000L, 0x00000800L, 0x00000802L, 0x04200802L,
    0x00200800L, 0x00000002L, 0x04000000L, 0x00200800L,
    0x04000000L, 0x00200800L, 0x00200000L, 0x04000802L,
    0x04000802L, 0x04200002L, 0x04200002L, 0x00000002L,
    0x00200002L, 0x04000000L, 0x04000800L, 0x00200000L,
    0x04200800L, 0x00000802L, 0x00200802L, 0x04200800L,
    0x00000802L, 0x04000002L, 0x04200802L, 0x04200000L,
    0x00200800L, 0x00000000L, 0x00000002L, 0x04200802L,
    0x00000000L, 0x00200802L, 0x04200000L, 0x00000800L,
    0x04000002L, 0x04000800L, 0x00000800L, 0x00200002
};

static const unsigned long SP8[64] =
{
    0x10001040L, 0x00001000L, 0x00040000L, 0x10041040L,
    0x10000000L, 0x10001040L, 0x00000040L, 0x10000000L,
    0x00040040L, 0x10040000L, 0x10041040L, 0x00041000L,
    0x10041000L, 0x00041040L, 0x00001000L, 0x00000040L,
    0x10040000L, 0x10000040L, 0x10001000L, 0x00001040L,
    0x00041000L, 0x00040040L, 0x10040040L, 0x10041000L,
    0x00001040L, 0x00000000L, 0x00000000L, 0x10040040L,
    0x10000040L, 0x10001000L, 0x00041040L, 0x00040000L,
    0x00041040L, 0x00040000L, 0x10041000L, 0x00001000L,
    0x00000040L, 0x10040040L, 0x00001000L, 0x00041040L,
    0x10001000L, 0x00000040L, 0x10000040L, 0x10040000L,
    0x10040040L, 0x10000000L, 0x00040000L, 0x10001040L,
    0x00000000L, 0x10041040L, 0x00040040L, 0x10000040L,
    0x10040000L, 0x10001000L, 0x10001040L, 0x00000000L,
    0x10041040L, 0x00041000L, 0x00041000L, 0x00001040L,
    0x00001040L, 0x00040040L, 0x10000000L, 0x10041000
};


static void cookey(const unsigned long *raw1, unsigned long *keyout);

#ifdef CLEAN_STACK
void _deskey(const unsigned char *key, short edf, unsigned long *keyout)
#else
void deskey(const unsigned char *key, short edf, unsigned long *keyout)
#endif
{
    int i, j, l, m, n;
    unsigned char pc1m[56], pcr[56];
    unsigned long kn[32];

    for(j=0; j < 56; j++)
    {
        l = pc1[j];
        m = l & 07;
        pc1m[j] = (key[l >> 3] & bytebit[m]) ? 1 : 0;
    }

    for(i=0; i < 16; i++)
    {
        if(edf == DE1) m = (15 - i) << 1;
        else m = i << 1;
        n = m + 1;
        kn[m] = kn[n] = 0L;
        for(j=0; j < 28; j++) 
        {
            l = j + totrot[i];
            if(l < 28) pcr[j] = pc1m[l];
            else pcr[j] = pc1m[l - 28];
        }
        for(/*j = 28*/; j < 56; j++)
        {
            l = j + totrot[i];
            if(l < 56) pcr[j] = pc1m[l];
            else pcr[j] = pc1m[l - 28];
        }
        for(j=0; j < 24; j++)
        {
            if(pcr[pc2[j]]) kn[m] |= bigbyte[j];
            if(pcr[pc2[j+24]]) kn[n] |= bigbyte[j];
        }
    }

    cookey(kn, keyout);
}

#ifdef CLEAN_STACK
void deskey(const unsigned char *key, short edf, unsigned long *keyout)
{
   _deskey(key, edf, keyout);
   burn_stack(sizeof(int)*5 + sizeof(unsigned long)*32 + sizeof(unsigned char)*112);
}
#endif

#ifdef CLEAN_STACK
static void _cookey(const unsigned long *raw1, unsigned long *keyout)
#else
static void cookey(const unsigned long *raw1, unsigned long *keyout)
#endif
{
    unsigned long *cook;
    const unsigned long *raw0;
    unsigned long dough[32];
    int i;

    cook = dough;
    for(i=0; i < 16; i++, raw1++)
    {
        raw0 = raw1++;
        *cook    = (*raw0 & 0x00fc0000L) << 6;
        *cook   |= (*raw0 & 0x00000fc0L) << 10;
        *cook   |= (*raw1 & 0x00fc0000L) >> 10;
        *cook++ |= (*raw1 & 0x00000fc0L) >> 6;
        *cook    = (*raw0 & 0x0003f000L) << 12;
        *cook   |= (*raw0 & 0x0000003fL) << 16;
        *cook   |= (*raw1 & 0x0003f000L) >> 4;
        *cook++ |= (*raw1 & 0x0000003fL);
    }

    memcpy(keyout, dough, sizeof dough);
}

#ifdef CLEAN_STACK
static void cookey(const unsigned long *raw1, unsigned long *keyout)
{
   _cookey(raw1, keyout);
   burn_stack(sizeof(unsigned long *) * 2 + sizeof(unsigned long)*32 + sizeof(int));
}
#endif

#ifndef CLEAN_STACK
static void desfunc(unsigned long *block, const unsigned long *keys)
#else
static void _desfunc(unsigned long *block, const unsigned long *keys)
#endif
{
    unsigned long fval, work, right, leftt;
    int round;

    leftt = block[0];
    right = block[1];

    work = ((leftt >> 4)  ^ right) & 0x0f0f0f0fL;
    right ^= work;
    leftt ^= (work << 4);

    work = ((leftt >> 16) ^ right) & 0x0000ffffL;
    right ^= work;
    leftt ^= (work << 16);

    work = ((right >> 2)  ^ leftt) & 0x33333333L;
    leftt ^= work;
    right ^= (work << 2);

    work = ((right >> 8)  ^ leftt) & 0x00ff00ffL;
    leftt ^= work;
    right ^= (work << 8);

    right = ((right << 1) | ((right >> 31) & 1L)) & 0xFFFFFFFFL;
    work = (leftt ^ right) & 0xaaaaaaaaL;
    
    leftt ^= work;
    right ^= work;
    leftt = ((leftt << 1) | ((leftt >> 31) & 1L)) & 0xffffffffL;

    for( round = 0; round < 8; round++)
    {
        work  = ((right << 28) | (right >> 4)) ^ *keys++;
        fval  = SP7[ work        & 0x3fL]
              | SP5[(work >>  8) & 0x3fL]
              | SP3[(work >> 16) & 0x3fL]
              | SP1[(work >> 24) & 0x3fL];
        work  = right ^ *keys++;
        fval |= SP8[ work        & 0x3fL]
              | SP6[(work >>  8) & 0x3fL]
              | SP4[(work >> 16) & 0x3fL]
              | SP2[(work >> 24) & 0x3fL];
        leftt ^= fval;

        work = ((leftt << 28) | (leftt >> 4)) ^ *keys++;
        fval  = SP7[ work        & 0x3fL]
              | SP5[(work >>  8) & 0x3fL]
              | SP3[(work >> 16) & 0x3fL]
              | SP1[(work >> 24) & 0x3fL];
        work  = leftt ^ *keys++;
        fval |= SP8[ work        & 0x3fL]
              | SP6[(work >>  8) & 0x3fL]
              | SP4[(work >> 16) & 0x3fL]
              | SP2[(work >> 24) & 0x3fL];
        right ^= fval;
    }
    right = (right << 31) | (right >> 1);
    work = (leftt ^ right) & 0xaaaaaaaaL;
    leftt ^= work;
    right ^= work;
    leftt = (leftt << 31) | (leftt >> 1);
    work = ((leftt >> 8) ^ right) & 0x00ff00ffL;
    right ^= work;
    leftt ^= (work << 8);
    // --
    work = ((leftt >> 2) ^ right) & 0x33333333L;
    right ^= work;
    leftt ^= (work << 2);
    work = ((right >> 16) ^ leftt) & 0x0000ffffL;
    leftt ^= work;
    right ^= (work << 16);
    work = ((right >> 4) ^ leftt) & 0x0f0f0f0fL;
    leftt ^= work;
    right ^= (work << 4);
    
    block[0] = right;
    block[1] = leftt;
}

#ifdef CLEAN_STACK
static void desfunc(unsigned long *block, const unsigned long *keys)
{
   _desfunc(block, keys);
   burn_stack(sizeof(unsigned long) * 4 + sizeof(int));
}
#endif


int des_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey)
{
    _ARGCHK(key != NULL);
    _ARGCHK(skey != NULL);

    if (num_rounds != 0 && num_rounds != 16) {
        return CRYPT_INVALID_ROUNDS;
    }

    if (keylen != 8) {
        return CRYPT_INVALID_KEYSIZE;
    }

    deskey(key, EN0, skey->des.ek);
    deskey(key, DE1, skey->des.dk);

    return CRYPT_OK;
}

int des3_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey)
{
    _ARGCHK(key != NULL);
    _ARGCHK(skey != NULL);

    if( num_rounds != 0 && num_rounds != 16) {
        return CRYPT_INVALID_ROUNDS;
    }

    if (keylen != 24) {
        return CRYPT_INVALID_KEYSIZE;
    }

    deskey(key,    EN0, skey->des3.ek[0]);
    deskey(key+8,  DE1, skey->des3.ek[1]);
    deskey(key+16, EN0, skey->des3.ek[2]);

    deskey(key,    DE1, skey->des3.dk[2]);
    deskey(key+8,  EN0, skey->des3.dk[1]);
    deskey(key+16, DE1, skey->des3.dk[0]);

    return CRYPT_OK;
}

void des_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *key)
{
    unsigned long work[2];
    _ARGCHK(pt != NULL);
    _ARGCHK(ct != NULL);
    _ARGCHK(key != NULL);
    LOAD32H(work[0], pt+0);
    LOAD32H(work[1], pt+4);
    desfunc(work, key->des.ek);
    STORE32H(work[0],ct+0);
    STORE32H(work[1],ct+4);
}

void des_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *key)
{
    unsigned long work[2];
    _ARGCHK(pt != NULL);
    _ARGCHK(ct != NULL);
    _ARGCHK(key != NULL);
    LOAD32H(work[0], ct+0);
    LOAD32H(work[1], ct+4);
    desfunc(work, key->des.dk);
    STORE32H(work[0],pt+0);
    STORE32H(work[1],pt+4);
}

void des3_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *key)
{
    unsigned long work[2];
    _ARGCHK(pt != NULL);
    _ARGCHK(ct != NULL);
    _ARGCHK(key != NULL);
    LOAD32H(work[0], pt+0);
    LOAD32H(work[1], pt+4);
    desfunc(work, key->des3.ek[0]);
    desfunc(work, key->des3.ek[1]);
    desfunc(work, key->des3.ek[2]);
    STORE32H(work[0],ct+0);
    STORE32H(work[1],ct+4);
}

void des3_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *key)
{
    unsigned long work[2];
    _ARGCHK(pt != NULL);
    _ARGCHK(ct != NULL);
    _ARGCHK(key != NULL);
    LOAD32H(work[0], ct+0);
    LOAD32H(work[1], ct+4);
    desfunc(work, key->des3.dk[0]);
    desfunc(work, key->des3.dk[1]);
    desfunc(work, key->des3.dk[2]);
    STORE32H(work[0],pt+0);
    STORE32H(work[1],pt+4);
}

int des_test(void)
{
    int errno;
    static const struct des_test_case {
        int num, mode; // mode 1 = encrypt
        unsigned char key[8], txt[8], out[8];
    } cases[] = {
        { 1, 1,     { 0x10, 0x31, 0x6E, 0x02, 0x8C, 0x8F, 0x3B, 0x4A },
                    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 } },
        { 2, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x95, 0xF8, 0xA5, 0xE5, 0xDD, 0x31, 0xD9, 0x00 },
                    { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        { 3, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0xDD, 0x7F, 0x12, 0x1C, 0xA5, 0x01, 0x56, 0x19 },
                    { 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        { 4, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x2E, 0x86, 0x53, 0x10, 0x4F, 0x38, 0x34, 0xEA },
                    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        { 5, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x4B, 0xD3, 0x88, 0xFF, 0x6C, 0xD8, 0x1D, 0x4F },
                    { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        { 6, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x20, 0xB9, 0xE7, 0x67, 0xB2, 0xFB, 0x14, 0x56 },
                    { 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        { 7, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x55, 0x57, 0x93, 0x80, 0xD7, 0x71, 0x38, 0xEF },
                    { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        { 8, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x6C, 0xC5, 0xDE, 0xFA, 0xAF, 0x04, 0x51, 0x2F },
                    { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        { 9, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x0D, 0x9F, 0x27, 0x9B, 0xA5, 0xD8, 0x72, 0x60 }, 
                    { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        {10, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0xD9, 0x03, 0x1B, 0x02, 0x71, 0xBD, 0x5A, 0x0A },
                    { 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },

        { 1, 0,     { 0x10, 0x31, 0x6E, 0x02, 0x8C, 0x8F, 0x3B, 0x4A },
                    { 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 },
                    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
        { 2, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0x95, 0xF8, 0xA5, 0xE5, 0xDD, 0x31, 0xD9, 0x00 } },
        { 3, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0xDD, 0x7F, 0x12, 0x1C, 0xA5, 0x01, 0x56, 0x19 } },
        { 4, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0x2E, 0x86, 0x53, 0x10, 0x4F, 0x38, 0x34, 0xEA } },
        { 5, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0x4B, 0xD3, 0x88, 0xFF, 0x6C, 0xD8, 0x1D, 0x4F } },
        { 6, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0x20, 0xB9, 0xE7, 0x67, 0xB2, 0xFB, 0x14, 0x56 } },
        { 7, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0x55, 0x57, 0x93, 0x80, 0xD7, 0x71, 0x38, 0xEF } },
        { 8, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0x6C, 0xC5, 0xDE, 0xFA, 0xAF, 0x04, 0x51, 0x2F } },
        { 9, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0x0D, 0x9F, 0x27, 0x9B, 0xA5, 0xD8, 0x72, 0x60 } }, 
        {10, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                    { 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                    { 0xD9, 0x03, 0x1B, 0x02, 0x71, 0xBD, 0x5A, 0x0A } }

        /*** more test cases you could add if you are not convinced (the above test cases aren't really too good):

                key              plaintext        ciphertext
                0000000000000000 0000000000000000 8CA64DE9C1B123A7
                FFFFFFFFFFFFFFFF FFFFFFFFFFFFFFFF 7359B2163E4EDC58
                3000000000000000 1000000000000001 958E6E627A05557B
                1111111111111111 1111111111111111 F40379AB9E0EC533
                0123456789ABCDEF 1111111111111111 17668DFC7292532D
                1111111111111111 0123456789ABCDEF 8A5AE1F81AB8F2DD
                0000000000000000 0000000000000000 8CA64DE9C1B123A7
                FEDCBA9876543210 0123456789ABCDEF ED39D950FA74BCC4
                7CA110454A1A6E57 01A1D6D039776742 690F5B0D9A26939B
                0131D9619DC1376E 5CD54CA83DEF57DA 7A389D10354BD271
                07A1133E4A0B2686 0248D43806F67172 868EBB51CAB4599A
                3849674C2602319E 51454B582DDF440A 7178876E01F19B2A
                04B915BA43FEB5B6 42FD443059577FA2 AF37FB421F8C4095
                0113B970FD34F2CE 059B5E0851CF143A 86A560F10EC6D85B
                0170F175468FB5E6 0756D8E0774761D2 0CD3DA020021DC09
                43297FAD38E373FE 762514B829BF486A EA676B2CB7DB2B7A
                07A7137045DA2A16 3BDD119049372802 DFD64A815CAF1A0F
                04689104C2FD3B2F 26955F6835AF609A 5C513C9C4886C088
                37D06BB516CB7546 164D5E404F275232 0A2AEEAE3FF4AB77
                1F08260D1AC2465E 6B056E18759F5CCA EF1BF03E5DFA575A
                584023641ABA6176 004BD6EF09176062 88BF0DB6D70DEE56
                025816164629B007 480D39006EE762F2 A1F9915541020B56
                49793EBC79B3258F 437540C8698F3CFA 6FBF1CAFCFFD0556
                4FB05E1515AB73A7 072D43A077075292 2F22E49BAB7CA1AC
                49E95D6D4CA229BF 02FE55778117F12A 5A6B612CC26CCE4A
                018310DC409B26D6 1D9D5C5018F728C2 5F4C038ED12B2E41
                1C587F1C13924FEF 305532286D6F295A 63FAC0D034D9F793
                0101010101010101 0123456789ABCDEF 617B3A0CE8F07100
                1F1F1F1F0E0E0E0E 0123456789ABCDEF DB958605F8C8C606
                E0FEE0FEF1FEF1FE 0123456789ABCDEF EDBFD1C66C29CCC7
                0000000000000000 FFFFFFFFFFFFFFFF 355550B2150E2451
                FFFFFFFFFFFFFFFF 0000000000000000 CAAAAF4DEAF1DBAE
                0123456789ABCDEF 0000000000000000 D5D44FF720683D0D
                FEDCBA9876543210 FFFFFFFFFFFFFFFF 2A2BB008DF97C2F2

            http://www.ecs.soton.ac.uk/~prw99r/ez438/vectors.txt
        ***/
    };
    int i, failed=0;
    unsigned char out[8];
    symmetric_key des;

    for(i=0; i < (int)(sizeof(cases)/sizeof(cases[0])); i++)
    {
        if ((errno = des_setup(cases[i].key, 8, 0, &des)) != CRYPT_OK) {
           return errno;
        }
        if (cases[i].mode) { 
           des_ecb_encrypt(cases[i].txt, out, &des);
        } else {
           des_ecb_decrypt(cases[i].txt, out, &des);
        }

        if (memcmp(cases[i].out, out, sizeof out) != 0) {
#if 0
            int j;
            printf("DES test #%d failed!\n", cases[i].num);

            printf(  "got:    "); 
            for (j=0; j < (int)sizeof out; j++) {
                printf("%02x ", out[j] & 0xff);
            }
            printf("\nwanted: ");
            for(j=0; j < (int)sizeof out; j++) {
                printf("%02x ", cases[i].out[j] & 0xff);
            }
            printf("\n");
#endif

            failed++;
        }
    }

    if(failed > 0) {
        return CRYPT_FAIL_TESTVECTOR;
    }

    return CRYPT_OK;
}

int des3_test(void)
{
   unsigned char key[24], pt[8], ct[8], tmp[8];
   symmetric_key skey;
   int x, errno;

   if ((errno = des_test()) != CRYPT_OK) {
      return errno;
   }

   for (x = 0; x < 8; x++) {
       pt[x] = x;
   }
   
   for (x = 0; x < 24; x++) {
       key[x] = x;
   }

   if ((errno = des3_setup(key, 24, 0, &skey)) != CRYPT_OK) {
      return errno;
   }
   
   des3_ecb_encrypt(pt, ct, &skey);
   des3_ecb_decrypt(ct, tmp, &skey);
   
   if (memcmp(pt, tmp, 8)) {
      return CRYPT_FAIL_TESTVECTOR;
   }
   
   return CRYPT_OK;
}

int des_keysize(int *desired_keysize)
{
    _ARGCHK(desired_keysize != NULL);
    if(*desired_keysize < 8) {
        return CRYPT_INVALID_KEYSIZE;
    }
    *desired_keysize = 8;
    return CRYPT_OK;
}

int des3_keysize(int *desired_keysize)
{
    _ARGCHK(desired_keysize != NULL);
    if(*desired_keysize < 24) {
        return CRYPT_INVALID_KEYSIZE;
    }
    *desired_keysize = 24;
    return CRYPT_OK;
}

#endif

