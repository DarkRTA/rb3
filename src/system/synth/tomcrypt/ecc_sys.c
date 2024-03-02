#ifdef PK_PACKET

int ecc_encrypt(const unsigned char *in,  unsigned long len, 
                      unsigned char *out, unsigned long *outlen,
                      prng_state *prng, int wprng, int cipher, int hash, 
                      ecc_key *key)
{
    unsigned char pub_expt[512], ecc_shared[256], IV[MAXBLOCKSIZE], skey[MAXBLOCKSIZE];
    ecc_key pubkey;
    unsigned long x, y, z, pubkeysize;
    int keysize, blocksize, hashsize, errno;
    symmetric_CTR ctr;

    _ARGCHK(in != NULL);
    _ARGCHK(out != NULL);
    _ARGCHK(outlen != NULL);
    _ARGCHK(key != NULL);

    /* check that wprng/cipher/hash are not invalid */
    if ((errno = prng_is_valid(wprng)) != CRYPT_OK) {
       return errno;
    }

    if ((errno = cipher_is_valid(cipher)) != CRYPT_OK) {
       return errno;
    }

    if ((errno = hash_is_valid(hash)) != CRYPT_OK) {
       return errno;
    }

    /* make a random key and export the public copy */
    if ((errno = ecc_make_key(prng, wprng, ecc_get_size(key), &pubkey)) != CRYPT_OK) {
       return errno;
    }

    pubkeysize = sizeof(pub_expt);
    if ((errno = ecc_export(pub_expt, &pubkeysize, PK_PUBLIC, &pubkey)) != CRYPT_OK) {
       ecc_free(&pubkey);
       return errno;
    }
    
    /* now check if the out buffer is big enough */
    if (*outlen < (10 + PACKET_SIZE + pubkeysize + 
                   cipher_descriptor[cipher].block_length + len)) {
       ecc_free(&pubkey);
       return CRYPT_BUFFER_OVERFLOW;
    }

    /* make random key */
    blocksize = cipher_descriptor[cipher].block_length;
    hashsize  = hash_descriptor[hash].hashsize;
    keysize = hashsize;
    if ((errno = cipher_descriptor[cipher].keysize(&keysize)) != CRYPT_OK) {
       ecc_free(&pubkey);
       return errno;
    }
    x = sizeof(ecc_shared);
    if ((errno = ecc_shared_secret(&pubkey, key, ecc_shared, &x)) != CRYPT_OK) {
       ecc_free(&pubkey);
       return errno;
    }
    ecc_free(&pubkey);

    z = sizeof(skey);
    if ((errno = hash_memory(hash, ecc_shared, x, skey, &z)) != CRYPT_OK) {
       return errno;
    }

    /* make up IV */
    if (prng_descriptor[wprng].read(IV, cipher_descriptor[cipher].block_length, prng) != 
        (unsigned long)cipher_descriptor[cipher].block_length) {
       return CRYPT_ERROR_READPRNG;
    }

    /* setup CTR mode */
    if ((errno = ctr_start(cipher, IV, skey, keysize, 0, &ctr)) != CRYPT_OK) {
       return errno;
    }

    /* output header */
    y = PACKET_SIZE;

    /* size of cipher name and the name itself */
    out[y++] = cipher_descriptor[cipher].ID;

    /* size of hash name and the name itself */
    out[y++] = hash_descriptor[hash].ID;

    /* length of ECC pubkey and the key itself */
    STORE32L(pubkeysize, out+y);
    y += 4;
    for (x = 0; x < (unsigned)pubkeysize; x++, y++) {
        out[y] = pub_expt[x];
    }

    /* cipher IV */
    for (x = 0; x < (unsigned)blocksize; x++, y++) {
        out[y] = IV[x];
    }

    /* length of ciphertext */
    STORE32L(len, out+y);
    y += 4;

    /* encrypt the message */
    if ((errno = ctr_encrypt(in, out+y, len, &ctr)) != CRYPT_OK) {
       return errno;
    }
    y += len;
    
    /* store header */
    packet_store_header(out, PACKET_SECT_ECC, PACKET_SUB_ENCRYPTED, y);

#ifdef CLEAN_STACK
    /* clean up */
    zeromem(pub_expt, sizeof(pub_expt));
    zeromem(ecc_shared, sizeof(ecc_shared));
    zeromem(skey, sizeof(skey));
    zeromem(IV, sizeof(IV));
    zeromem(&ctr, sizeof(ctr));
#endif

    *outlen = y;
    return CRYPT_OK;
}

