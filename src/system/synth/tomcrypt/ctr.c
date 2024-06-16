#include "mycrypt.h"

#ifdef CTR

int ctr_start(int cipher, const unsigned char *count, const unsigned char *key, int keylen, 
              int num_rounds, symmetric_CTR *ctr)
{
   int x, errno;

   // _ARGCHK(count != NULL);
   // _ARGCHK(key != NULL);
   // _ARGCHK(ctr != NULL);

   /* bad param? */
   if ((errno = cipher_is_valid(cipher)) != CRYPT_OK) {
      errno = 1;
      return errno;
   }

   /* setup cipher */
   if ((errno = cipher_descriptor[cipher].setup(key, keylen, num_rounds, &ctr->key)) != CRYPT_OK) {
      errno = 1;
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

int ctr_reinit(int cipher, unsigned char* r4, symmetric_CTR* ctr) {
   if (cipher_is_valid(cipher)) return 1;
   else {
      ctr->padlen = 0;
      memcpy(ctr->ctr, r4, ctr->blocklen);
      cipher_descriptor[ctr->cipher].ecb_encrypt(ctr->ctr, ctr->pad, &ctr->key);
      return 0;
   }
}

int ctr_encrypt_fast(const unsigned char* r3, unsigned char* r4, unsigned long len, symmetric_CTR* ctr){
   while (len != 0) {
      int i = 0;
      while (i < ctr->blocklen) {
         ctr[i].ctr[0]++;
         if (ctr[i].ctr[0] != 0) break;
         i++;
      }
      cipher_descriptor[ctr->cipher].ecb_encrypt(ctr->ctr, ctr->pad, &ctr->key);
   }
   return 0;
}

int ctr_encrypt(const unsigned char *pt, unsigned char *ct, unsigned long len, symmetric_CTR *ctr)
{
   int x;

   // _ARGCHK(pt != NULL);
   // _ARGCHK(ct != NULL);
   // _ARGCHK(ctr != NULL);

   if (cipher_is_valid(ctr->cipher) != CRYPT_OK) {
       return CRYPT_ERROR;
   }

   if(
      (((int)pt & 3) == 0) && 
      (((int)ct & 3) == 0) && 
      ((len & ctr->blocklen - 1U) == 0) &&
      (ctr->blocklen == 0x10) &&
      (ctr->padlen == ctr->blocklen)
   ){
      return ctr_encrypt_fast(pt, ct, len, ctr);
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
   // _ARGCHK(pt != NULL);
   // _ARGCHK(ct != NULL);
   // _ARGCHK(ctr != NULL);

   return ctr_encrypt(ct, pt, len, ctr);
}

#endif
