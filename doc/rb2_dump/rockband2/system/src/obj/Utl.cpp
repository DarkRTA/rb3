/*
    Compile unit: C:\rockband2\system\src\obj\Utl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805FCEBC -> 0x805FF2EC
*/
static class DataArray * objects; // size: 0x4, address: 0x80A55360
static class Symbol initSym; // size: 0x4, address: 0x80A55368
// Range: 0x805FCEBC -> 0x805FCFC4
void InitObject(class Object * o /* r31 */) {
    // Local variables
    class DataArray * init; // r4

    // References
    // -> static class Symbol initSym;
    // -> static class DataArray * objects;
}

// Range: 0x805FCFC4 -> 0x805FCFE8
char * PathName() {
    // Local variables
    class Object * obj; // r0
}

// Range: 0x805FCFE8 -> 0x805FD134
static void RecurseSuperClasses(class vector & classes /* r28 */) {
    // Local variables
    class DataArray * da; // r31
    class DataArray * parents; // r30
    int i; // r29
    class Symbol parentnm; // r1+0x28
}

// Range: 0x805FD134 -> 0x805FD1D0
void ListSuperClasses(class vector & classes /* r31 */) {}

// Range: 0x805FD1D0 -> 0x805FD2E8
static unsigned char RecurseSuperClassesSearch(class Symbol & searchClass /* r29 */) {
    // Local variables
    class DataArray * da; // r31
    class DataArray * parents; // r31
    int i; // r30
    class Symbol parentnm; // r1+0x24
}

// Range: 0x805FD2E8 -> 0x805FD398
unsigned char IsASubclass(class Symbol & child /* r29 */, class Symbol & parent /* r30 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x805FD398 -> 0x805FD48C
void ReplaceObject(class Object * from /* r26 */, class Object * to /* r27 */, unsigned char deleteFrom /* r28 */, unsigned char setProxyFile /* r29 */) {}

static class Symbol objects; // size: 0x4, address: 0x80A55370
static class Symbol types; // size: 0x4, address: 0x80A55378
static class Symbol editor; // size: 0x4, address: 0x80A55380
// Range: 0x805FD48C -> 0x805FDD18
void CopyTypeProperties(class Object * from /* r28 */, class Object * to /* r29 */) {
    // Local variables
    class list fromProps; // r1+0x180
    class list toProps; // r1+0x178
    class list fromArrayProps; // r1+0x170
    class list toArrayProps; // r1+0x168
    class DataArray * fromTypeArr; // r30
    class DataArray * fromTypeEditor; // r0
    struct _List_iterator fromIt; // r1+0xE8
    struct _List_iterator toIt; // r1+0xE4
    class Symbol prop; // r1+0xE0
    const class DataNode * fromVal; // r26
    enum DataType fromType; // r0
    enum DataType toType; // r0
    class Object * objProp; // r0
    struct _List_iterator fromIt; // r1+0xDC
    struct _List_iterator toIt; // r1+0xD8
    class Symbol prop; // r1+0xD4
    class DataArray * fromValArr; // r0
    class DataArrayPtr propIdx; // r1+0x160
    class DataArrayPtr propTag; // r1+0x158
    int ii; // r26

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class Debug TheDebug;
    // -> static class Symbol editor;
    // -> static class Symbol types;
    // -> static class Symbol objects;
    // -> const char * gNullStr;
}

// Range: 0x805FDD18 -> 0x805FDE54
static void MergeObjects(class Object * from /* r26 */, class ObjectDir * fromDir /* r27 */, class Object * to /* r28 */, class ObjectDir * toDir /* r29 */, class MergeFilter & filter /* r30 */, unsigned char subdirs /* r31 */) {
    // Local variables
    enum Action action; // r0
}