int ecc_decrypt(const unsigned char *in,  unsigned long len, 
                      unsigned char *out, unsigned long *outlen, 
                      ecc_key *key)
{
   unsigned char shared_secret[256], skey[MAXBLOCKSIZE];
   unsigned long x, y, z, res, hashsize, blocksize;
   int cipher, hash, keysize, errno;
   ecc_key pubkey;
   symmetric_CTR ctr;

   _ARGCHK(in != NULL);
   _ARGCHK(out != NULL);
   _ARGCHK(outlen != NULL);
   _ARGCHK(key != NULL);

   /* right key type? */
   if (key->type != PK_PRIVATE) {
      return CRYPT_PK_NOT_PRIVATE;
   }

   /* is header correct? */
   if ((errno = packet_valid_header((unsigned char *)in, PACKET_SECT_ECC, PACKET_SUB_ENCRYPTED)) != CRYPT_OK) {
      return errno;
   }

   /* now lets get the cipher name */
   y = PACKET_SIZE;
   cipher = find_cipher_id(in[y++]);
   if (cipher == -1) {
      return CRYPT_INVALID_CIPHER;
   }

   /* now lets get the hash name */
   hash = find_hash_id(in[y++]);
   if (hash == -1) {
      return CRYPT_INVALID_HASH;
   }

   /* common values */
   blocksize = cipher_descriptor[cipher].block_length;
   hashsize  = hash_descriptor[hash].hashsize;
   keysize = hashsize;
   if ((errno = cipher_descriptor[cipher].keysize(&keysize)) != CRYPT_OK) {
      return errno;
   }

   /* get public key */
   LOAD32L(x, in+y);
   y += 4;
   if ((errno = ecc_import(in+y, &pubkey)) != CRYPT_OK) {
      return errno;
   }
   y += x;

   /* make shared key */
   x = sizeof(shared_secret);
   if ((errno = ecc_shared_secret(key, &pubkey, shared_secret, &x)) != CRYPT_OK) {
      ecc_free(&pubkey);
      return errno;
   }
   ecc_free(&pubkey);

   z = sizeof(skey);
   if ((errno = hash_memory(hash, shared_secret, x, skey, &z)) != CRYPT_OK) {
      res = errno;
      goto done;
   }

   /* setup CTR mode */
   if ((errno = ctr_start(cipher, in+y, skey, keysize, 0, &ctr)) != CRYPT_OK) {
      res = errno;
      goto done;
   }
   y += blocksize;

   /* get length */
   LOAD32L(len,in+y);
   y += 4;
   
   /* buffer overflow? */
   if (len > *outlen) {
      res = CRYPT_BUFFER_OVERFLOW;
      goto done;
   }

   /* decrypt message */
   if ((errno = ctr_decrypt(in+y, out, len, &ctr)) != CRYPT_OK) {
      res = errno;
      goto done;
   }
   *outlen = len;

   res = CRYPT_OK;
done:
#ifdef CLEAN_STACK
   zeromem(shared_secret, sizeof(shared_secret));
   zeromem(skey, sizeof(skey));
   zeromem(&ctr, sizeof(ctr));
#endif
   return res;
}

/* Signatures 
 *
 * Signatures are performed using a slightly modified ElGamal protocol.  
 * In these notes uppercase letters are points and lowercase letters are 
 * scalars.  The users private key is 'x' and public key is Y = xG.  
 * The order of the curve is 'r'.
 *
 *
 * To sign a message 'm' the user does this

1.  Makes up a random 'k' and finds kG [basically makes up a ecc_key], we will let A = kG
2.  Finds b such that b = (m - x)/k mod r
3.  Outputs (A, b) as the signature

To verify a user computes mG and compares that to (bA + Y).  Note that (bA + Y) is equal to

= ((m - x)/k)(kG) + xG
= (m - x)G + xG
= mG

In theory, assuming the ECC Discrete Log is a hard problem an attacker 
cannot find 'x' from (A, b).  'b' is perfectly decorrelated and reveals no 
information.  A reveals what kG is but not 'k' directly.  Therefore, 
assuming finding 'k' given kG is hard, finding 'x' from b is hard too.

*/

