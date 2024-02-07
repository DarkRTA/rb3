/*
    Compile unit: C:\rockband2\system\src\obj\DataUtl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805DF840 -> 0x805E01A8
*/
class Symbol name; // size: 0x4, address: 0x80A54E84
class map gMacroTable; // size: 0x18, address: 0x80988FC8
class ObjectDir * gDataDir; // size: 0x4, address: 0x80A54E88
class Object * gDataThis; // size: 0x4, address: 0x80A54E8C
static unsigned char gDataMacroWarning; // size: 0x1, address: 0x80A479F0
struct VarStack {
    // total size: 0xC
    class DataNode * var; // offset 0x0, size 0x4
    class DataNode value; // offset 0x4, size 0x8
};
static struct VarStack gVarStack[100]; // size: 0x4B0, address: 0x80988FF0
static struct VarStack * gVarStackPtr; // size: 0x4, address: 0x80A479F4
// Range: 0x805DF840 -> 0x805DF894
static class Loader * DataFactory(const class FilePath & file /* r30 */, enum LoaderPos pos /* r31 */) {}

// Range: 0x805DF894 -> 0x805DF920
void DataInit() {
    // References
    // -> static unsigned char gDataMacroWarning;
    // -> class Symbol name;
    // -> class LoadMgr TheLoadMgr;
}

class TextFile : public Object, public TextStream {
    // total size: 0x30
    class File * mFile; // offset 0x2C, size 0x4
};
// Range: 0x805DF920 -> 0x805DF9F8
void DataTerminate() {
    // Local variables
    struct _Rb_tree_iterator i; // r1+0x14

    // References
    // -> class ObjectDir * gDataDir;
    // -> class Object * gDataThis;
    // -> class map gMacroTable;
}

// Range: 0x805DF9F8 -> 0x805DFB94
void DataSetMacro(class Symbol & key /* r30 */, class DataArray * macro /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> static unsigned char gDataMacroWarning;
    // -> class map gMacroTable;
}

// Range: 0x805DFB94 -> 0x805DFC24
class DataArray * DataGetMacro() {
    // Local variables
    struct _Rb_tree_iterator i; // r1+0x10

    // References
    // -> class map gMacroTable;
}

// Range: 0x805DFC24 -> 0x805DFD40
class Symbol DataGetMacroByInt(int value /* r29 */, const char * prefix /* r30 */) {
    // Local variables
    struct _Rb_tree_iterator it; // r1+0x1C
    class DataArray * macro_array; // r3
    class DataNode & node; // r0
    class String name; // r1+0x20

    // References
    // -> const char * gNullStr;
    // -> class map gMacroTable;
}

// Range: 0x805DFD40 -> 0x805DFE98
void DataMergeTags(class DataArray * dest /* r28 */, class DataArray * src /* r29 */) {
    // Local variables
    int i; // r31
    class DataNode & n; // r0
    class DataArray * srcArray; // r30
    class DataArray * destArray; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class DataNode & thisVar; // size: 0x4, address: 0x80A54E94
// Range: 0x805DFE98 -> 0x805DFF7C
class Object * DataSetThis(class Object * o /* r30 */) {
    // Local variables
    class Object * old; // r31

    // References
    // -> static class DataNode & thisVar;
    // -> class ObjectDir * gDataDir;
    // -> class ObjectDir * sMainDir;
    // -> class Object * gDataThis;
}

// Range: 0x805DFF7C -> 0x805DFF84
class Object * DataThis() {
    // References
    // -> class Object * gDataThis;
}

// Range: 0x805DFF84 -> 0x805E0028
void DataPushVar(class DataNode * var /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static struct VarStack gVarStack[100];
    // -> static struct VarStack * gVarStackPtr;
}

// Range: 0x805E0028 -> 0x805E00EC
void DataPopVar() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static struct VarStack gVarStack[100];
    // -> static struct VarStack * gVarStackPtr;
}

// Range: 0x805E00EC -> 0x805E01A8
static void __sinit_\DataUtl_cpp() {
    // References
    // -> static struct VarStack gVarStack[100];
    // -> class map gMacroTable;
}


