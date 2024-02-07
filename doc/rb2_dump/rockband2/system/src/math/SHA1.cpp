/*
    Compile unit: C:\rockband2\system\src\math\SHA1.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80626F28 -> 0x80628BBC
*/
// Range: 0x80626F28 -> 0x80626F60
void * CSHA1::CSHA1(class CSHA1 * const this /* r31 */) {}

// Range: 0x80626F60 -> 0x80626FB4
void * CSHA1::~CSHA1(class CSHA1 * const this /* r30 */) {}

// Range: 0x80626FB4 -> 0x80627000
void CSHA1::Reset() {}

// Range: 0x80627000 -> 0x80628974
void CSHA1::Transform(class CSHA1 * const this /* r25 */, unsigned long * pState /* r26 */) {
    // Local variables
    unsigned long a; // r31
    unsigned long b; // r30
    unsigned long c; // r29
    unsigned long d; // r28
    unsigned long e; // r27
}

// Range: 0x80628974 -> 0x80628A70
void CSHA1::Update(class CSHA1 * const this /* r28 */, const unsigned char * pData /* r29 */, unsigned long uLen /* r30 */) {
    // Local variables
    unsigned long i; // r31
    unsigned long j; // r6
}

// Range: 0x80628A70 -> 0x80628BA8
void CSHA1::Final(class CSHA1 * const this /* r31 */) {
    // Local variables
    unsigned long i; // r5
    unsigned char finalcount[8]; // r1+0x8
}

// Range: 0x80628BA8 -> 0x80628BBC
void CSHA1::GetHash(const class CSHA1 * const this /* r5 */) {}


