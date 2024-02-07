/*
    Compile unit: C:\rockband2\system\src\os\Elf.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805AF460 -> 0x805B058C
*/
static char * gDemangleTypes[10][2]; // size: 0x50, address: 0x80984A40
static int gDemangleTypeNum; // size: 0x4, address: 0x80A549B8
// Range: 0x805AF460 -> 0x805AFD8C
static unsigned char DemangleIntoBuffer(const char * & src /* r28 */, char * & dst /* r29 */, unsigned char toplevel /* r30 */) {
    // Local variables
    int len; // r31
    const char * c; // r1+0x8
    int num_params; // r31
    int num_levels; // r31
    int num_params; // r31
    int ref; // r3
    int len; // r28
    char c; // r0

    // References
    // -> struct __locale _current_locale;
    // -> static char * gDemangleTypes[10][2];
    // -> static int gDemangleTypeNum;
}

// Range: 0x805AFD8C -> 0x805AFF80
static void DemangleString(char * str /* r31 */) {
    // Local variables
    char out[512]; // r1+0x10
    char * outp; // r1+0xC
    int name_length; // r30
    const char * c; // r1+0x8

    // References
    // -> static int gDemangleTypeNum;
}

struct Elf32_Ehdr {
    // total size: 0x34
    unsigned char e_ident[16]; // offset 0x0, size 0x10
    unsigned short e_type; // offset 0x10, size 0x2
    unsigned short e_machine; // offset 0x12, size 0x2
    unsigned int e_version; // offset 0x14, size 0x4
    unsigned int e_entry; // offset 0x18, size 0x4
    unsigned int e_phoff; // offset 0x1C, size 0x4
    unsigned int e_shoff; // offset 0x20, size 0x4
    unsigned int e_flags; // offset 0x24, size 0x4
    unsigned short e_ehsize; // offset 0x28, size 0x2
    unsigned short e_phentsize; // offset 0x2A, size 0x2
    unsigned short e_phnum; // offset 0x2C, size 0x2
    unsigned short e_shentsize; // offset 0x2E, size 0x2
    unsigned short e_shnum; // offset 0x30, size 0x2
    unsigned short e_shstrndx; // offset 0x32, size 0x2
};
struct Elf32_Shdr {
    // total size: 0x28
    unsigned int sh_name; // offset 0x0, size 0x4
    unsigned int sh_type; // offset 0x4, size 0x4
    unsigned int sh_flags; // offset 0x8, size 0x4
    unsigned int sh_addr; // offset 0xC, size 0x4
    unsigned int sh_offset; // offset 0x10, size 0x4
    unsigned int sh_size; // offset 0x14, size 0x4
    unsigned int sh_link; // offset 0x18, size 0x4
    unsigned int sh_info; // offset 0x1C, size 0x4
    unsigned int sh_addralign; // offset 0x20, size 0x4
    unsigned int sh_entsize; // offset 0x24, size 0x4
};
class Elf {
    // total size: 0x44
protected:
    class File * mFile; // offset 0x0, size 0x4
    struct Elf32_Ehdr mHeader; // offset 0x4, size 0x34
    struct Elf32_Shdr * mSections; // offset 0x38, size 0x4
    int mSyms; // offset 0x3C, size 0x4
    int mNumSyms; // offset 0x40, size 0x4
};
// Range: 0x805AFF80 -> 0x805B0054
void Elf::GetString(class Elf * const this /* r29 */, char * buffer /* r30 */, int len /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

struct Elf32_Sym {
    // total size: 0x10
    unsigned int st_name; // offset 0x0, size 0x4
    unsigned int st_value; // offset 0x4, size 0x4
    unsigned int st_size; // offset 0x8, size 0x4
    unsigned char st_info; // offset 0xC, size 0x1
    unsigned char st_other; // offset 0xD, size 0x1
    unsigned short st_shndx; // offset 0xE, size 0x2
};
// Range: 0x805B0054 -> 0x805B0160
void Elf::GetFunction(class Elf * const this /* r27 */, char * buffer /* r31 */, int len /* r28 */, unsigned int addr /* r29 */) {
    // Local variables
    int i; // r30
    struct Elf32_Sym sym; // r1+0x8
}

static int _x; // size: 0x4, address: 0x80A549BC
// Range: 0x805B0160 -> 0x805B0338
void Elf::OpenFile(class Elf * const this /* r25 */) {
    // Local variables
    class String name; // r1+0x14
    const char * cdrom0; // r29
    const char * host0; // r28
    unsigned long pos; // r27
    unsigned char onHost; // r26
    unsigned char usingCD; // r27

    // References
    // -> class Debug TheDebug;
    // -> static int _x;
    // -> unsigned int npos;
}

// Range: 0x805B0338 -> 0x805B0510
void * Elf::Elf(class Elf * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805B0510 -> 0x805B058C
void * Elf::~Elf(class Elf * const this /* r30 */) {}