// Range: 0x805FDE54 -> 0x805FE354
void MergeDirs(class ObjectDir * fromDir /* r26 */, class ObjectDir * toDir /* r27 */, class MergeFilter & filter /* r28 */, unsigned char subdirs /* r29 */) {
    // Local variables
    int i; // r30
    struct _List_iterator ref; // r1+0x30
    class Object * o; // r0
    class ObjDirItr i; // r1+0x48
    class Object * to; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805FE354 -> 0x805FE3D0
void ReserveToFit(class ObjectDir * src /* r27 */, class ObjectDir * dst /* r28 */, int extraObjects /* r29 */) {
    // Local variables
    int stringSize; // r30
    int hashSize; // r0
}

// Range: 0x805FE3D0 -> 0x805FE47C
int SubDirStringUsed(class ObjectDir * dir /* r29 */) {
    // Local variables
    int used; // r31
    const class vector & s; // r0
    const class ObjDirPtr * it; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805FE47C -> 0x805FE520
int SubDirHashUsed(class ObjectDir * dir /* r29 */) {
    // Local variables
    int used; // r31
    const class vector & s; // r0
    const class ObjDirPtr * it; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805FE520 -> 0x805FE5FC
class Object * CopyObject(class Object * from /* r27 */, class Object * to /* r28 */, unsigned char setProxyFile /* r29 */) {
    // Local variables
    class ObjectDir * d; // r29

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
}

// Range: 0x805FE5FC -> 0x805FE6A4
class Object * CloneObject(class Object * from /* r30 */, unsigned char instance /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805FE6A4 -> 0x805FE7E0
char * NextName(const char * old_name /* r28 */, class ObjectDir * dir /* r27 */) {
    // Local variables
    char name[128]; // r1+0x8
    const char * base; // r31
    const char * ext; // r30
    char * num; // r29
    int n; // r28
}

// Range: 0x805FE7E0 -> 0x805FE854
static void EditorBlockProps(class DataArray * editDefn /* r29 */, class list & props /* r30 */, class list * arrayProps /* r31 */) {
    // Local variables
    class DataArray * ed; // r0
}

static class Symbol objects; // size: 0x4, address: 0x80A55388
// Range: 0x805FE854 -> 0x805FEA30
void ListProperties(class list & props /* r30 */, class Symbol & classnm /* r27 */, class Symbol & type /* r28 */, class list * arrayProps /* r31 */) {
    // Local variables
    class DataArray * classdef; // r29
    class DataArray * da; // r0
    class vector classes; // r1+0x38
    class Symbol * i; // r29

    // References
    // -> const char * gNullStr;
    // -> static class Symbol objects;
}

// Range: 0x805FEA30 -> 0x805FEB4C
static int GetPropSize(class Object * o /* r26 */, class DataArray * prop /* r27 */, int nodes /* r28 */) {
    // Local variables
    class DataArrayPtr da; // r1+0x8
    int i; // r29
    int size; // r29

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x805FEB4C -> 0x805FEC00
unsigned char IsPropPathValid(class Object * o /* r28 */, class DataArray * prop /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x805FEC00 -> 0x805FED58
unsigned char PropPathCompare(class DataArray * a /* r27 */, class DataArray * b /* r28 */) {
    // Local variables
    int i; // r29
    enum DataType t; // r0
}

// Range: 0x805FED58 -> 0x805FEDBC
class DataNode * GetPropertyVal(class Object * o /* r29 */, class DataArray * prop /* r30 */, unsigned char fail /* r31 */) {}

// Range: 0x805FEDBC -> 0x805FF164
void TestDuplicateObjNames(class ObjectDir * o /* r30 */) {
    // Local variables
    class ObjDirItr it; // r1+0x18
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805FF164 -> 0x805FF2EC
void CheckForDuplicateTypeHandlers(class Object * o /* r29 */) {
    // Local variables
    class DataArray * t; // r31
    class list handlers; // r1+0x40
    int i; // r30
    class DataNode & n; // r0
    class Symbol handler; // r1+0x2C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std29_Rb_tree_node<PQ23Hmx6Object>; // size: 0x8, address: 0x8092ADF8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std62_Rb_tree_node<Q211stlpmtx_std30pair<CP6ObjRef,12DataArrayPtr>>; // size: 0x8, address: 0x8092AE50
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std60_Rb_tree_node<Q211stlpmtx_std28pair<CP9ObjectDir,8FilePath>>; // size: 0x8, address: 0x8092AEA8

