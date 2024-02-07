/*
    Compile unit: C:\rockband2\system\src\beatmatch\PhraseCatcher.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802F4BA4 -> 0x802F4D8C
*/
// Range: 0x802F4BA4 -> 0x802F4BC4
void * PhraseCatcher::PhraseCatcher() {}

// Range: 0x802F4BC4 -> 0x802F4BCC
void PhraseCatcher::Start() {}

// Range: 0x802F4BCC -> 0x802F4BD0
void PhraseCatcher::Poll() {}

// Range: 0x802F4BD0 -> 0x802F4BDC
void PhraseCatcher::Jump() {}

// Range: 0x802F4BDC -> 0x802F4C04
void PhraseCatcher::Hit() {}

// Range: 0x802F4C04 -> 0x802F4C2C
void PhraseCatcher::Miss() {}

// Range: 0x802F4C2C -> 0x802F4C54
void PhraseCatcher::Pass() {}

// Range: 0x802F4C54 -> 0x802F4CE0
void PhraseCatcher::ComputeNewPhrase(class PhraseCatcher * const this /* r31 */) {
    // Local variables
    unsigned char ok; // r0
}

// Range: 0x802F4CE0 -> 0x802F4D28
void PhraseCatcher::FailCurrentPhrase(class PhraseCatcher * const this /* r31 */) {}

// Range: 0x802F4D28 -> 0x802F4D8C
void PhraseCatcher::Succeed(class PhraseCatcher * const this /* r31 */) {
    // Local variables
    struct PhraseInfo captured_phrase; // r1+0x8
}