int ecc_sign(const unsigned char *in,  unsigned long inlen, 
                   unsigned char *out, unsigned long *outlen, 
                   int hash, prng_state *prng, int wprng, 
                   ecc_key *key)
{
   ecc_key pubkey;
   mp_int b, p;
   unsigned char epubkey[256], er[256], md[MAXBLOCKSIZE];
   unsigned long x, y, z, pubkeysize, rsize;
   int res, errno;

   _ARGCHK(in != NULL);
   _ARGCHK(out != NULL);
   _ARGCHK(outlen != NULL);
   _ARGCHK(key != NULL);

   /* is this a private key? */
   if (key->type != PK_PRIVATE) {
      return CRYPT_PK_NOT_PRIVATE;
   }

   if ((errno = prng_is_valid(wprng)) != CRYPT_OK) {
      return errno;
   }

   if ((errno = hash_is_valid(hash)) != CRYPT_OK) {
      return errno;
   }

   /* make up a key and export the public copy */
   if ((errno = ecc_make_key(prng, wprng, ecc_get_size(key), &pubkey)) != CRYPT_OK)  {
      return errno;
   }

   pubkeysize = sizeof(epubkey);
   if ((errno = ecc_export(epubkey, &pubkeysize, PK_PUBLIC, &pubkey)) != CRYPT_OK) {
      ecc_free(&pubkey);
      return errno;
   }

   /* get the hash and load it as a bignum into 'b' */
   md[0] = 0;
   z = sizeof(md)-1;
   if ((errno = hash_memory(hash, in, inlen, md+1, &z)) != CRYPT_OK) {
      ecc_free(&pubkey);
      return errno;
   }

   /* init the bignums */
   if (mp_init_multi(&b, &p, NULL) != MP_OKAY) { 
      ecc_free(&pubkey);
      return CRYPT_MEM;
   }
   if (mp_read_radix(&p, sets[key->idx].order, 10) != MP_OKAY)            { goto error; }
   if (mp_read_raw(&b, md, 1+hash_descriptor[hash].hashsize) != MP_OKAY)  { goto error; }

   /* find b = (m - x)/k */
   if (mp_invmod(&pubkey.k, &p, &pubkey.k) != MP_OKAY)                    { goto error; } /* k = 1/k */
   if (mp_submod(&b, &key->k, &p, &b) != MP_OKAY)                         { goto error; } /* b = m - x */
   if (mp_mulmod(&b, &pubkey.k, &p, &b) != MP_OKAY)                       { goto error; } /* b = (m - x)/k */

   /* export it */
   rsize = mp_raw_size(&b);
   if (rsize > sizeof(er)) { 
      goto error; 
   }
   mp_toraw(&b, er);

   /* now lets check the outlen before we write */
   if (*outlen < (9 + PACKET_SIZE + rsize + pubkeysize)) {
      res = CRYPT_BUFFER_OVERFLOW;
      goto done1;
   }

   /* lets output */
   y = PACKET_SIZE;
   
   /* length of hash name plus NULL */
   out[y++] = hash_descriptor[hash].ID;

   /* size of public key */
   STORE32L(pubkeysize, out+y);
   y += 4;

   /* copy the public key */
   for (x = 0; x < pubkeysize; x++, y++) {
       out[y] = epubkey[x];
   }

   /* size of 'r' */
   STORE32L(rsize, out+y);
   y += 4;

   /* copy r */
   for (x = 0; x < rsize; x++, y++) {
       out[y] = er[x];
   }

   /* store header */
   packet_store_header(out, PACKET_SECT_ECC, PACKET_SUB_SIGNED, y);

   /* clear memory */
   *outlen = y;
   res = CRYPT_OK;
   goto done1;
error:
   res = CRYPT_MEM;
done1:
   mp_clear_multi(&b, &p, NULL);
   ecc_free(&pubkey);
#ifdef CLEAN_STACK
   zeromem(er, sizeof(er));
   zeromem(epubkey, sizeof(epubkey));
   zeromem(md, sizeof(md));
#endif
   return res;   
}

