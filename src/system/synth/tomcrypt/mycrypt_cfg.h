/* This is the build config file.
 *
 * With this you can setup what to inlcude/exclude automatically during any build.  Just comment
 * out the line that #define's the word for the thing you want to remove.  phew!
 */

#ifndef MYCRYPT_CFG_H
#define MYCRYPT_CFG_H

// "LibTomCrypt 0.70\n\n
// Endianess: neutral\n
#define ENDIAN_NEUTRAL
// Clean stack: disabled\n
// Ciphers built-in:\n   Rijndael\n\n
#define RIJNDAEL
// Hashes built-in:\n   MD4\n\n
#define MD4
// Block Chaining Modes:\n   M_CTR\n\n
#define CTR
// PRNG:\n\n
// PK Algs:\n\n
// Compiler:\n\n
// Various others:  HMAC  SMALL_PRIME_TAB \n\n\n\n"
#define HMAC
#define SMALL_PRIME_TAB

/* you can change how memory allocation works ... */
extern void *XMALLOC(size_t n);
extern void *XCALLOC(size_t n, size_t s);
extern void XFREE(void *p);

/* change the clock function too */
extern clock_t XCLOCK(void);

/* type of argument checking, 0=default, 1=fatal and 2=none */
#define ARGTYPE  0

/* Controls endianess and size of registers.  Leave uncommented to get platform neutral [slower] code */
/* detect x86-32 machines somewhat */
#if (defined(_MSC_VER) && defined(WIN32))  || (defined(__GNUC__) && (defined(__DJGPP__) || defined(__CYGWIN__) || defined(__MINGW32__)))
   #define ENDIAN_LITTLE
   #define ENDIAN_32BITWORD
#endif

/* detects MIPS R5900 processors (PS2) */
#if (defined(__R5900) || defined(R5900) || defined(__R5900__)) && (defined(_mips) || defined(__mips__) || defined(mips))
   #define ENDIAN_LITTLE
   #define ENDIAN_64BITWORD
#endif

/* #define ENDIAN_LITTLE */
/* #define ENDIAN_BIG */

/* #define ENDIAN_32BITWORD */
/* #define ENDIAN_64BITWORD */

#if (defined(ENDIAN_BIG) || defined(ENDIAN_LITTLE)) && !(defined(ENDIAN_32BITWORD) || defined(ENDIAN_64BITWORD))
    #error You must specify a word size as well as endianess in mycrypt_cfg.h
#endif

#if !(defined(ENDIAN_BIG) || defined(ENDIAN_LITTLE))
   #define ENDIAN_NEUTRAL
#endif

#ifdef SHA384
   #ifndef SHA512
      #error The SHA384 hash requires SHA512 to be defined!
   #endif
#endif

#ifdef YARROW
   #ifndef CTR
      #error YARROW Requires CTR mode
   #endif
#endif

/* packet code */
#if defined(MRSA) || defined(MDH) || defined(MECC)
    #define PACKET

    /* size of a packet header in bytes */
    #define PACKET_SIZE            8

    /* Section tags */
    #define PACKET_SECT_RSA        0
    #define PACKET_SECT_DH         1
    #define PACKET_SECT_ECC        2

    /* Subsection Tags for the first three sections */
    #define PACKET_SUB_KEY         0
    #define PACKET_SUB_ENCRYPTED   1
    #define PACKET_SUB_SIGNED      2
    #define PACKET_SUB_ENC_KEY     3
#endif

/* Diffie-Hellman key settings you can omit ones you don't want to save space */
#ifdef MDH

#define DH512
#define DH768
#define DH1024
#define DH1280
#define DH1536
#define DH1792
#define DH2048
#define DH2560
#define DH3072
#define DH4096

#endif /* MDH */

/* ECC Key settings */
#ifdef MECC 

#define ECC160
#define ECC192
#define ECC224
#define ECC256
#define ECC384
#define ECC521

#endif /* MECC */

#ifdef MPI
   #include "mpi.h"
#else
   #ifdef MRSA
      #error RSA requires the big int library 
   #endif
   #ifdef MECC
      #error ECC requires the big int library 
   #endif
   #ifdef MDH
      #error DH requires the big int library 
   #endif
#endif /* MPI */

#endif /* MYCRYPT_CFG_H */
