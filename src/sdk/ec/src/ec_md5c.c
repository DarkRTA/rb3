/* OpenSSL - crypto/md5/md5_dgst.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

// #include <stdio.h>
#include <ec/internal/md5.h>
#include <ec/internal/md5_locl.h>
// #include <openssl/opensslv.h>

// const char MD5_version[] = "MD5" OPENSSL_VERSION_PTEXT;

/* Implemented from RFC1321 The MD5 Message-Digest Algorithm
 */

static unsigned char PADDING[0x40] = { 0x80 };

#define INIT_DATA_A (HASH_LONG)0x67452301L
#define INIT_DATA_B (HASH_LONG)0xefcdab89L
#define INIT_DATA_C (HASH_LONG)0x98badcfeL
#define INIT_DATA_D (HASH_LONG)0x10325476L

void MD5_Init(MD5_CTX *c) {
    c->Nh = 0;
    c->Nl = 0;
    c->A = INIT_DATA_A;
    c->B = INIT_DATA_B;
    c->C = INIT_DATA_C;
    c->D = INIT_DATA_D;
}

static void MD5Transform(MD5_CTX *c, const void* data);
static void Encode(void *dest, const void *src, size_t len);
static void MD5_memcpy(void *dest, const void *src, size_t len);
static void MD5_memset(void *dest, int value, size_t len);

void HASH_UPDATE(HASH_CTX *c, const void *data_, size_t len) {
    const unsigned char *data = data_;
    unsigned char *p;
    HASH_LONG nl;
    HASH_LONG l;
    size_t n;

    nl = c->Nl;
    l = nl + (((HASH_LONG)len) << 3);
    c->Nl = l;

    nl = nl >> 3 & 0x3F;
    /* 95-05-24 eay Fixed a bug with the overflow handling, thanks to
     * Wei Dai <weidai@eskimo.com> for pointing it out. */
    if (l < (((HASH_LONG)len) << 3)) /* overflow */
        c->Nh++;

    n = 0x40 - nl;
    c->Nh += (HASH_LONG)(len >> 29); /* might cause compiler warning on 16-bit */

    if (len >= n) {
        MD5_memcpy(c->data + nl, data, n);
        MD5Transform(c, c->data);
        for (; n + 0x3F < len; n += 0x40) {
            MD5Transform(c, data + n);
        }
        nl = 0;
    } else {
        n = 0;
    }

    MD5_memcpy(c->data + nl, data + n, len - n);
}

// void HASH_TRANSFORM(HASH_CTX *c, const unsigned char *data) {
//     HASH_BLOCK_DATA_ORDER(c, data, 1);
// }

void HASH_FINAL(unsigned char *md, HASH_CTX *c) {
    unsigned char dest[sizeof(c->Nl) * 2];
    HASH_LONG l;

    Encode(dest, &c->Nl, sizeof(c->Nl) * 2);
    l = c->Nl >> 3 & 0x3F;

    MD5_Update(c, PADDING, l < 0x38 ? 0x38 - l : 0x78 - l);
    MD5_Update(c, dest, sizeof(dest));
    Encode(md, c, 0x10);
    MD5_memset(c, 0, sizeof(*c));
}