/* verify that mG = (bA + Y) */
int ecc_verify(const unsigned char *sig, const unsigned char *msg, 
                     unsigned long inlen, int *stat, 
                     ecc_key *key)
{
   ecc_point *mG;
   ecc_key   pubkey;
   mp_int b, p, m;
   unsigned long x, y, z;
   int hash, res, errno;
   unsigned char md[MAXBLOCKSIZE];

   _ARGCHK(sig != NULL);
   _ARGCHK(msg != NULL);
   _ARGCHK(stat != NULL);
   _ARGCHK(key != NULL);

   /* default to invalid signature */
   *stat = 0;

   /* is the message format correct? */
   if ((errno = packet_valid_header((unsigned char *)sig, PACKET_SECT_ECC, PACKET_SUB_SIGNED)) != CRYPT_OK) {
      return errno;
   }     

   /* get hash name */
   y = PACKET_SIZE;
   hash = find_hash_id(sig[y++]);
   if (hash == -1) {
      return CRYPT_INVALID_HASH;
   }

   /* get size of public key */
   LOAD32L(x, sig+y);
   y += 4;

   /* load the public key */
   if ((errno = ecc_import((unsigned char*)sig+y, &pubkey)) != CRYPT_OK) {
      return errno;
   }
   y += x;

   /* load size of 'b' */
   LOAD32L(x, sig+y);
   y += 4;

   /* init values */
   if (mp_init_multi(&b, &m, &p, NULL) != MP_OKAY) { 
      ecc_free(&pubkey);
      return CRYPT_MEM;
   }

   mG = new_point();
   if (mG == NULL) { 
      mp_clear_multi(&b, &m, &p, NULL);
      ecc_free(&pubkey);
      return CRYPT_MEM;
   } 

   /* load b */
   if (mp_read_raw(&b, (unsigned char *)sig+y, x) != MP_OKAY)                      { goto error; }
   y += x;

   /* get m in binary a bignum */
   md[0] = 0;
   z = sizeof(md)-1;
   if ((errno = hash_memory(hash, msg, inlen, md+1, &z)) != CRYPT_OK) {
      res = errno;
      goto done1;
   }
   if (mp_read_raw(&m, md, hash_descriptor[hash].hashsize + 1) != MP_OKAY)         { goto error; }
   
   /* load prime */
   if (mp_read_radix(&p, sets[key->idx].prime, 10) != MP_OKAY)                     { goto error; }

   /* get bA */
   if (ecc_mulmod(&b, &pubkey.pubkey, &pubkey.pubkey, &p, key->idx) != CRYPT_OK)             { goto error; }
   
   /* get bA + Y */
   if (add_point(&pubkey.pubkey, &key->pubkey, &pubkey.pubkey, &p) != CRYPT_OK)    { goto error; }

   /* get mG */
   if (mp_read_radix(&mG->x, sets[key->idx].Gx, 16) != MP_OKAY)                    { goto error; }
   if (mp_read_radix(&mG->y, sets[key->idx].Gy, 16) != MP_OKAY)                    { goto error; }
   if (ecc_mulmod(&m, mG, mG, &p, key->idx) != CRYPT_OK)                                     { goto error; }

   /* compare mG to bA + Y */
   if (!mp_cmp(&mG->x, &pubkey.pubkey.x) && !mp_cmp(&mG->y, &pubkey.pubkey.y)) {
      *stat = 1;
   }

   /* clear up and return */
   res = CRYPT_OK;
   goto done1;
error:
   res = CRYPT_MEM;
done1:
   del_point(mG);
   ecc_free(&pubkey);
   mp_clear_multi(&p, &m, &b, NULL);
#ifdef CLEAN_STACK
   zeromem(md, sizeof(md));
#endif
   return CRYPT_OK;
}

#endif

