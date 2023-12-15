/* This is the worst code you have ever seen written on purpose.... this code is just a big hack to test
out the functionality of the library */

#ifdef SONY_PS2
#include <eetypes.h>
#include <eeregs.h>
#include "timer.h"
#endif

#include "../mycrypt.h"

int errno;


int null_setup(const unsigned char *key, int keylen, int num_rounds, symmetric_key *skey)
{
   return CRYPT_OK;
}

void null_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *key)
{
   memcpy(ct, pt, 8);
}

void null_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *key)
{
   memcpy(pt, ct, 8);
}

int null_test(void)
{
   return CRYPT_OK;
}

int null_keysize(int *desired_keysize)
{
   return CRYPT_OK;
} 

const struct _cipher_descriptor null_desc =
{
    "memcpy()",
    255,
    8, 8, 8, 1,
    &null_setup,
    &null_ecb_encrypt,
    &null_ecb_decrypt,
    &null_test,
    &null_keysize
};


prng_state prng;

void store_tests(void) 
{
 unsigned char buf[8];
 unsigned long L;
 ulong64 LL;

 printf("LOAD32/STORE32 tests\n");
 L = 0x12345678UL;
 STORE32L(L, &buf[0]);
 L = 0;
 LOAD32L(L, &buf[0]);
 if (L != 0x12345678UL) printf("LOAD/STORE32 Little don't work\n");
 LL = CONST64(0x01020304050607);
 STORE64L(LL, &buf[0]);
 LL = 0;
 LOAD64L(LL, &buf[0])
 if (LL != CONST64(0x01020304050607)) printf("LOAD/STORE64 Little don't work\n");

 L = 0x12345678UL;
 STORE32H(L, &buf[0]);
 L = 0;
 LOAD32H(L, &buf[0]);
 if (L != 0x12345678UL) printf("LOAD/STORE32 High don't work\n");
 LL = CONST64(0x01020304050607);
 STORE64H(LL, &buf[0]);
 LL = 0;
 LOAD64H(LL, &buf[0])
 if (LL != CONST64(0x01020304050607)) printf("LOAD/STORE64 High don't work\n");
}

void cipher_tests(void) {
   int x;

   printf("Ciphers compiled in\n");
 for (x = 0; cipher_descriptor[x].name != NULL; x++) {
     printf(" %12s (%2d) Key Size: %4ld to %4ld, Block Size: %3ld, Default # of rounds: %2ld\n", cipher_descriptor[x].name,
            cipher_descriptor[x].ID,
            cipher_descriptor[x].min_key_length*8,cipher_descriptor[x].max_key_length*8,
            cipher_descriptor[x].block_length*8, cipher_descriptor[x].default_rounds);
 }

}

void ecb_tests(void)
{
 int x;

 printf("ECB tests\n");
 for (x = 0; cipher_descriptor[x].name != NULL; x++) {
     printf(" %12s: ",
           cipher_descriptor[x].name);
     if ((errno = cipher_descriptor[x].test()) != CRYPT_OK)
        printf(" **failed** Reason: %s\n", error_to_string(errno));
     else 
        printf("passed\n");
 }
}

