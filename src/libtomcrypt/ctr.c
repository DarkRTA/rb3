#include "mycrypt.h"

#ifdef CTR

int ctr_start(int cipher, const unsigned char *count, const unsigned char *key, int keylen, 
              int num_rounds, symmetric_CTR *ctr)
{
   int x, errno;

   _ARGCHK(count != NULL);
   _ARGCHK(key != NULL);
   _ARGCHK(ctr != NULL);

   /* bad param? */
   if ((errno = cipher_is_valid(cipher)) != CRYPT_OK) {
      return errno;
   }

   /* setup cipher */
   if ((errno = cipher_descriptor[cipher].setup(key, keylen, num_rounds, &ctr->key)) != CRYPT_OK) {
      return errno;
   }

   /* copy ctr */
   ctr->blocklen = cipher_descriptor[cipher].block_length;
   ctr->cipher   = cipher;
   ctr->padlen   = 0;
   for (x = 0; x < ctr->blocklen; x++) {
       ctr->ctr[x] = count[x];
   }
   cipher_descriptor[ctr->cipher].ecb_encrypt(ctr->ctr, ctr->pad, &ctr->key);
   return CRYPT_OK;
}

int ctr_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_CTR *ctr)
{
   int x, errno;

   _ARGCHK(pt != NULL);
   _ARGCHK(ct != NULL);
   _ARGCHK(ctr != NULL);

   if ((errno = cipher_is_valid(ctr->cipher)) != CRYPT_OK) {
       return errno;
   }

   while (len--) {
      /* is the pad empty? */
      if (ctr->padlen == ctr->blocklen) {
         /* increment counter */
         for (x = 0; x < ctr->blocklen; x++) {
            ctr->ctr[x] = (ctr->ctr[x] + 1) & 255;
            if (ctr->ctr[x] != 0) {
               break;
            }
         }

         /* encrypt it */
         cipher_descriptor[ctr->cipher].ecb_encrypt(ctr->ctr, ctr->pad, &ctr->key);
         ctr->padlen = 0;
      }
      *ct++ = *pt++ ^ ctr->pad[ctr->padlen++];
   }
   return CRYPT_OK;
}

int ctr_decrypt(const unsigned char *ct, unsigned char *pt, unsigned long len, symmetric_CTR *ctr)
{
   _ARGCHK(pt != NULL);
   _ARGCHK(ct != NULL);
   _ARGCHK(ctr != NULL);

   return ctr_encrypt(ct, pt, len, ctr);
}

#endif