int ecc_encrypt_key(const unsigned char *inkey, unsigned long keylen,
                          unsigned char *out,  unsigned long *len, 
                          prng_state *prng, int wprng, int hash, 
                          ecc_key *key)
{
    unsigned char pub_expt[256], ecc_shared[256], skey[MAXBLOCKSIZE];
    ecc_key pubkey;
    unsigned long x, y, z, hashsize, pubkeysize;
    int errno;

    _ARGCHK(inkey != NULL);
    _ARGCHK(out != NULL);
    _ARGCHK(len != NULL);
    _ARGCHK(key != NULL);

    /* check that wprng/cipher/hash are not invalid */
    if ((errno = prng_is_valid(wprng)) != CRYPT_OK) {
       return errno;
    }

    if ((errno = hash_is_valid(hash)) != CRYPT_OK) {
       return errno;
    }

    if (keylen > hash_descriptor[hash].hashsize) {
       return CRYPT_INVALID_HASH;
    }

    /* make a random key and export the public copy */
    if ((errno = ecc_make_key(prng, wprng, ecc_get_size(key), &pubkey)) != CRYPT_OK) {
       return errno;
    }

    pubkeysize = sizeof(pub_expt);
    if ((errno = ecc_export(pub_expt, &pubkeysize, PK_PUBLIC, &pubkey)) != CRYPT_OK) {
       ecc_free(&pubkey);
       return errno;
    }
    
    /* now check if the out buffer is big enough */
    if (*len < (9 + PACKET_SIZE + pubkeysize + hash_descriptor[hash].hashsize)) {
       ecc_free(&pubkey);
       return CRYPT_BUFFER_OVERFLOW;
    }

    /* make random key */
    hashsize  = hash_descriptor[hash].hashsize;
    x = sizeof(ecc_shared);
    if ((errno = ecc_shared_secret(&pubkey, key, ecc_shared, &x)) != CRYPT_OK) {
       ecc_free(&pubkey);
       return errno;
    }
    ecc_free(&pubkey);
    z = sizeof(skey);
    if ((errno = hash_memory(hash, ecc_shared, x, skey, &z)) != CRYPT_OK) {
       return errno;
    }

    /* Encrypt the key */
    for (x = 0; x < keylen; x++) {
      skey[x] ^= inkey[x];
    }

    /* output header */
    y = PACKET_SIZE;
 
    /* size of hash name and the name itself */
    out[y++] = hash_descriptor[hash].ID;

    /* length of ECC pubkey and the key itself */
    STORE32L(pubkeysize, out+y);
    y += 4;

    for (x = 0; x < pubkeysize; x++, y++) {
        out[y] = pub_expt[x];
    }

    STORE32L(keylen, out+y);
    y += 4;

    /* Store the encrypted key */
    for (x = 0; x < keylen; x++, y++) {
      out[y] = skey[x];
    }

    /* store header */
    packet_store_header(out, PACKET_SECT_ECC, PACKET_SUB_ENC_KEY, y);

#ifdef CLEAN_STACK
    /* clean up */
    zeromem(pub_expt, sizeof(pub_expt));
    zeromem(ecc_shared, sizeof(ecc_shared));
    zeromem(skey, sizeof(skey));
#endif
    *len = y;
    return CRYPT_OK;
}

int ecc_decrypt_key(const unsigned char *in, unsigned char *outkey, 
                          unsigned long *keylen, ecc_key *key)
{
   unsigned char shared_secret[256], skey[MAXBLOCKSIZE];
   unsigned long x, y, z, res, hashsize, keysize;
   int hash, errno;
   ecc_key pubkey;

   _ARGCHK(in != NULL);
   _ARGCHK(outkey != NULL);
   _ARGCHK(keylen != NULL);
   _ARGCHK(key != NULL);

   /* right key type? */
   if (key->type != PK_PRIVATE) {
      return CRYPT_PK_NOT_PRIVATE;
   }

   /* is header correct? */
   if ((errno = packet_valid_header((unsigned char *)in, PACKET_SECT_ECC, PACKET_SUB_ENC_KEY)) != CRYPT_OK) {
      return errno;
   }

   /* now lets get the hash name */
   y = PACKET_SIZE;
   hash = find_hash_id(in[y++]);
   if (hash == -1) {
      return CRYPT_INVALID_HASH;
   }

   /* common values */
   hashsize  = hash_descriptor[hash].hashsize;

   /* get public key */
   LOAD32L(x, in+y);
   y += 4;
   if ((errno = ecc_import(in+y, &pubkey)) != CRYPT_OK) {
      return errno;
   }
   y += x;

   /* make shared key */
   x = sizeof(shared_secret);
   if ((errno = ecc_shared_secret(key, &pubkey, shared_secret, &x)) != CRYPT_OK) {
      ecc_free(&pubkey);
      return errno;
   }
   ecc_free(&pubkey);

   z = sizeof(skey);
   if ((errno = hash_memory(hash, shared_secret, x, skey, &z)) != CRYPT_OK) {
      return errno;
   }

   LOAD32L(keysize, in+y);
   y += 4;

   if (*keylen < keysize) {
       res = CRYPT_BUFFER_OVERFLOW;
       goto done;
   }

   /* Decrypt the key */
   for (x = 0; x < keysize; x++, y++) {
     outkey[x] = skey[x] ^ in[y];
   }

   *keylen = keysize;

   res = CRYPT_OK;
done:
#ifdef CLEAN_STACK
   zeromem(shared_secret, sizeof(shared_secret));
   zeromem(skey, sizeof(skey));
#endif
   return res;
}