#ifdef CBC
void cbc_tests(void)
{
 symmetric_CBC cbc;
 int x, y;
 unsigned char blk[32], ct[32], key[32], IV[32];
 const unsigned char test[] = { 0XFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

 printf("CBC tests\n");
 /* ---- CBC ENCODING ---- */
 /* make up a block and IV */
 for (x = 0; x < 32; x++) blk[x] = IV[x] = x;

 /* now lets start a cbc session */
 if ((errno = cbc_start(find_cipher("blowfish"), IV, key, 16, 0, &cbc)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* now lets encode 32 bytes */
 for (x = 0; x < 4; x++)
    cbc_encrypt(blk+8*x, ct+8*x, &cbc);

 zeromem(blk, sizeof(blk));

 /* ---- CBC DECODING ---- */
 /* make up a IV */
 for (x = 0; x < 32; x++) IV[x] = x;

 /* now lets start a cbc session */
 if ((errno = cbc_start(find_cipher("blowfish"), IV, key, 16, 0, &cbc)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* now lets decode 32 bytes */
 for (x = 0; x < 4; x++)
    cbc_decrypt(ct+8*x, blk+8*x, &cbc);

 /* print output */
 for (x = y = 0; x < 32; x++) if (blk[x] != x) y = 1;
 printf("  %s\n", y?"failed":"passed");

 /* lets actually check the bytes */
 memset(IV, 0, 8); IV[0] = 0xFF;              /* IV  = FF 00 00 00 00 00 00 00 */
 memset(blk, 0, 32); blk[8] = 0xFF;           /* BLK = 00 00 00 00 00 00 00 00 FF 00 00 00 00 00 00 00 */
 cbc_start(find_cipher("memcpy()"), IV, key, 8, 0, &cbc);
 cbc_encrypt(blk, ct, &cbc);                  /* expect: FF 00 00 00 00 00 00 00 */
 cbc_encrypt(blk+8, ct+8, &cbc);              /* expect: 00 00 00 00 00 00 00 00 */
 if (memcmp(ct, test, 16)) {
    printf("CBC failed logical testing.\n");
    for (x = 0; x < 16; x++) printf("%02x ", ct[x]);
    printf("\n");
 } else {
    printf("CBC passed logical testing.\n");
 }
}
#else
void cbc_tests(void) { printf("CBC not compiled in\n"); }
#endif

#ifdef OFB
void ofb_tests(void)
{
 symmetric_OFB ofb;
 int x, y;
 unsigned char blk[32], ct[32], key[32], IV[32];

 printf("OFB tests\n");
 /* ---- ofb ENCODING ---- */
 /* make up a block and IV */
 for (x = 0; x < 32; x++) blk[x] = IV[x] = x;

 /* now lets start a ofb session */
 if ((errno = ofb_start(find_cipher("blowfish"), IV, key, 16, 0, &ofb)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* now lets encode 32 bytes */
 for (x = 0; x < 4; x++)
    ofb_encrypt(blk+8*x, ct+8*x, 8, &ofb);

 zeromem(blk, sizeof(blk));

 /* ---- ofb DECODING ---- */
 /* make up a IV */
 for (x = 0; x < 32; x++) IV[x] = x;

 /* now lets start a ofb session */
 if ((errno = ofb_start(find_cipher("blowfish"), IV, key, 16, 0, &ofb)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* now lets decode 32 bytes */
 for (x = 0; x < 4; x++)
    ofb_decrypt(ct+8*x, blk+8*x, 8, &ofb);

 /* print output */
 for (x = y = 0; x < 32; x++) if (blk[x] != x) y = 1;
 printf("  %s\n", y?"failed":"passed");
}
#else
void ofb_tests(void) { printf("OFB not compiled in\n"); }
#endif

#ifdef CFB
void cfb_tests(void)
{
 symmetric_CFB cfb;
 int x, y;
 unsigned char blk[32], ct[32], key[32], IV[32];

 printf("CFB tests\n");
 /* ---- cfb ENCODING ---- */
 /* make up a block and IV */
 for (x = 0; x < 32; x++) blk[x] = IV[x] = x;

 /* now lets start a cfb session */
 if ((errno = cfb_start(find_cipher("blowfish"), IV, key, 16, 0, &cfb)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* now lets encode 32 bytes */
 for (x = 0; x < 4; x++)
    cfb_encrypt(blk+8*x, ct+8*x, 8, &cfb);

 zeromem(blk, sizeof(blk));

 /* ---- cfb DECODING ---- */
 /* make up ahash_descriptor[prng->yarrow.hash].hashsize IV */
 for (x = 0; x < 32; x++) IV[x] = x;

 /* now lets start a cfb session */
 if ((errno = cfb_start(find_cipher("blowfish"), IV, key, 16, 0, &cfb)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* now lets decode 32 bytes */
 for (x = 0; x < 4; x++)
    cfb_decrypt(ct+8*x, blk+8*x, 8, &cfb);

 /* print output */
 for (x = y = 0; x < 32; x++) if (blk[x] != x) y = 1;
 printf("  %s\n", y?"failed":"passed");
}
#else
void cfb_tests(void) { printf("CFB not compiled in\n"); }
#endif

#ifdef CTR
void ctr_tests(void)
{
 symmetric_CTR ctr;
 int x, y;
 unsigned char blk[32], ct[32], key[32], count[32];
 const unsigned char test[] = { 0xFF, 0, 0, 0, 0, 0, 0, 0,  0, 3, 0, 0, 0, 0, 0, 0 };

 printf("CTR tests\n");
 /* ---- CTR ENCODING ---- */
 /* make up a block and IV */
 for (x = 0; x < 32; x++) blk[x] = count[x] = x;

 /* now lets start a ctr session */
 if ((errno = ctr_start(find_cipher("rijndael"), count, key, 16, 0, &ctr)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* now lets encode 32 bytes */
 for (x = 0; x < 4; x++)
    ctr_encrypt(blk+8*x, ct+8*x, 8, &ctr);

 zeromem(blk, sizeof(blk));

 /* ---- CTR DECODING ---- */
 /* make up a IV */
 for (x = 0; x < 32; x++) count[x] = x;

 /* now lets start a cbc session */
 if ((errno = ctr_start(find_cipher("rijndael"), count, key, 16, 0, &ctr)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* now lets decode 32 bytes */
 for (x = 0; x < 4; x++)
    ctr_decrypt(ct+8*x, blk+8*x, 8, &ctr);

 /* print output */
 for (x = y = 0; x < 32; x++) if (blk[x] != x) y = 1;
 printf("  %s\n", y?"failed":"passed");

 /* lets actually check the bytes */
 memset(count, 0, 8); count[0] = 0xFF;        /* IV  = FF 00 00 00 00 00 00 00 */
 memset(blk, 0, 32); blk[9] = 2;              /* BLK = 00 00 00 00 00 00 00 00 00 02 00 00 00 00 00 00 */
 ctr_start(find_cipher("memcpy()"), count, key, 8, 0, &ctr);
 ctr_encrypt(blk, ct, 8, &ctr);               /* expect: FF 00 00 00 00 00 00 00 */
 ctr_encrypt(blk+8, ct+8, 8, &ctr);           /* expect: 00 03 00 00 00 00 00 00 */
 if (memcmp(ct, test, 16)) {
    printf("CTR failed logical testing.\n");
    for (x = 0; x < 16; x++) printf("%02x ", ct[x]);
    printf("\n");
 } else {
    printf("CTR passed logical testing.\n");
 }

}
#else
void ctr_tests(void) { printf("CTR not compiled in\n"); }
#endif

void hash_tests(void)
{
 int x;
 printf("Hash tests\n");
 for (x = 0; hash_descriptor[x].name != NULL; x++) {
     printf(" %10s (%2d) ", hash_descriptor[x].name, hash_descriptor[x].ID);
     if (hash_descriptor[x].test() != CRYPT_OK)
        printf("**failed** Reason: %s\n", error_to_string(errno));
     else 
        printf("passed\n");
 }
}

#ifdef MRSA
void pad_test(void)
{
 unsigned char in[100], out[100];
 unsigned long x, y;
  
 /* make a dummy message */
 for (x = 0; x < 16; x++) in[x] = (unsigned char)x;

 /* pad the message so that random filler is placed before and after it */
 y = 100;
 if ((errno = rsa_pad(in, 16, out, &y, find_prng("yarrow"), &prng)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* depad the message to get the original content */
 memset(in, 0, sizeof(in));
 x = 100;
 if ((errno = rsa_depad(out, y, in, &x)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* check outcome */
 printf("rsa_pad: ");
 if (x != 16) { printf("Failed.  Wrong size.\n"); return; }
 for (x = 0; x < 16; x++) if (in[x] != x) { printf("Failed.  Expected %02lx and got %02x.\n", x, in[x]); return; }
 printf("passed.\n");
}

void rsa_test(void)
{
 unsigned char in[4096], out[4096];
 unsigned long x, y, z, limit;
 int stat;
 rsa_key key;
 clock_t t;

 /* ---- SINGLE ENCRYPT ---- */
 /* encrypt a short 8 byte string */
 if ((errno = rsa_make_key(&prng, find_prng("yarrow"), 1024/8, 65537, &key)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }
 for (x = 0; x < 8; x++) in[x] = (unsigned char)(x+1);
 y = sizeof(in);
 if ((errno = rsa_exptmod(in, 8, out, &y, PK_PUBLIC, &key)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* decrypt it */
 zeromem(in, sizeof(in));
 x = sizeof(out);
 if ((errno = rsa_exptmod(out, y, in, &x, PK_PRIVATE, &key)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }

 /* compare */
 printf("RSA    : ");
 for (x = 0; x < 8; x++) if (in[x] != (x+1)) { printf("Failed.  x==%02lx, in[%ld]==%02x\n", x, x, in[x]); }
 printf("passed.\n");

#ifdef PK_PACKET 
 /* ---- BLOCK ENCRYPT ---- */
 /* now lets test rsa_encrypt() */
 for (x = 0; x < 8; x++) in[x] = (unsigned char)x;
 x = sizeof(out);
 if ((errno = rsa_encrypt(in, 8, out, &x, &prng, find_prng("yarrow"), find_cipher("rijndael"), &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }

 /* test rsa_decrypt() */
 zeromem(in, sizeof(in));
 y = sizeof(in);
 if ((errno = rsa_decrypt(out, x, in, &y, &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("rsa_encrypt()/rsa_decrypt(): ");
 for (y = 0; y < 8; y++) if (in[y] != y) { printf("failed.\n"); return; }
 printf("Passed.\n");

 /* ---- SIGNATURES ---- */
 x = sizeof(in);
 if ((errno = rsa_sign("hello", 5, in, &x, find_hash("md5"), &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 if ((errno = rsa_verify(in, "hello", 5, &stat, &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("RSA Signatures: %s, ", (stat==1)?"pass":"fail");
 if ((errno = rsa_verify(in, "abcde", 5, &stat, &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("%s\n", (stat==0)?"pass":"fail");

 /* ---- EXPORT/IMPORT ---- */
 x = sizeof(out);
 if ((errno = rsa_export(out, &x, PK_PRIVATE_OPTIMIZED, &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("RSA Export takes %lu bytes\n", x);
 rsa_free(&key);
 if ((errno = rsa_import(out, &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("RSA Import: ");
 if ((errno = rsa_verify(in, "hello", 5, &stat, &key)) != CRYPT_OK) { 
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("%s, ", (stat==1)?"pass":"fail");
 if ((errno = rsa_verify(in, "abcde", 5, &stat, &key)) != CRYPT_OK) { 
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("%s\n", (stat==0)?"pass":"fail");
#endif 

 /* test the rsa_encrypt_key functions */
 for (x = 0; x < 16; x++) in[x] = x;
 y = sizeof(out);
 if ((errno = rsa_encrypt_key(in, 16, out, &y, &prng, find_prng("yarrow"), &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 zeromem(in, sizeof(in));
 x = sizeof(in);
 if ((errno = rsa_decrypt_key(out, in, &x, &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("RSA en/de crypt key routines: ");
 if (x != 16) { printf("Failed (length)\n"); return; }
 for (x = 0; x < 16; x++) if (in[x] != x) { printf("Failed (contents)\n"); return; }
 printf("Passed\n");

 /* test sign_hash functions */
 for (x = 0; x < 16; x++) in[x] = x;
 x = sizeof(in);
 if ((errno = rsa_sign_hash(in, 16, out, &x, &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("RSA signed hash: %lu bytes\n", x);
 if ((errno = rsa_verify_hash(out, in, &stat, &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("Verify hash: %s, ", stat?"passed":"failed");
 in[0] ^= 1;
 if ((errno = rsa_verify_hash(out, in, &stat, &key)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("%s\n", (!stat)?"passed":"failed");
 rsa_free(&key);

 /* make a RSA key */
#ifdef SONY_PS2
   limit = 1024;
#else
   limit = 2048;
#endif

 for (z = 1024; z <= limit; z += 512) {
    t = XCLOCK();
    if ((errno = rsa_make_key(&prng, find_prng("yarrow"), z/8, 65537, &key)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }
    t = XCLOCK() - t;
    printf("Took %.0f ms to make a %ld-bit RSA key.\n", 1000.0 * ((double)t / (double)XCLOCKS_PER_SEC), z);

    /* time encryption */
    y = sizeof(in);
    t = XCLOCK();
    if ((errno = rsa_exptmod(in, 8, out, &y, PK_PUBLIC, &key)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }
    t = XCLOCK() - t;
    printf("Took %.0f ms to encrypt with a %ld-bit RSA key.\n", 1000.0 * ((double)t / (double)XCLOCKS_PER_SEC), z);

    /* time decryption */
    x = sizeof(out);
    t = XCLOCK();
    if ((errno = rsa_exptmod(out, y, in, &x, PK_PRIVATE, &key)) != CRYPT_OK) { printf("Error: %s\n", error_to_string(errno)); return; }
    t = XCLOCK() - t;
    printf("Took %.0f ms to decrypt with a %ld-bit RSA key.\n", 1000.0 * ((double)t / (double)XCLOCKS_PER_SEC), z);
    rsa_free(&key);
 }
 


}
#else
void pad_test(void) { printf("MRSA not compiled in\n"); }
void rsa_test(void) { printf("MRSA not compiled in\n"); }
#endif

#ifdef BASE64
void base64_test(void)
{
   unsigned char buf[2][100];
   unsigned long x, y;

   printf("Base64 tests\n");
   zeromem(buf, sizeof(buf));
   for (x = 0; x < 16; x++) buf[0][x] = (unsigned char)x;

   x = 100;
   if (base64_encode(buf[0], 16, buf[1], &x) != CRYPT_OK) {
      printf("  error: %s\n", error_to_string(errno));
      return;
   }
   printf("  encoded 16 bytes to %ld bytes...[%s]\n", x, buf[1]);
   memset(buf[0], 0, 100);
   y = 100;
   if (base64_decode(buf[1], x, buf[0], &y) != CRYPT_OK) {
      printf("  error: %s\n", error_to_string(errno));
      return;
   }
   printf("  decoded %ld bytes to %ld bytes\n", x, y);
   for (x = 0; x < 16; x++) if (buf[0][x] != x) { 
      printf(" **failed**\n"); 
      return; 
   }
   printf("  passed\n");
}
#else
void base64_test(void) { printf("Base64 not compiled in\n"); }
#endif

void time_hash(void)
{
    clock_t t1;
    int x, y;
    unsigned long z;
    unsigned char input[4096], out[MAXBLOCKSIZE];
    printf("Hash Time Trials (4KB blocks):\n");
    for (x = 0; hash_descriptor[x].name != NULL; x++) {
        t1 = XCLOCK();
        z = sizeof(out);
        y = 0;
        while (XCLOCK() - t1 < (3 * XCLOCKS_PER_SEC)) {
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z);
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z);
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z);
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z); 
            hash_memory(x, input, 4096, out, &z); y += 16;
        }
        t1 = XCLOCK() - t1;
        printf("%-20s: Hash at %5.2f Mbit/sec\n", hash_descriptor[x].name,
               ((8.0 * 4096.0) * ((double)y / ((double)t1 / (double)XCLOCKS_PER_SEC))) / 1000000.0);
    }
}

void time_ecb(void)
{
    clock_t t1, t2;
    long x, y1, y2;
    unsigned char pt[32], key[32];
    symmetric_key skey;
    void (*func)(const unsigned char *, unsigned char *, symmetric_key *);

    printf("ECB Time Trials for the Symmetric Ciphers:\n");
    for (x = 0; cipher_descriptor[x].name != NULL; x++) {
        cipher_descriptor[x].setup(key, cipher_descriptor[x].min_key_length, 0, &skey);

#define DO1   func(pt,pt,&skey);
#define DO2   DO1 DO1
#define DO4   DO2 DO2
#define DO8   DO4 DO4
#define DO16  DO8 DO8
#define DO32  DO16 DO16
#define DO64  DO32 DO32
#define DO128 DO64 DO64
#define DO256 DO128 DO128 

        func = cipher_descriptor[x].ecb_encrypt;
        y1 = 0;
        t1 = XCLOCK();
        while (XCLOCK() - t1 < 2*XCLOCKS_PER_SEC) {
            DO256; y1 += 256;
        }
        t1 = XCLOCK() - t1;

        func = cipher_descriptor[x].ecb_decrypt;
        y2 = 0;
        t2 = XCLOCK();
        while (XCLOCK() - t2 < 2*XCLOCKS_PER_SEC) {
            DO256; y2 += 256;
        }
        t2 = XCLOCK() - t2;
        printf("%-20s: Encrypt at %5.2f Mbit/sec and Decrypt at %5.2f Mbit/sec\n",
               cipher_descriptor[x].name,
               ((8.0 * (double)cipher_descriptor[x].block_length) * ((double)y1 / ((double)t1 / (double)XCLOCKS_PER_SEC))) / 1000000.0,
               ((8.0 * (double)cipher_descriptor[x].block_length) * ((double)y2 / ((double)t2 / (double)XCLOCKS_PER_SEC))) / 1000000.0);

#undef DO256
#undef DO128
#undef DO64
#undef DO32
#undef DO16
#undef DO8
#undef DO4
#undef DO2
#undef DO1
    }
}

#ifdef MDH
void dh_tests(void)
{
   unsigned char buf[3][4096];
   unsigned long x, y, z;
   int low, high, stat, stat2;
   dh_key usera, userb;
   clock_t t1;

/*   if ((errno = dh_test()) != CRYPT_OK) printf("DH Error: %s\n", error_to_string(errno)); */

   dh_sizes(&low, &high);
   printf("DH Keys from %d to %d supported.\n", low*8, high*8);

   /* make up two keys */
   if ((errno = dh_make_key(&prng, find_prng("yarrow"), 96, &usera)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }
   if ((errno = dh_make_key(&prng, find_prng("yarrow"), 96, &userb)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   /* make the shared secret */
   x = 4096;
   if ((errno = dh_shared_secret(&usera, &userb, buf[0], &x)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   y = 4096;
   if ((errno = dh_shared_secret(&userb, &usera, buf[1], &y)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }
   if (y != x) { printf("DH Shared keys are not same size.\n"); return; }
   if (memcmp(buf[0], buf[1], x)) { printf("DH Shared keys not same contents.\n"); return; }

   /* now export userb */
   y = 4096;
   if ((errno = dh_export(buf[1], &y, PK_PUBLIC, &userb)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }
   dh_free(&userb);

   /* import and make the shared secret again */
   if ((errno = dh_import(buf[1], &userb)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }
   z = 4096;
   if ((errno = dh_shared_secret(&usera, &userb, buf[2], &z)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   printf("DH routines: ");
   if (z != x) { printf("failed.  Size don't match?\n"); return; }
   if (memcmp(buf[0], buf[2], x)) { printf("Failed.  Content didn't match.\n"); return; }
   printf("Passed\n");
   dh_free(&usera);
   dh_free(&userb);

/* time stuff */
   t1 = XCLOCK();
   dh_make_key(&prng, find_prng("yarrow"), 64, &usera);
   t1 = XCLOCK() - t1;
   printf("Make dh-512 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   dh_free(&usera);

   t1 = XCLOCK();
   dh_make_key(&prng, find_prng("yarrow"), 96, &usera);
   t1 = XCLOCK() - t1;
   printf("Make dh-768 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   dh_free(&usera);

   t1 = XCLOCK();
   dh_make_key(&prng, find_prng("yarrow"), 128, &usera);
   t1 = XCLOCK() - t1;
   printf("Make dh-1024 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   dh_free(&usera);

#ifndef SONY_PS2
   t1 = XCLOCK();
   dh_make_key(&prng, find_prng("yarrow"), 160, &usera);
   t1 = XCLOCK() - t1;
   printf("Make dh-1280 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   dh_free(&usera);

   t1 = XCLOCK();
   dh_make_key(&prng, find_prng("yarrow"), 192, &usera);
   t1 = XCLOCK() - t1;
   printf("Make dh-1536 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   dh_free(&usera);

   t1 = XCLOCK();
   dh_make_key(&prng, find_prng("yarrow"), 224, &usera);
   t1 = XCLOCK() - t1;
   printf("Make dh-1792 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   dh_free(&usera);

   t1 = XCLOCK();
   dh_make_key(&prng, find_prng("yarrow"), 256, &usera);
   t1 = XCLOCK() - t1;
   printf("Make dh-2048 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   dh_free(&usera);

   t1 = XCLOCK();
   dh_make_key(&prng, find_prng("yarrow"), 320, &usera);
   t1 = XCLOCK() - t1;
   printf("Make dh-2560 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   dh_free(&usera);
#endif   
   
#ifdef PK_PACKET
/* try dh packet stuff */
   for (x = 0; x < 16; x++) buf[0][x] = (unsigned char)x;
   dh_make_key(&prng, find_prng("yarrow"), 24, &usera);

   x = 4096;
   if (dh_encrypt(buf[0], 16, buf[1], &x, &prng, find_prng("yarrow"), find_cipher("rijndael"),
                   find_hash("sha1"), &usera) != CRYPT_OK) {
      printf("dh_encrypt says %s\n", error_to_string(errno));
      return;
   }
   printf("dh encrypted 16 bytes into %ld bytes!\n", x);

   y = 4096;
   if ((errno = dh_decrypt(buf[1], x, buf[2], &y, &usera)) != CRYPT_OK) {
      printf("dh_decrypt says %s\n", error_to_string(errno));
      return;
   }

   printf("dh packet: ");
   if (16 != y) { printf("Failed: Sizes different! 16 vs %ld\n", y); return; }
   if (memcmp(buf[0], buf[2], 16)) { printf("Failed; Content mismatch.\n"); return; }
   printf("Passed!\n");
   dh_free(&usera);

/* try dh signatures */
   dh_make_key(&prng, find_prng("yarrow"), 96, &usera);
   x = 4096;
   if ((errno = dh_sign("hello", 5, buf[0], &x, find_hash("sha1"), &prng, find_prng("yarrow"), &usera)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   printf("dh-768 Signature took %ld bytes\n", x);

   if ((errno = dh_verify(buf[0], "hello", 5, &stat, &usera)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }
   if ((errno = dh_verify(buf[0], "hellp", 5, &stat2, &usera)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   printf("dh Signatures: %s (%d,%d)\n", ((stat==1)&&(stat2==0))?"passed":"failed", stat,stat2);
   dh_free(&usera);
#endif  

/* test encrypt_key */
 dh_make_key(&prng, find_prng("yarrow"), 96, &usera);
 for (x = 0; x < 16; x++) buf[0][x] = x;
 y = sizeof(buf[1]);
 if ((errno = dh_encrypt_key(buf[0], 16, buf[1], &y, &prng, find_prng("yarrow"), find_hash("md5"), &usera)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 zeromem(buf[0], sizeof(buf[0]));
 x = sizeof(buf[0]);
 if ((errno = dh_decrypt_key(buf[1], buf[0], &x, &usera)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("DH en/de crypt key routines: ");
 if (x != 16) { printf("Failed (length)\n"); return; }
 for (x = 0; x < 16; x++) if (buf[0][x] != x) { printf("Failed (contents)\n"); return; }
 printf("Passed (size %lu)\n", y);

/* test sign_hash */
   for (x = 0; x < 16; x++) buf[0][x] = x;
   x = sizeof(buf[1]);
   if ((errno = dh_sign_hash(buf[0], 16, buf[1], &x, &prng, find_prng("yarrow"), &usera)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
   }
   if (dh_verify_hash(buf[1], buf[0], 16, &stat, &usera)) {
    printf("Error: %s\n", error_to_string(errno));
    return;
   }
   buf[0][0] ^= 1;
   if (dh_verify_hash(buf[1], buf[0], 16, &stat2, &usera)) {
    printf("Error: %s\n", error_to_string(errno));
    return;
   }
   printf("dh_sign/verify_hash: %s (%d,%d)\n", ((stat==1)&&(stat2==0))?"passed":"failed", stat,stat2);
 dh_free(&usera);
}
#else
void dh_tests(void) { printf("MDH not compiled in\n"); }
#endif

int callback_x = 0;
void callback(void)
{ 
   printf("%c\x08", "-\\|/"[++callback_x & 3]); 
#ifndef SONY_PS2
   fflush(stdout);
#endif
}

void rng_tests(void)
{
   unsigned char buf[16];
   clock_t t1;
   int x, y;

   printf("RNG tests\n");
   t1 = XCLOCK();
   x = rng_get_bytes(buf, sizeof(buf), &callback);
   t1 = XCLOCK() - t1;
   printf("  %f bytes per second...",
         (double)x / ((double)t1 / (double)XCLOCKS_PER_SEC));
   printf("read %d bytes.\n  ", x);
   for (y = 0; y < x; y++)
       printf("%02x ", buf[y]);
   printf("\n");

#ifdef YARROW
   if ((errno = rng_make_prng(128, find_prng("yarrow"), &prng, &callback)) != CRYPT_OK) {
       printf(" starting yarrow error: %s\n", error_to_string(errno));
       exit(-1);
   }
#endif
}

#ifdef MECC
void ecc_tests(void)
{
   unsigned char buf[4][4096];
   unsigned long x, y, z;
   int stat, stat2, low, high;
   ecc_key usera, userb;
   clock_t t1;

   if ((errno = ecc_test()) != CRYPT_OK) printf("ecc Error: %s\n", error_to_string(errno));

   ecc_sizes(&low, &high);
   printf("ecc Keys from %d to %d supported.\n", low*8, high*8);

   /* make up two keys */
   if ((errno = ecc_make_key(&prng, find_prng("yarrow"), 24, &usera)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }
   if ((errno = ecc_make_key(&prng, find_prng("yarrow"), 24, &userb)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   /* make the shared secret */
   x = 4096;
   if ((errno = ecc_shared_secret(&usera, &userb, buf[0], &x)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   y = 4096;
   if ((errno = ecc_shared_secret(&userb, &usera, buf[1], &y)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   if (y != x) { printf("ecc Shared keys are not same size.\n"); return; }

   if (memcmp(buf[0], buf[1], x)) { printf("ecc Shared keys not same contents.\n"); return; }

   /* now export userb */
   y = 4096;
   if ((errno = ecc_export(buf[1], &y, PK_PUBLIC, &userb)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }
   ecc_free(&userb);
   printf("ECC-192 export took %ld bytes\n", y);

   /* import and make the shared secret again */
   if ((errno = ecc_import(buf[1], &userb)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   z = 4096;
   if ((errno = ecc_shared_secret(&usera, &userb, buf[2], &z)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   printf("ecc routines: ");
   if (z != x) { printf("failed.  Size don't match?\n"); return; }
   if (memcmp(buf[0], buf[2], x)) { printf("Failed.  Content didn't match.\n"); return; }
   printf("Passed\n");
   ecc_free(&usera);
   ecc_free(&userb);

/* time stuff */
   t1 = XCLOCK();
   ecc_make_key(&prng, find_prng("yarrow"), 20, &usera);
   t1 = XCLOCK() - t1;
   printf("Make ECC-160 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   ecc_free(&usera);

   t1 = XCLOCK();
   ecc_make_key(&prng, find_prng("yarrow"), 24, &usera);
   t1 = XCLOCK() - t1;
   printf("Make ECC-192 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   ecc_free(&usera);

   t1 = XCLOCK();
   ecc_make_key(&prng, find_prng("yarrow"), 28, &usera);
   t1 = XCLOCK() - t1;
   printf("Make ECC-224 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   ecc_free(&usera);
   
#ifndef SONY_PS2
   t1 = XCLOCK();
   ecc_make_key(&prng, find_prng("yarrow"), 32, &usera);
   t1 = XCLOCK() - t1;
   printf("Make ECC-256 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   ecc_free(&usera);

   t1 = XCLOCK();
   ecc_make_key(&prng, find_prng("yarrow"), 48, &usera);
   t1 = XCLOCK() - t1;
   printf("Make ECC-384 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   ecc_free(&usera);

   t1 = XCLOCK();
   ecc_make_key(&prng, find_prng("yarrow"), 65, &usera);
   t1 = XCLOCK() - t1;
   printf("Make ECC-521 key took %f msec\n", 1000.0 * ((double)t1 / (double)XCLOCKS_PER_SEC));
   ecc_free(&usera);
#endif   

#ifdef PK_PACKET
/* try ECC packet stuff */
   for (x = 0; x < 16; x++) buf[0][x] = (unsigned char)x;
   ecc_make_key(&prng, find_prng("yarrow"), 20, &usera);

   x = 4096;
   if (ecc_encrypt(buf[0], 16, buf[1], &x, &prng, find_prng("yarrow"), find_cipher("rijndael"),
                   find_hash("tiger"), &usera) != CRYPT_OK) {
      printf("ecc_encrypt says %s\n", error_to_string(errno));
      return;
   }
   printf("Ecc encrypted 16 bytes into %ld bytes!\n", x);

   y = 4096;
   if ((errno = ecc_decrypt(buf[1], x, buf[2], &y, &usera)) != CRYPT_OK) {
      printf("ecc_decrypt says %s\n", error_to_string(errno));
      return;
   }

   printf("ECC packet: ");
   if (16 != y) { printf("Failed: Sizes different! 16 vs %ld\n", y); return; }
   if (memcmp(buf[0], buf[2], 16)) { printf("Failed; Content mismatch.\n"); return; }
   printf("Passed!\n");
   ecc_free(&usera);

/* try ECC signatures */
   ecc_make_key(&prng, find_prng("yarrow"), 20, &usera);
   x = 4096;
   if ((errno = ecc_sign("hello", 5, buf[0], &x, find_hash("sha1"), &prng, find_prng("yarrow"), &usera)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   printf("ECC-160 Signature took %ld bytes\n", x);

   if ((errno = ecc_verify(buf[0], "hello", 5, &stat, &usera)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }
   if ((errno = ecc_verify(buf[0], "hellp", 5, &stat2, &usera)) != CRYPT_OK) {
      printf("Error: %s\n", error_to_string(errno));
      return;
   }

   printf("ECC Signatures: %s (%d,%d)\n", ((stat==1)&&(stat2==0))?"passed":"failed", stat,stat2);
   ecc_free(&usera);
#endif

/* test encrypt_key */
 ecc_make_key(&prng, find_prng("yarrow"), 32, &usera);
 for (x = 0; x < 16; x++) buf[0][x] = x;
 y = sizeof(buf[1]);
 if ((errno = ecc_encrypt_key(buf[0], 16, buf[1], &y, &prng, find_prng("yarrow"), find_hash("md5"), &usera)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 zeromem(buf[0], sizeof(buf[0]));
 x = sizeof(buf[0]);
 if ((errno = ecc_decrypt_key(buf[1],buf[0], &x, &usera)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
 }
 printf("ECC en/de crypt key routines: ");
 if (x != 16) { printf("Failed (length)\n"); return; }
 for (x = 0; x < 16; x++) if (buf[0][x] != x) { printf("Failed (contents)\n"); return; }
 printf("Passed (size: %lu)\n", y);
/* test sign_hash */
   for (x = 0; x < 16; x++) buf[0][x] = x;
   x = sizeof(buf[1]);
   if ((errno = ecc_sign_hash(buf[0], 16, buf[1], &x, &prng, find_prng("yarrow"), &usera)) != CRYPT_OK) {
    printf("Error: %s\n", error_to_string(errno));
    return;
   }
   if (ecc_verify_hash(buf[1], buf[0], 16, &stat, &usera)) {
    printf("Error: %s\n", error_to_string(errno));
    return;
   }
   buf[0][0] ^= 1;
   if (ecc_verify_hash(buf[1], buf[0], 16, &stat2, &usera)) {
    printf("Error: %s\n", error_to_string(errno));
    return;
   }
   printf("ecc_sign/verify_hash: %s (%d,%d)\n", ((stat==1)&&(stat2==0))?"passed":"failed", stat,stat2);
 ecc_free(&usera);
}
#else
void ecc_tests(void) { printf("MECC not compiled in\n"); }
#endif

#ifdef GF
void gf_tests(void)
{
   gf_int a, b, c, d;
   int n;
   unsigned char buf[1024];

   printf("GF tests\n");
   gf_zero(a);gf_zero(b);gf_zero(c);gf_zero(d);

   /* a == 0x18000000b */
   a[1] = 1;
   a[0] = 0x8000000bUL;

   /* b == 0x012345678 */
   b[0] = 0x012345678UL;

   /* find 1/b mod a */
   gf_invmod(b,a,c);

   /* find 1/1/b mod a */
   gf_invmod(c,a,d);

   /* display them */
   printf("  %08lx %08lx\n", c[0], d[0]);

   /* store as binary string */
   n = gf_size(a);
   printf("  a takes %d bytes\n", n);
   gf_toraw(a, buf);
   gf_readraw(a, buf, n);
   printf("  a == %08lx%08lx\n", a[1], a[0]);

   /* primality testing */
   gf_zero(a);
   a[0] = 0x169;
   printf("  GF prime: %s, ", gf_is_prime(a)?"passed":"failed");
   a[0] = 0x168;
   printf("  %s\n", gf_is_prime(a)?"failed":"passed");

   /* test sqrt code */
   gf_zero(a);
   a[1] = 0x00000001;
   a[0] = 0x8000000bUL;
   gf_zero(b);
   b[0] = 0x12345678UL;

   gf_sqrt(b, a, c);
   gf_mulmod(c, c, a, b);
   printf("  (%08lx)^2 = %08lx (mod %08lx%08lx) \n", c[0], b[0], a[1], a[0]);
}
#else
void gf_tests(void) { printf("GF not compiled in\n"); }
#endif

#ifdef MPI
void test_prime(void)
{
   unsigned char buf[1024];
   mp_int a;
   int x;
  
   /* make a 1024 bit prime */
   mp_init(&a);
   rand_prime(&a, 128, &prng, find_prng("yarrow"));

   /* dump it */
   mp_todecimal(&a, buf);
   printf("1024-bit prime:\n");
   for (x = 0; x < (int)strlen(buf); ) {
       printf("%c", buf[x]);
       if (!(++x % 60)) printf("\\ \n");
   }
   printf("\n\n");

   mp_clear(&a);
}
#else
void test_prime(void) { printf("MPI not compiled in\n"); }
#endif

void register_all_algs(void)
{
#ifdef BLOWFISH
   register_cipher(&blowfish_desc);
#endif
#ifdef XTEA
   register_cipher(&xtea_desc);
#endif
#ifdef RC5
   register_cipher(&rc5_desc);
#endif
#ifdef RC6
   register_cipher(&rc6_desc);
#endif
#ifdef SAFERP
   register_cipher(&saferp_desc);
#endif
#ifdef SERPENT
   register_cipher(&serpent_desc);
#endif
#ifdef RIJNDAEL
   register_cipher(&rijndael_desc);
#endif
#ifdef SAFER
   register_cipher(&safer_k64_desc);
   register_cipher(&safer_sk64_desc);
   register_cipher(&safer_k128_desc);
   register_cipher(&safer_sk128_desc);
#endif
#ifdef TWOFISH
   register_cipher(&twofish_desc);
#endif
#ifdef RC2
   register_cipher(&rc2_desc);
#endif
#ifdef CAST5
   register_cipher(&cast5_desc);
#endif
#ifdef DES
   register_cipher(&des_desc);
   register_cipher(&des3_desc);
#endif

   register_cipher(&null_desc);

#ifdef SHA256
   register_hash(&sha256_desc);
#endif
#ifdef TIGER
   register_hash(&tiger_desc);
#endif
#ifdef SHA1
   register_hash(&sha1_desc);
#endif
#ifdef MD5
   register_hash(&md5_desc);
#endif
#ifdef SHA384
   register_hash(&sha384_desc);
#endif
#ifdef SHA512
   register_hash(&sha512_desc);
#endif
#ifdef MD4
   register_hash(&md4_desc);
#endif
#ifdef MD2
   register_hash(&md2_desc);
#endif

#ifdef YARROW
   register_prng(&yarrow_desc);
#endif
#ifdef SPRNG
   register_prng(&sprng_desc);
#endif
}

void kr_display(pk_key *kr)
{
   static const char *system[] = { "NON-KEY", "RSA", "DH", "ECC" };
   static const char *type[]   = { "PRIVATE", "PUBLIC", "PRIVATE_OPTIMIZED" };

   while (kr->system != NON_KEY) {
       printf("CRC [%08lx], System [%10s], Type [%20s], %s, %s, %s\n", kr->ID, system[kr->system], type[kr->key_type], kr->name, kr->email, kr->description);
       kr = kr->next;
   }
   printf("\n");
}

void kr_test_makekeys(pk_key **kr)
{
   if ((errno = kr_init(kr)) != CRYPT_OK) {
      printf("KR init error %s\n", error_to_string(errno));
      exit(-1);
   }

   /* make a ECC key */
   printf("KR: Making ECC key...\n");
   if ((errno = kr_make_key(*kr, &prng, find_prng("yarrow"), ECC_KEY, 24, "ecckey", "ecc@ecc.ecc", "ecckey one")) != CRYPT_OK) {
      printf("Make key error: %s\n", error_to_string(errno));
      exit(-1);
   }

   /* make a RSA key */
   printf("KR: Making RSA key...\n");
   if ((errno = kr_make_key(*kr, &prng, find_prng("yarrow"), RSA_KEY, 128, "rsakey", "rsa@rsa.rsa", "rsakey one")) != CRYPT_OK) {
      printf("Make key error: %s\n", error_to_string(errno));
      exit(-1);
   }

   /* make a DH key */
   printf("KR: Making DH key...\n");
   if ((errno = kr_make_key(*kr, &prng, find_prng("yarrow"), DH_KEY, 128, "dhkey", "dh@dh.dh", "dhkey one")) != CRYPT_OK) {
      printf("Make key error: %s\n", error_to_string(errno));
      exit(-1);
   }
}

void kr_test(void)
{
   pk_key *kr, *_kr;
   unsigned char buf[8192], buf2[8192], buf3[8192];
   unsigned long len;
   int i, j, stat;
#ifndef NO_FILE   
   FILE *f;
#endif

   kr_test_makekeys(&kr);

   printf("The original list:\n");
   kr_display(kr);

   for (i = 0; i < 3; i++) {
       len = sizeof(buf);
       if ((errno = kr_export(kr, kr->ID, kr->key_type, buf, &len)) != CRYPT_OK) {
          printf("Error exporting key %d, %s\n", i, error_to_string(errno));
          exit(-1);
       }
       printf("Exported key was: %lu bytes\n", len);
       if ((errno = kr_del(&kr, kr->ID)) != CRYPT_OK) {
          printf("Error deleting key %d, %s\n", i, error_to_string(errno));
          exit(-1);
       }
       kr_display(kr);
       if ((errno = kr_import(kr, buf)) != CRYPT_OK) {
          printf("Error importing key %d, %s\n", i, error_to_string(errno));
          exit(-1);
       }
       kr_display(kr);
   }         

   for (i = 0; i < 3; i++) {
       len = sizeof(buf);
       if ((errno = kr_export(kr, kr->ID, PK_PUBLIC, buf, &len)) != CRYPT_OK) {
          printf("Error exporting key %d, %s\n", i, error_to_string(errno));
          exit(-1);
       }
       printf("Exported key was: %lu bytes\n", len);
       if ((errno = kr_del(&kr, kr->ID)) != CRYPT_OK) {
          printf("Error deleting key %d, %s\n", i, error_to_string(errno));
          exit(-1);
       }
       kr_display(kr);
       if ((errno = kr_import(kr, buf)) != CRYPT_OK) {
          printf("Error importing key %d, %s\n", i, error_to_string(errno));
          exit(-1);
       }
       kr_display(kr);
   }

   if ((errno = kr_clear(&kr)) != CRYPT_OK) {
      printf("Error clearing ring: %s\n", error_to_string(errno));
      exit(-1);
   }


/* TEST output to file */
#ifndef NO_FILE

   if ((errno = kr_init(&kr)) != CRYPT_OK) {
      printf("KR init error %s\n", error_to_string(errno));
      exit(-1);
   }
   kr_test_makekeys(&kr);

   /* save to file */
   f = fopen("ring.dat", "wb");
   if ((errno = kr_save(kr, f, NULL)) != CRYPT_OK) {
      printf("kr_save error %s\n", error_to_string(errno));
      exit(-1);
   }
   fclose(f);

   /* delete and load */
   if ((errno = kr_clear(&kr)) != CRYPT_OK) {
      printf("clear error: %s\n", error_to_string(errno));
      exit(-1);
   }

   f = fopen("ring.dat", "rb");
   if ((errno = kr_load(&kr, f, NULL)) != CRYPT_OK) {
      printf("kr_load error %s\n", error_to_string(errno));
      exit(-1);
   }
   fclose(f);
   remove("ring.dat");
   printf("After load and save...\n");
   kr_display(kr);
  
   if ((errno = kr_clear(&kr)) != CRYPT_OK) {
      printf("clear error: %s\n", error_to_string(errno));
      exit(-1);
   }

#endif

/* test the packet encryption/sign stuff */
   for (i = 0; i < 16; i++) buf[i] = i;
   kr_test_makekeys(&kr);
   _kr = kr;
   for (i = 0; i < 3; i++) {
       printf("Testing a key with system %d, type %d:\t", _kr->system, _kr->key_type);
       len = sizeof(buf2);
       if ((errno = kr_encrypt_key(kr, _kr->ID, buf, 16, buf2, &len, &prng, find_prng("yarrow"), find_hash("md5"))) != CRYPT_OK) {
          printf("Encrypt error, %d, %s\n", i, error_to_string(errno));
          exit(-1);
       }
       len = sizeof(buf3);
       if ((errno = kr_decrypt_key(kr, buf2, buf3, &len)) != CRYPT_OK) {
          printf("decrypt error, %d, %s\n", i, error_to_string(errno));
          exit(-1);
       }
       if (len != 16 || memcmp(buf3, buf, 16)) {
          printf("kr_decrypt_key failed, %i, %lu\n", i, len);
          exit(-1);
       }
       printf("kr_encrypt_key passed, ");

       len = sizeof(buf2);
       if ((errno = kr_sign_hash(kr, _kr->ID, buf, 16, buf2, &len, &prng, find_prng("yarrow"))) != CRYPT_OK) {
          printf("kr_sign_hash failed, %i, %lu\n", i, len);
          exit(-1);
       }
       printf("kr_sign_hash: ");
       if ((errno = kr_verify_hash(kr, buf2, buf, 16, &stat)) != CRYPT_OK) {
          printf("kr_sign_hash failed, %i, %lu\n", i, len);
          exit(-1);
       }
       printf("%s, ", stat?"passed":"failed");
       buf[15] ^= 1;
       if ((errno = kr_verify_hash(kr, buf2, buf, 16, &stat)) != CRYPT_OK) {
          printf("kr_sign_hash failed, %i, %lu\n", i, len);
          exit(-1);
       }
       printf("%s\n", (!stat)?"passed":"failed");
       buf[15] ^= 1;

       len = sizeof(buf);
       if ((errno = kr_fingerprint(kr, _kr->ID, find_hash("sha1"), buf, &len)) != CRYPT_OK) {
          printf("kr_fingerprint failed, %i, %lu\n", i, len);
          exit(-1);
       }
       printf("Fingerprint:  ");
       for (j = 0; j < 20; j++) {
           printf("%02x", buf[j]);
           if (j < 19) printf(":");
       }
       printf("\n\n");

       _kr = _kr->next;
    }

/* Test encrypting/decrypting to a public key */
/* first dump the other two keys */
   kr_del(&kr, kr->ID);
   kr_del(&kr, kr->ID);
   kr_display(kr);

   /* now export it as public and private */
   len = sizeof(buf);
   if ((errno = kr_export(kr, kr->ID, PK_PUBLIC, buf, &len)) != CRYPT_OK) {
       printf("Error exporting key %d, %s\n", i, error_to_string(errno));
       exit(-1);
   }

   /* check boundaries */
   memset(buf+len, 0, sizeof(buf)-len);

   len = sizeof(buf2);
   if ((errno = kr_export(kr, kr->ID, PK_PRIVATE, buf2, &len)) != CRYPT_OK) {
       printf("Error exporting key  %s\n", error_to_string(errno));
       exit(-1);
   }

   /* check boundaries */
   memset(buf2+len, 0, sizeof(buf2)-len);

   /* delete the key and import the public */
   kr_clear(&kr);
   kr_init(&kr);
   kr_display(kr);
   if ((errno = kr_import(kr, buf)) != CRYPT_OK) {
      printf("Error importing key %s\n", error_to_string(errno));
      exit(-1);
   }
   kr_display(kr);
   
   /* now encrypt a buffer */
   for (i = 0; i < 16; i++) buf[i] = i;
   len = sizeof(buf3);
   if ((errno = kr_encrypt_key(kr, kr->ID, buf, 16, buf3, &len, &prng, find_prng("yarrow"), find_hash("md5"))) != CRYPT_OK) {
      printf("Encrypt error, %d, %s\n", i, error_to_string(errno));
      exit(-1);
   }

   /* now delete the key and import the private one */
   kr_clear(&kr);
   kr_init(&kr);
   kr_display(kr);
   if ((errno = kr_import(kr, buf2)) != CRYPT_OK) {
      printf("Error importing key %s\n", error_to_string(errno));
      exit(-1);
   }
   kr_display(kr);

   /* now decrypt */
   len = sizeof(buf2);
   if ((errno = kr_decrypt_key(kr, buf3, buf2, &len)) != CRYPT_OK) {
      printf("decrypt error, %s\n", error_to_string(errno));
      exit(-1);
   }

   printf("KR encrypt to public, decrypt with private: ");
   if (len == 16 && !memcmp(buf2, buf, 16)) {
      printf("passed\n"); 
   } else {
      printf("failed\n");
   }

   kr_clear(&kr);

}   

void test_errs(void)
{
   #define ERR(x)  printf("%25s => %s\n", #x, error_to_string(x));

   ERR(CRYPT_OK);
   ERR(CRYPT_ERROR);

   ERR(CRYPT_INVALID_KEYSIZE);
   ERR(CRYPT_INVALID_ROUNDS);
   ERR(CRYPT_FAIL_TESTVECTOR);

   ERR(CRYPT_BUFFER_OVERFLOW);
   ERR(CRYPT_INVALID_PACKET);

   ERR(CRYPT_INVALID_PRNGSIZE);
   ERR(CRYPT_ERROR_READPRNG);

   ERR(CRYPT_INVALID_CIPHER);
   ERR(CRYPT_INVALID_HASH);
   ERR(CRYPT_INVALID_PRNG);

   ERR(CRYPT_MEM);

   ERR(CRYPT_PK_TYPE_MISMATCH);
   ERR(CRYPT_PK_NOT_PRIVATE);

   ERR(CRYPT_INVALID_ARG);

   ERR(CRYPT_PK_INVALID_TYPE);
   ERR(CRYPT_PK_INVALID_SYSTEM);
   ERR(CRYPT_PK_DUP);
   ERR(CRYPT_PK_NOT_FOUND);
   ERR(CRYPT_PK_INVALID_SIZE);

   ERR(CRYPT_INVALID_PRIME_SIZE);
}   



int main(void)
{
#ifdef SONY_PS2
  TIMER_Init();
#endif

 register_all_algs();

 if ((errno = yarrow_start(&prng)) != CRYPT_OK) {
    printf("yarrow_start: %s\n", error_to_string(errno));
 }
 if ((errno = yarrow_add_entropy("hello", 5, &prng)) != CRYPT_OK) {
    printf("yarrow_add_entropy: %s\n", error_to_string(errno));
 }
 if ((errno = yarrow_ready(&prng)) != CRYPT_OK) {
    printf("yarrow_ready: %s\n", error_to_string(errno));
 }

 printf(crypt_build_settings);
 test_errs();


#ifdef HMAC
  printf("HMAC: %s\n", hmac_test() == CRYPT_OK ? "passed" : "failed");
#endif

 store_tests();
 cipher_tests();
 hash_tests();

 ecb_tests();
 cbc_tests();
 ctr_tests();
 ofb_tests();
 cfb_tests();

 rng_tests();
 //test_prime();

 kr_test();
 rsa_test();
 pad_test();
 ecc_tests();
 dh_tests();

 gf_tests();
 base64_test();

 time_ecb();
 time_hash();

#ifdef SONY_PS2
  TIMER_Shutdown();
#endif

 return 0;
}