static void MD5Transform(MD5_CTX *c, const void *data_) {
    const unsigned char *cdata = data_;
    const HASH_LONG *data = data_;
    register unsigned MD32_REG_T A, B, C, D, l;
    MD5_LONG XX[MD5_LBLOCK];

    A = c->A;
    B = c->B;
    C = c->C;
    D = c->D;

    for (int i = 0; i < sizeof(XX) / sizeof(*XX); i++) {
        HOST_c2l(cdata, XX[i]);
    }

    /* Round 0 */
    R0(A, B, C, D, XX[0], 7, 0xd76aa478L);
    HOST_c2l(data, l);
    XX[2] = l;
    R0(D, A, B, C, XX[1], 12, 0xe8c7b756L);
    HOST_c2l(data, l);
    XX[3] = l;
    R0(C, D, A, B, XX[2], 17, 0x242070dbL);
    HOST_c2l(data, l);
    XX[4] = l;
    R0(B, C, D, A, XX[3], 22, 0xc1bdceeeL);
    HOST_c2l(data, l);
    XX[5] = l;
    R0(A, B, C, D, XX[4], 7, 0xf57c0fafL);
    HOST_c2l(data, l);
    XX[6] = l;
    R0(D, A, B, C, XX[5], 12, 0x4787c62aL);
    HOST_c2l(data, l);
    XX[7] = l;
    R0(C, D, A, B, XX[6], 17, 0xa8304613L);
    HOST_c2l(data, l);
    XX[8] = l;
    R0(B, C, D, A, XX[7], 22, 0xfd469501L);
    HOST_c2l(data, l);
    XX[9] = l;
    R0(A, B, C, D, XX[8], 7, 0x698098d8L);
    HOST_c2l(data, l);
    XX[10] = l;
    R0(D, A, B, C, XX[9], 12, 0x8b44f7afL);
    HOST_c2l(data, l);
    XX[11] = l;
    R0(C, D, A, B, XX[10], 17, 0xffff5bb1L);
    HOST_c2l(data, l);
    XX[12] = l;
    R0(B, C, D, A, XX[11], 22, 0x895cd7beL);
    HOST_c2l(data, l);
    XX[13] = l;
    R0(A, B, C, D, XX[12], 7, 0x6b901122L);
    HOST_c2l(data, l);
    XX[14] = l;
    R0(D, A, B, C, XX[13], 12, 0xfd987193L);
    HOST_c2l(data, l);
    XX[15] = l;
    R0(C, D, A, B, XX[14], 17, 0xa679438eL);
    R0(B, C, D, A, XX[15], 22, 0x49b40821L);
    /* Round 1 */
    R1(A, B, C, D, XX[1], 5, 0xf61e2562L);
    R1(D, A, B, C, XX[6], 9, 0xc040b340L);
    R1(C, D, A, B, XX[11], 14, 0x265e5a51L);
    R1(B, C, D, A, XX[0], 20, 0xe9b6c7aaL);
    R1(A, B, C, D, XX[5], 5, 0xd62f105dL);
    R1(D, A, B, C, XX[10], 9, 0x02441453L);
    R1(C, D, A, B, XX[15], 14, 0xd8a1e681L);
    R1(B, C, D, A, XX[4], 20, 0xe7d3fbc8L);
    R1(A, B, C, D, XX[9], 5, 0x21e1cde6L);
    R1(D, A, B, C, XX[14], 9, 0xc33707d6L);
    R1(C, D, A, B, XX[3], 14, 0xf4d50d87L);
    R1(B, C, D, A, XX[8], 20, 0x455a14edL);
    R1(A, B, C, D, XX[13], 5, 0xa9e3e905L);
    R1(D, A, B, C, XX[2], 9, 0xfcefa3f8L);
    R1(C, D, A, B, XX[7], 14, 0x676f02d9L);
    R1(B, C, D, A, XX[12], 20, 0x8d2a4c8aL);
    /* Round 2 */
    R2(A, B, C, D, XX[5], 4, 0xfffa3942L);
    R2(D, A, B, C, XX[8], 11, 0x8771f681L);
    R2(C, D, A, B, XX[11], 16, 0x6d9d6122L);
    R2(B, C, D, A, XX[14], 23, 0xfde5380cL);
    R2(A, B, C, D, XX[1], 4, 0xa4beea44L);
    R2(D, A, B, C, XX[4], 11, 0x4bdecfa9L);
    R2(C, D, A, B, XX[7], 16, 0xf6bb4b60L);
    R2(B, C, D, A, XX[10], 23, 0xbebfbc70L);
    R2(A, B, C, D, XX[13], 4, 0x289b7ec6L);
    R2(D, A, B, C, XX[0], 11, 0xeaa127faL);
    R2(C, D, A, B, XX[3], 16, 0xd4ef3085L);
    R2(B, C, D, A, XX[6], 23, 0x04881d05L);
    R2(A, B, C, D, XX[9], 4, 0xd9d4d039L);
    R2(D, A, B, C, XX[12], 11, 0xe6db99e5L);
    R2(C, D, A, B, XX[15], 16, 0x1fa27cf8L);
    R2(B, C, D, A, XX[2], 23, 0xc4ac5665L);
    /* Round 3 */
    R3(A, B, C, D, XX[0], 6, 0xf4292244L);
    R3(D, A, B, C, XX[7], 10, 0x432aff97L);
    R3(C, D, A, B, XX[14], 15, 0xab9423a7L);
    R3(B, C, D, A, XX[5], 21, 0xfc93a039L);
    R3(A, B, C, D, XX[12], 6, 0x655b59c3L);
    R3(D, A, B, C, XX[3], 10, 0x8f0ccc92L);
    R3(C, D, A, B, XX[10], 15, 0xffeff47dL);
    R3(B, C, D, A, XX[1], 21, 0x85845dd1L);
    R3(A, B, C, D, XX[8], 6, 0x6fa87e4fL);
    R3(D, A, B, C, XX[15], 10, 0xfe2ce6e0L);
    R3(C, D, A, B, XX[6], 15, 0xa3014314L);
    R3(B, C, D, A, XX[13], 21, 0x4e0811a1L);
    R3(A, B, C, D, XX[4], 6, 0xf7537e82L);
    R3(D, A, B, C, XX[11], 10, 0xbd3af235L);
    R3(C, D, A, B, XX[2], 15, 0x2ad7d2bbL);
    R3(B, C, D, A, XX[9], 21, 0xeb86d391L);

    c->A += A;
    c->B += B;
    c->C += C;
    c->D += D;

    MD5_memset(XX, 0, sizeof(XX));
}

static void Encode(void *dest, const void *src, size_t len) {
    unsigned char *d = dest;
    const volatile HASH_LONG *s = src;

    int iSrc = 0;
    for (int count = 0; count < (len + 3) / sizeof(HASH_LONG); count++) {
        // HOST_l2c(s[count], d);

        d[iSrc + 0] = s[count] >> 0;
        d[iSrc + 1] = s[count] >> 8;
        d[iSrc + 2] = s[count] >> 16;
        d[iSrc + 3] = s[count] >> 24;
        iSrc += 4;
    }
}

static void MD5_memcpy(void *dest, const void *src, size_t len) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    size_t i = 0;
    for (; i < len; i++) {
        *d++ = *s++;
    }
}

static void MD5_memset(void *dest, int value, size_t len) {
    unsigned char *d = dest;
    size_t i = 0;
    for (; i < len; i++) {
        *d++ = value;
    }
}
