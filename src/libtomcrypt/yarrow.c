#include "mycrypt.h"

#ifdef YARROW

const struct _prng_descriptor yarrow_desc =
{
    "yarrow",
    &yarrow_start,
    &yarrow_add_entropy,
    &yarrow_ready,
    &yarrow_read
};

int yarrow_start(prng_state *prng)
{
   int errno;
   
   _ARGCHK(prng != NULL);

   /* these are the default hash/cipher combo used */
#ifdef RIJNDAEL
   prng->yarrow.cipher = register_cipher(&rijndael_desc);
#elif defined(BLOWFISH)
   prng->yarrow.cipher = register_cipher(&blowfish_desc);
#elif defined(TWOFISH)
   prng->yarrow.cipher = register_cipher(&twofish_desc);
#elif defined(CAST5)
   prng->yarrow.cipher = register_cipher(&cast5_desc);
#elif defined(SERPENT)
   prng->yarrow.cipher = register_cipher(&serpent_desc);
#elif defined(SAFER)
   prng->yarrow.cipher = register_cipher(&saferp_desc);
#elif defined(RC5)
   prng->yarrow.cipher = register_cipher(&rc5_desc);
#elif defined(RC6)
   prng->yarrow.cipher = register_cipher(&rc6_desc);
#elif defined(XTEA)
   prng->yarrow.cipher = register_cipher(&xtea_desc);
#elif defined(RC2)
   prng->yarrow.cipher = register_cipher(&rc2_desc);
#elif defined(DES)
   prng->yarrow.cipher = register_cipher(&des3_desc);
#elif
   #error YARROW needs at least one CIPHER
#endif
   if ((errno = cipher_is_valid(prng->yarrow.cipher)) != CRYPT_OK) {
      return errno;
   }

#ifdef SHA256
   prng->yarrow.hash   = register_hash(&sha256_desc);
#elif defined(SHA512)
   prng->yarrow.hash   = register_hash(&sha512_desc);
#elif defined(SHA384)
   prng->yarrow.hash   = register_hash(&sha384_desc);
#elif defined(SHA1)
   prng->yarrow.hash   = register_hash(&sha1_desc);
#elif defined(TIGER)
   prng->yarrow.hash   = register_hash(&tiger_desc);
#elif defined(MD5)
   prng->yarrow.hash   = register_hash(&md5_desc);
#elif defined(MD4)
   prng->yarrow.hash   = register_hash(&md4_desc);
#elif defined(MD2)
   prng->yarrow.hash   = register_hash(&md2_desc);
#else
   #error YARROW needs at least one HASH
#endif
   if ((errno = hash_is_valid(prng->yarrow.hash)) != CRYPT_OK) {
      return errno;
   }

   /* zero the memory used */
   zeromem(prng->yarrow.pool, sizeof(prng->yarrow.pool));

   return CRYPT_OK;
}

int yarrow_add_entropy(const unsigned char *buf, unsigned long len, prng_state *prng)
{
   hash_state md;
   int errno;

   _ARGCHK(buf != NULL);
   _ARGCHK(prng != NULL);

   if ((errno = hash_is_valid(prng->yarrow.hash)) != CRYPT_OK) {
      return errno;
   }

   /* start the hash */
   hash_descriptor[prng->yarrow.hash].init(&md);

   /* hash the current pool */
   hash_descriptor[prng->yarrow.hash].process(&md, prng->yarrow.pool, hash_descriptor[prng->yarrow.hash].hashsize);

   /* add the new entropy */
   hash_descriptor[prng->yarrow.hash].process(&md, buf, len);

   /* store result */
   hash_descriptor[prng->yarrow.hash].done(&md, prng->yarrow.pool);

   return CRYPT_OK;
}

int yarrow_ready(prng_state *prng)
{
   int ks, errno;

   _ARGCHK(prng != NULL);

   if ((errno = hash_is_valid(prng->yarrow.hash)) != CRYPT_OK) {
      return errno;
   }
   
   if ((errno = cipher_is_valid(prng->yarrow.cipher)) != CRYPT_OK) {
      return errno;
   }

   /* setup CTR mode using the "pool" as the key */
   ks = hash_descriptor[prng->yarrow.hash].hashsize;
   if ((errno = cipher_descriptor[prng->yarrow.cipher].keysize(&ks)) != CRYPT_OK) {
      return errno;
   }

   if ((errno = ctr_start(prng->yarrow.cipher, prng->yarrow.pool, prng->yarrow.pool, ks, 0, &prng->yarrow.ctr)) != CRYPT_OK) {
      return errno;
   }
   return CRYPT_OK;
}

unsigned long yarrow_read(unsigned char *buf, unsigned long len, prng_state *prng)
{
   _ARGCHK(buf != NULL);
   _ARGCHK(prng != NULL);

   if (ctr_encrypt(buf, buf, len, &prng->yarrow.ctr) != CRYPT_OK) {
      return 0;
   }
   return len;
}

#endif