int ecc_sign_hash(const unsigned char *in,  unsigned long inlen, 
                        unsigned char *out, unsigned long *outlen, 
                        prng_state *prng, int wprng, ecc_key *key)
{
   ecc_key pubkey;
   mp_int b, p;
   unsigned char epubkey[256], er[256], md[MAXBLOCKSIZE];
   unsigned long x, y, pubkeysize, rsize;
   int res, errno;

   _ARGCHK(in != NULL);
   _ARGCHK(out != NULL);
   _ARGCHK(outlen != NULL);
   _ARGCHK(key != NULL);

   /* is this a private key? */
   if (key->type != PK_PRIVATE) {
      return CRYPT_PK_NOT_PRIVATE;
   }

   if ((errno = prng_is_valid(wprng)) != CRYPT_OK) {
      return errno;
   }

   /* make up a key and export the public copy */
   if ((errno = ecc_make_key(prng, wprng, ecc_get_size(key), &pubkey)) != CRYPT_OK) {
      return errno;
   }

   pubkeysize = sizeof(epubkey);
   if ((errno = ecc_export(epubkey, &pubkeysize, PK_PUBLIC, &pubkey)) != CRYPT_OK) {
      ecc_free(&pubkey);
      return errno;
   }

   /* get the hash and load it as a bignum into 'b' */
   md[0] = 0;
   memcpy(md+1, in, MIN(sizeof(md)-1,inlen));

   /* init the bignums */
   if (mp_init_multi(&b, &p, NULL) != MP_OKAY) { 
      ecc_free(&pubkey);
      return CRYPT_MEM;
   }
   if (mp_read_radix(&p, (unsigned char *)sets[key->idx].order, 10) != MP_OKAY)            { goto error; }
   if (mp_read_raw(&b, md, 1+MIN(sizeof(md)-1,inlen)) != MP_OKAY)         { goto error; }

   /* find b = (m - x)/k */
   if (mp_invmod(&pubkey.k, &p, &pubkey.k) != MP_OKAY)                    { goto error; } /* k = 1/k */
   if (mp_submod(&b, &key->k, &p, &b) != MP_OKAY)                         { goto error; } /* b = m - x */
   if (mp_mulmod(&b, &pubkey.k, &p, &b) != MP_OKAY)                       { goto error; } /* b = (m - x)/k */

   /* export it */
   rsize = mp_raw_size(&b);
   if (rsize > sizeof(er)) { 
      goto error; 
   }
   mp_toraw(&b, er);

   /* now lets check the outlen before we write */
   if (*outlen < (12 + rsize + pubkeysize)) {
      res = CRYPT_BUFFER_OVERFLOW;
      goto done1;
   }

   /* lets output */
   y = PACKET_SIZE;
   
   /* size of public key */
   STORE32L(pubkeysize, out+y);
   y += 4;

   /* copy the public key */
   for (x = 0; x < pubkeysize; x++, y++) {
       out[y] = epubkey[x];
   }

   /* size of 'r' */
   STORE32L(rsize, out+y);
   y += 4;

   /* copy r */
   for (x = 0; x < rsize; x++, y++) {
       out[y] = er[x];
   }

   /* store header */
   packet_store_header(out, PACKET_SECT_ECC, PACKET_SUB_SIGNED, y);

   /* clear memory */
   *outlen = y;
   res = CRYPT_OK;
   goto done1;
error:
   res = CRYPT_MEM;
done1:
   mp_clear_multi(&b, &p, NULL);
   ecc_free(&pubkey);
#ifdef CLEAN_STACK
   zeromem(er, sizeof(er));
   zeromem(epubkey, sizeof(epubkey));
   zeromem(md, sizeof(md));
#endif
   return res;   
}

