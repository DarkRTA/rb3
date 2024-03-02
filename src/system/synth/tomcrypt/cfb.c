#include "mycrypt.h"

#ifdef CFB

int cfb_start(int cipher, const unsigned char *IV, const unsigned char *key, 
              int keylen, int num_rounds, symmetric_CFB *cfb)
{
   int x, errno;

   _ARGCHK(IV != NULL);
   _ARGCHK(key != NULL);
   _ARGCHK(cfb != NULL);

   if ((errno = cipher_is_valid(cipher)) != CRYPT_OK) {
      return errno;
   }

   /* copy data */
   cfb->cipher = cipher;
   cfb->blocklen = cipher_descriptor[cipher].block_length;
   for (x = 0; x < cfb->blocklen; x++)
       cfb->IV[x] = IV[x];

   /* init the cipher */
   if ((errno = cipher_descriptor[cipher].setup(key, keylen, num_rounds, &cfb->key)) != CRYPT_OK) {
      return errno;
   }

   /* encrypt the IV */
   cipher_descriptor[cfb->cipher].ecb_encrypt(cfb->IV, cfb->IV, &cfb->key);
   cfb->padlen = 0;

   return CRYPT_OK;
}

int cfb_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_CFB *cfb)
{
   int errno;

   _ARGCHK(pt != NULL);
   _ARGCHK(ct != NULL);
   _ARGCHK(cfb != NULL);

   if ((errno = cipher_is_valid(cfb->cipher)) != CRYPT_OK) {
       return errno;
   }
   while (len--) {
       if (cfb->padlen == cfb->blocklen) {
          cipher_descriptor[cfb->cipher].ecb_encrypt(cfb->pad, cfb->IV, &cfb->key);
          cfb->padlen = 0;
       }
       cfb->pad[cfb->padlen] = (*ct = *pt ^ cfb->IV[cfb->padlen]);
       ++pt; 
       ++ct;
       ++cfb->padlen;
   }
   return CRYPT_OK;
}

int cfb_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_CFB *cfb)
{
   int errno;

   _ARGCHK(pt != NULL);
   _ARGCHK(ct != NULL);
   _ARGCHK(cfb != NULL);

   if ((errno = cipher_is_valid(cfb->cipher)) != CRYPT_OK) {
       return errno;
   }
   while (len--) {
       if (cfb->padlen == cfb->blocklen) {
          cipher_descriptor[cfb->cipher].ecb_encrypt(cfb->pad, cfb->IV, &cfb->key);
          cfb->padlen = 0;
       }
       cfb->pad[cfb->padlen] = *ct;
       *pt = *ct ^ cfb->IV[cfb->padlen];
       ++pt; 
       ++ct;
       ++cfb->padlen;
   }
   return CRYPT_OK;
}

#endif

