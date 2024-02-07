/*
    Compile unit: C:\rockband2\system\src\utl\Str.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x806216E4 -> 0x8062275C
*/
unsigned int npos; // size: 0x4, address: 0x80A57EE0
static char gEmpty; // size: 0x1, address: 0x80A55528
// Range: 0x806216E4 -> 0x80621730
void * String::String(class String * const this /* r31 */) {
    // References
    // -> static char gEmpty;
    // -> struct [anonymous] __vt__6String;
}

// Range: 0x80621730 -> 0x80621794
void * String::String(class String * const this /* r30 */, const char * str /* r31 */) {
    // References
    // -> static char gEmpty;
    // -> struct [anonymous] __vt__6String;
}

// Range: 0x80621794 -> 0x806217F8
void * String::String(class String * const this /* r30 */, class Symbol & sym /* r31 */) {
    // References
    // -> static char gEmpty;
    // -> struct [anonymous] __vt__6String;
}

// Range: 0x806217F8 -> 0x8062185C
void * String::String(class String * const this /* r30 */, const class String & str /* r31 */) {
    // References
    // -> static char gEmpty;
    // -> struct [anonymous] __vt__6String;
}

// Range: 0x8062185C -> 0x806218F0
void String::reserve(class String * const this /* r29 */, unsigned int cap /* r30 */) {
    // Local variables
    char * str; // r31
}

// Range: 0x806218F0 -> 0x80621964
void * String::~String(class String * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__6String;
}

// Range: 0x80621964 -> 0x80621968
void String::Print() {}

// Range: 0x80621968 -> 0x806219AC
class String String::__pl(class String * tstr /* r30 */, const char * var /* r31 */) {}

// Range: 0x806219AC -> 0x80621A3C
class String & String::__apl(class String * const this /* r29 */, const char * str /* r30 */) {
    // Local variables
    int len; // r0
}

// Range: 0x80621A3C -> 0x80621A44
class String & String::__apl() {}

// Range: 0x80621A44 -> 0x80621A4C
class String & String::__apl() {}

// Range: 0x80621A4C -> 0x80621ABC
class String & String::__apl(class String * const this /* r29 */, char c /* r30 */) {
    // Local variables
    int len; // r0
}

// Range: 0x80621ABC -> 0x80621B48
class String & String::__as(class String * const this /* r30 */, const char * str /* r31 */) {}

// Range: 0x80621B48 -> 0x80621B50
class String & String::__as() {}

// Range: 0x80621B50 -> 0x80621B9C
class String & String::__as(class String * const this /* r30 */, const class String & str /* r31 */) {}

// Range: 0x80621B9C -> 0x80621C10
char & String::__vc(class String * const this /* r30 */, unsigned int i /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80621C10 -> 0x80621CA8
char & String::rindex(class String * const this /* r30 */, int i /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80621CA8 -> 0x80621CF0
unsigned char String::__ne(const class String * const this /* r5 */) {}

// Range: 0x80621CF0 -> 0x80621D28
unsigned char String::__ne(const class String * const this /* r5 */) {}

// Range: 0x80621D28 -> 0x80621D6C
unsigned char String::__eq(const class String * const this /* r5 */) {}

// Range: 0x80621D6C -> 0x80621DA0
unsigned char String::__eq(const class String * const this /* r5 */) {}

// Range: 0x80621DA0 -> 0x80621DCC
unsigned char String::__lt() {}

// Range: 0x80621DCC -> 0x80621E10
void String::resize(class String * const this /* r30 */, unsigned int n /* r31 */) {}

// Range: 0x80621E10 -> 0x80621EC4
unsigned int String::find(const class String * const this /* r29 */, char c /* r30 */, unsigned int pos /* r31 */) {
    // Local variables
    char * d; // r6

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80621EC4 -> 0x80621ED0
unsigned int String::find() {}

// Range: 0x80621ED0 -> 0x80621ED8
unsigned int String::find() {}

// Range: 0x80621ED8 -> 0x80621F74
unsigned int String::find(const class String * const this /* r31 */, const char * str /* r29 */, unsigned int pos /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80621F74 -> 0x8062204C
unsigned int String::find_first_of(const class String * const this /* r29 */, const char * str /* r30 */, unsigned int pos /* r31 */) {
    // Local variables
    const char * c; // r7
    const char * d; // r8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8062204C -> 0x80622054
unsigned int String::find_first_of() {}

// Range: 0x80622054 -> 0x8062209C
unsigned int String::find_last_of() {}

// Range: 0x8062209C -> 0x80622134
unsigned int String::find_last_of(const class String * const this /* r29 */) {
    // Local variables
    int latest_pos; // r31
    const char * c; // r30
    int i; // r3
}

// Range: 0x80622134 -> 0x806221FC
unsigned int String::rfind(const class String * const this /* r28 */, const char * str /* r29 */) {
    // Local variables
    int pos; // r31
    const char * c; // r30
    int i; // r3
}

// Range: 0x806221FC -> 0x80622230
unsigned char String::contains() {}

// Range: 0x80622230 -> 0x80622348
class String String::substr(const class String * const this /* r28 */, unsigned int pos /* r29 */, unsigned int len /* r30 */) {
    // Local variables
    char buf[256]; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80622348 -> 0x806223A0
void String::ToLower() {
    // Local variables
    char * c; // r5

    // References
    // -> struct __locale _current_locale;
}

// Range: 0x806223A0 -> 0x806223F8
void String::ToUpper() {
    // Local variables
    char * c; // r5

    // References
    // -> struct __locale _current_locale;
}

// Range: 0x806223F8 -> 0x80622428
void String::ReplaceAll() {
    // Local variables
    char * c; // r6
}

// Range: 0x80622428 -> 0x8062244C
void String::swap() {
    // Local variables
    char * str; // r5
    unsigned int cap; // r6
}

// Range: 0x8062244C -> 0x806225B8
class String & String::replace(class String * const this /* r31 */, unsigned int pos /* r27 */, unsigned int len /* r28 */, const char * str /* r29 */) {
    // Local variables
    int newlen; // r30
    class String s; // r1+0x8
    char * c; // r4
    char * d; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806225B8 -> 0x806225C8
class String & String::erase() {}

// Range: 0x806225C8 -> 0x806225E4
class String & String::erase() {}

// Range: 0x806225E4 -> 0x806225EC
class String & String::erase() {}

// Range: 0x806225EC -> 0x806225F8
class String & String::insert() {}

// Range: 0x806225F8 -> 0x8062269C
unsigned char SearchReplace(const char * target /* r27 */, const char * search /* r28 */, const char * replace /* r29 */, char * out /* r30 */) {
    // Local variables
    unsigned char replaced; // r31
    const char * r; // r0
    int l; // r31
}

// Range: 0x8062269C -> 0x8062275C
unsigned char StrNCopy(char * dest /* r29 */, const char * src /* r30 */, int n /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x10
} __vt__6String; // size: 0x10, address: 0x8092F230

