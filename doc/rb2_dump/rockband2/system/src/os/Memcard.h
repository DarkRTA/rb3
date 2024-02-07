/*
    Compile unit: C:\rockband2\system\src\os\Memcard.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805BEEF8 -> 0x805BF138
*/
// Range: 0x805BEEF8 -> 0x805BEF14
void Memcard::Init() {
    // References
    // -> class ObjectDir * sMainDir;
}

// Range: 0x805BEF14 -> 0x805BEFCC
void Memcard::DestroyContainer(class MCContainer * pContainer /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805BEFCC -> 0x805BF00C
void * MCContainer::~MCContainer(class MCContainer * const this /* r31 */) {}

// Range: 0x805BF00C -> 0x805BF0BC
void MCContainer::DestroyMCFile(class MCFile * pFile /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805BF0BC -> 0x805BF0C4
class String MCContainer::BuildPath() {}

// Range: 0x805BF0C4 -> 0x805BF0CC
wchar_t * Memcard::GetDisplayName() {}

// Range: 0x805BF0CC -> 0x805BF0D4
char * Memcard::GetContainerName() {}

// Range: 0x805BF0D4 -> 0x805BF0D8
void Memcard::SetContainerDisplayName() {}

// Range: 0x805BF0D8 -> 0x805BF0DC
void Memcard::SetContainerName() {}

// Range: 0x805BF0DC -> 0x805BF138
void * Memcard::~Memcard(class Memcard * const this /* r30 */) {}


