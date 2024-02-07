/*
    Compile unit: C:\rockband2\system\src\obj\TypeProps.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805FBC48 -> 0x805FCEB4
*/
// Range: 0x805FBC48 -> 0x805FBDCC
class DataArray * TypeProps::GetArray(class TypeProps * const this /* r27 */, class Symbol & prop /* r28 */, class DataArray * typeDef /* r29 */) {
    // Local variables
    class DataNode * n; // r0
    class DataArray * a; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805FBDCC -> 0x805FBE78
void TypeProps::SetArrayValue(class TypeProps * const this /* r29 */, int i /* r31 */, const class DataNode & val /* r30 */) {
    // Local variables
    class DataArray * a; // r0
    class DataNode & n; // r31
    class Object * o; // r3
    class Object * o; // r3
}

// Range: 0x805FBE78 -> 0x805FBF00
void TypeProps::RemoveArrayValue(class TypeProps * const this /* r29 */, int i /* r30 */) {
    // Local variables
    class DataArray * a; // r31
    class DataNode & n; // r0
    class Object * o; // r3
}

// Range: 0x805FBF00 -> 0x805FBF80
void TypeProps::InsertArrayValue(class TypeProps * const this /* r29 */, int i /* r30 */, const class DataNode & val /* r31 */) {
    // Local variables
    class DataArray * a; // r0
    class Object * o; // r3
}

// Range: 0x805FBF80 -> 0x805FC170
void TypeProps::SetKeyValue(class TypeProps * const this /* r30 */, class Symbol & key /* r27 */, const class DataNode & value /* r31 */) {
    // Local variables
    class Object * o; // r3
    int i; // r28
    class DataNode & n; // r28
    class Object * o; // r3
}

// Range: 0x805FC170 -> 0x805FC23C
class DataNode * TypeProps::KeyValue(class TypeProps * const this /* r28 */, class Symbol & key /* r29 */, unsigned char fail /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

static class Symbol proxy_save; // size: 0x4, address: 0x80A55354
// Range: 0x805FC23C -> 0x805FC648
void TypeProps::Save(class TypeProps * const this /* r25 */, class BinStream & d /* r26 */) {
    // Local variables
    class Object * o; // r27
    class DataArray * typeDef; // r28
    int i; // r29
    class DataArray * prop; // r30
    class DataArray * typeDef; // r30
    class DataArray * proxyMap; // r29
    int idx; // r28
    int i; // r27
    class Symbol prop; // r1+0x30
    class DataArray * def; // r23

    // References
    // -> const char * kAssertStr;
    // -> static class Symbol proxy_save;
    // -> class Debug TheDebug;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class LoadMgr TheLoadMgr;
}

static class Symbol proxy_save; // size: 0x4, address: 0x80A5535C
// Range: 0x805FC648 -> 0x805FC99C
void TypeProps::Load(class TypeProps * const this /* r24 */, class BinStream & d /* r23 */, unsigned char oldProxy /* r25 */) {
    // Local variables
    class DataArray * typeDef; // r30
    class Object * old; // r29
    class DataArray * proxyMap; // r28
    int size; // r27
    int i; // r26
    class Symbol s; // r1+0x34
    class DataArray * prop; // r23
    int i; // r23
    class DataArray * prop; // r26

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol proxy_save;
    // -> unsigned char gLoadingProxyFromDisk;
}

// Range: 0x805FC99C -> 0x805FCA4C
void TypeProps::ReplaceObject(class TypeProps * const this /* r29 */, class DataNode & n /* r30 */, class Object * to /* r31 */) {
    // Local variables
    class Object * o; // r3
}

// Range: 0x805FCA4C -> 0x805FCB28
void TypeProps::Replace(class TypeProps * const this /* r26 */, class Object * from /* r27 */, class Object * to /* r28 */) {
    // Local variables
    int i; // r31
    class DataNode & n; // r4
    class DataArray * a; // r30
    int j; // r29
    class DataNode & nj; // r4
}

// Range: 0x805FCB28 -> 0x805FCC0C
void TypeProps::ReleaseObjects(class TypeProps * const this /* r28 */) {
    // Local variables
    int i; // r31
    class DataNode & n; // r0
    class Object * o; // r3
    class DataArray * a; // r30
    int j; // r29
    class DataNode & nj; // r0
    class Object * o; // r3
}

// Range: 0x805FCC0C -> 0x805FCCF0
void TypeProps::AddRefObjects(class TypeProps * const this /* r28 */) {
    // Local variables
    int i; // r31
    class DataNode & n; // r0
    class Object * o; // r3
    class DataArray * a; // r30
    int j; // r29
    class DataNode & nj; // r0
    class Object * o; // r3
}

// Range: 0x805FCCF0 -> 0x805FCD50
class TypeProps & TypeProps::__as(class TypeProps * const this /* r30 */, const class TypeProps & prop /* r31 */) {}

// Range: 0x805FCD50 -> 0x805FCE54
void TypeProps::ClearKeyValue(class TypeProps * const this /* r29 */, class Symbol & key /* r30 */) {
    // Local variables
    int i; // r31
    class DataNode & n; // r0
    class Object * o; // r3
}

// Range: 0x805FCE54 -> 0x805FCEB4
void TypeProps::ClearAll(class TypeProps * const this /* r31 */) {}

struct {
    // total size: 0x18
} __vt__9TypeProps; // size: 0x18, address: 0x8092AA40
struct {
    // total size: 0x8
} __RTTI__9TypeProps; // size: 0x8, address: 0x8092AA70

