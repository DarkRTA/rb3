#include "mycrypt.h"

#ifdef XTEA

const struct _cipher_descriptor xtea_desc =
{
    "xtea",
    1,
    16, 16, 8, 32,
    &xtea_setup,
    &xtea_ecb_encrypt,
    &xtea_ecb_decrypt,
    &xtea_test,
    &xtea_keysize
};

int xtea_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey)
{
   _ARGCHK(key != NULL);
   _ARGCHK(skey != NULL);

   /* check arguments */
   if (keylen != 16) {
      return CRYPT_INVALID_KEYSIZE;
   }

   if (num_rounds != 0 && num_rounds != 32) {
      return CRYPT_INVALID_ROUNDS;
   }

   /* load key */
   LOAD32L(skey->xtea.K[0], key+0);
   LOAD32L(skey->xtea.K[1], key+4);
   LOAD32L(skey->xtea.K[2], key+8);
   LOAD32L(skey->xtea.K[3], key+12);
   return CRYPT_OK;
}

void xtea_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *key)
{
   unsigned long y, z, sum;
   int r;

   _ARGCHK(pt != NULL);
   _ARGCHK(ct != NULL);
   _ARGCHK(key != NULL);

   LOAD32L(y, &pt[0]);
   LOAD32L(z, &pt[4]);
   sum = 0;
   for (r = 0; r < 32; r++) {
       y = (y + ((((z<<4)^(z>>5)) + z) ^ (sum + key->xtea.K[sum&3]))) & 0xFFFFFFFFUL;
       sum = (sum + 0x9E3779B9UL) & 0xFFFFFFFFUL;
       z = (z + ((((y<<4)^(y>>5)) + y) ^ (sum + key->xtea.K[(sum>>11)&3]))) & 0xFFFFFFFFUL;
   }
   STORE32L(y, &ct[0]);
   STORE32L(z, &ct[4]);
}

void xtea_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *key)
{
   unsigned long y, z, sum;
   int r;

   _ARGCHK(pt != NULL);
   _ARGCHK(ct != NULL);
   _ARGCHK(key != NULL);

   LOAD32L(y, &ct[0]);
   LOAD32L(z, &ct[4]);
   sum = (32UL*0x9E3779B9UL)&0xFFFFFFFFUL;
   for (r = 0; r < 32; r++) {
       z = (z - ((((y<<4)^(y>>5)) + y) ^ (sum + key->xtea.K[(sum>>11)&3]))) & 0xFFFFFFFFUL;
       sum = (sum - 0x9E3779B9UL) & 0xFFFFFFFFUL;
       y = (y - ((((z<<4)^(z>>5)) + z) ^ (sum + key->xtea.K[sum&3]))) & 0xFFFFFFFFUL;
   }
   STORE32L(y, &pt[0]);
   STORE32L(z, &pt[4]);
}

int xtea_test(void)
{
   static const unsigned char key[16] = 
      { 0x78, 0x56, 0x34, 0x12, 0xf0, 0xcd, 0xcb, 0x9a,
        0x48, 0x37, 0x26, 0x15, 0xc0, 0xbf, 0xae, 0x9d };
   static const unsigned char pt[8] = 
      { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
   static const unsigned char ct[8] = 
      { 0x75, 0xd7, 0xc5, 0xbf, 0xcf, 0x58, 0xc9, 0x3f };
   unsigned char tmp[2][8];
   symmetric_key skey;
   int errno;

   if ((errno = xtea_setup(key, 16, 0, &skey)) != CRYPT_OK)  {
      return errno;
   }
   xtea_ecb_encrypt(pt, tmp[0], &skey);
   xtea_ecb_decrypt(tmp[0], tmp[1], &skey);

   if (memcmp(tmp[0], ct, 8) || memcmp(tmp[1], pt, 8)) { 
      return CRYPT_FAIL_TESTVECTOR;
   }

   return CRYPT_OK;
}

int xtea_keysize(int *desired_keysize)
{
   _ARGCHK(desired_keysize);
   if (*desired_keysize < 16) {
      return CRYPT_INVALID_KEYSIZE; 
   }
   *desired_keysize = 16;
   return CRYPT_OK;
}


#endif