/* verify that mG = (bA + Y) */
int ecc_verify_hash(const unsigned char *sig, const unsigned char *hash, 
                     unsigned long inlen, int *stat, 
                     ecc_key *key)
{
   ecc_point *mG;
   ecc_key   pubkey;
   mp_int b, p, m;
   unsigned long x, y;
   int res, errno;
   unsigned char md[MAXBLOCKSIZE];

   _ARGCHK(sig != NULL);
   _ARGCHK(hash != NULL);
   _ARGCHK(hash != NULL);
   _ARGCHK(key != NULL);

   /* default to invalid signature */
   *stat = 0;

   /* is the message format correct? */
   if ((errno = packet_valid_header((unsigned char *)sig, PACKET_SECT_ECC, PACKET_SUB_SIGNED)) != CRYPT_OK) {
      return errno;
   }     

   /* get hash name */
   y = PACKET_SIZE;

   /* get size of public key */
   LOAD32L(x, sig+y);
   y += 4;

   /* load the public key */
   if ((errno = ecc_import((unsigned char*)sig+y, &pubkey)) != CRYPT_OK) {
      return errno;
   }
   y += x;

   /* load size of 'b' */
   LOAD32L(x, sig+y);
   y += 4;

   /* init values */
   if (mp_init_multi(&b, &m, &p, NULL) != MP_OKAY) { 
      ecc_free(&pubkey);
      return CRYPT_MEM;
   }

   mG = new_point();
   if (mG == NULL) { 
      mp_clear_multi(&b, &m, &p, NULL);
      ecc_free(&pubkey);
      return CRYPT_MEM;
   } 

   /* load b */
   if (mp_read_raw(&b, (unsigned char *)sig+y, x) != MP_OKAY)                      { goto error; }
   y += x;

   /* get m in binary a bignum */
   md[0] = 0;
   memcpy(md+1,hash,MIN(sizeof(md)-1,inlen));
   if (mp_read_raw(&m, md, 1+MIN(sizeof(md)-1,inlen)) != MP_OKAY)                  { goto error; }
   
   /* load prime */
   if (mp_read_radix(&p, (unsigned char *)sets[key->idx].prime, 10) != MP_OKAY)    { goto error; }

   /* get bA */
   if (ecc_mulmod(&b, &pubkey.pubkey, &pubkey.pubkey, &p, key->idx) != CRYPT_OK)   { goto error; }
   
   /* get bA + Y */
   if (add_point(&pubkey.pubkey, &key->pubkey, &pubkey.pubkey, &p) != CRYPT_OK)    { goto error; }

   /* get mG */
   if (mp_read_radix(&mG->x, (unsigned char *)sets[key->idx].Gx, 16) != MP_OKAY)   { goto error; }
   if (mp_read_radix(&mG->y, (unsigned char *)sets[key->idx].Gy, 16) != MP_OKAY)   { goto error; }
   if (ecc_mulmod(&m, mG, mG, &p, key->idx) != CRYPT_OK)                           { goto error; }

   /* compare mG to bA + Y */
   if (!mp_cmp(&mG->x, &pubkey.pubkey.x) && !mp_cmp(&mG->y, &pubkey.pubkey.y)) {
      *stat = 1;
   }

   /* clear up and return */
   res = CRYPT_OK;
   goto done;
error:
   res = CRYPT_ERROR;
done:
   del_point(mG);
   ecc_free(&pubkey);
   mp_clear_multi(&p, &m, &b, NULL);
#ifdef CLEAN_STACK
   zeromem(md, sizeof(md));
#endif
   return CRYPT_OK;
}

