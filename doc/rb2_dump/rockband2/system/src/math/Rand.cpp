/*
    Compile unit: C:\rockband2\system\src\math\Rand.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8062DAB8 -> 0x8062DD5C
*/
// Range: 0x8062DAB8 -> 0x8062DB18
void * Rand::Rand(class Rand * const this /* r31 */) {}

// Range: 0x8062DB18 -> 0x8062DB6C
void Rand::Seed() {
    // Local variables
    unsigned int seed; // r4
    int i; // r7
    int rand_lo; // r0
    int rand_hi; // r0
}

// Range: 0x8062DB6C -> 0x8062DBFC
int Rand::Int(class Rand * const this /* r29 */, int low /* r30 */, int high /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8062DBFC -> 0x8062DC4C
float Rand::Float(float low /* f30 */, float high /* f31 */) {}

// Range: 0x8062DC4C -> 0x8062DC98
float Rand::Float() {
    // Local variables
    float answer; // f1
}

// Range: 0x8062DC98 -> 0x8062DD00
int Rand::Int() {
    // Local variables
    int ret; // r5
}

class Rand gRand; // size: 0x410, address: 0x8098A508
// Range: 0x8062DD00 -> 0x8062DD10
void SeedRand() {
    // References
    // -> class Rand gRand;
}

// Range: 0x8062DD10 -> 0x8062DD1C
int RandomInt() {
    // References
    // -> class Rand gRand;
}

// Range: 0x8062DD1C -> 0x8062DD34
int RandomInt(int low /* r0 */) {
    // References
    // -> class Rand gRand;
}

// Range: 0x8062DD34 -> 0x8062DD40
float RandomFloat() {
    // References
    // -> class Rand gRand;
}

// Range: 0x8062DD40 -> 0x8062DD4C
float RandomFloat() {
    // References
    // -> class Rand gRand;
}

// Range: 0x8062DD4C -> 0x8062DD5C
static void __sinit_\Rand_cpp() {
    // References
    // -> class Rand gRand;
}


