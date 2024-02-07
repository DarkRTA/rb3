/*
    Compile unit: C:\rockband2\system\src\net\NetMessage.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80527E14 -> 0x80528108
*/
class NetMessageFactory TheNetMessageFactory; // size: 0xC, address: 0x80981FE4
// Range: 0x80527E14 -> 0x80527F84
void NetMessageFactory::RegisterNetMessage(class NetMessageFactory * const this /* r31 */, class String & type /* r27 */, class NetMessage * (* creator)() /* r28 */) {
    // Local variables
    int n; // r29
    struct TypeCreatorPair newPair; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80527F84 -> 0x80528048
unsigned char NetMessageFactory::GetNetMessageByteCode(const class NetMessageFactory * const this /* r29 */, class String & type /* r30 */) {
    // Local variables
    int n; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80528048 -> 0x805280DC
class NetMessage * NetMessageFactory::CreateNetMessage(class NetMessageFactory * const this /* r30 */, unsigned char byteCode /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ217NetMessageFactory15TypeCreatorPair; // size: 0x8, address: 0x80905948
// Range: 0x805280DC -> 0x80528108
static void __sinit_\NetMessage_cpp() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}


