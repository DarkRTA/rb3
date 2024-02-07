/*
    Compile unit: C:\rockband2\system\src\obj\DataFunc.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805D4D44 -> 0x805DC9BC
*/
class map gDataFuncs; // size: 0x18, address: 0x80988E78
// Range: 0x805D4D44 -> 0x805D4EF0
void DataRegisterFunc(class Symbol & sym /* r30 */, class DataNode (* func)(class DataArray *) /* r31 */) {
    // Local variables
    struct _Rb_tree_iterator i; // r1+0x2C

    // References
    // -> class Debug TheDebug;
    // -> class map gDataFuncs;
}

class DataFuncObj : public Object {
    // total size: 0x2C
    class DataArray * mFunc; // offset 0x28, size 0x4
};
// Range: 0x805D4EF0 -> 0x805D4FFC
class DataNode DataFuncObj::New(class DataArray * a /* r29 */) {
    // References
    // -> struct [anonymous] __vt__11DataFuncObj;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x805D4FFC -> 0x805D50A0
static class DataNode DataSprintf(class DataArray * array /* r30 */) {
    // Local variables
    class FormatString f; // r1+0x8
    int i; // r31
}

// Range: 0x805D50A0 -> 0x805D5154
static class DataNode DataPrintf(class DataArray * array /* r30 */) {
    // Local variables
    class FormatString f; // r1+0x8
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D5154 -> 0x805D51D4
static class DataNode DataPrint(class DataArray * array /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D51D4 -> 0x805D5268
static class DataNode DataSprint(class DataArray * array /* r30 */) {
    // Local variables
    class String s; // r1+0x8
    int i; // r31
}

// Range: 0x805D5268 -> 0x805D5344
static class DataNode DataSet(class DataNode * r /* r30 */, class DataArray * array /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
}

// Range: 0x805D5344 -> 0x805D53FC
static class DataNode DataIfElse(class DataArray * array /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D53FC -> 0x805D54D4
static class DataNode DataIf(class DataArray * array /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x805D54D4 -> 0x805D55B0
static class DataNode DataUnless(class DataArray * array /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x805D55B0 -> 0x805D5628
static class DataNode DataEq(class DataArray * array /* r30 */) {}

// Range: 0x805D5628 -> 0x805D5794
static class DataNode DataFindElem(class DataArray * array /* r27 */) {
    // Local variables
    int i; // r28
}

// Range: 0x805D5794 -> 0x805D580C
static class DataNode DataNe() {}

// Range: 0x805D580C -> 0x805D5890
static class DataNode DataLe(class DataArray * array /* r31 */) {}

// Range: 0x805D5890 -> 0x805D5910
static class DataNode DataLt(class DataArray * array /* r31 */) {}

// Range: 0x805D5910 -> 0x805D5994
static class DataNode DataGe(class DataArray * array /* r31 */) {}

// Range: 0x805D5994 -> 0x805D5A14
static class DataNode DataGt(class DataArray * array /* r31 */) {}

// Range: 0x805D5A14 -> 0x805D5A60
static class DataNode DataNot() {}

// Range: 0x805D5A60 -> 0x805D5AF0
static class DataNode DataAnd(class DataArray * array /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x805D5AF0 -> 0x805D5B7C
static class DataNode DataOr(class DataArray * array /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x805D5B7C -> 0x805D5BF8
static class DataNode DataXor(class DataArray * array /* r30 */) {}

// Range: 0x805D5BF8 -> 0x805D5CC8
static class DataNode DataBitAnd(class DataArray * array /* r29 */) {
    // Local variables
    int val; // r31
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805D5CC8 -> 0x805D5EC0
static class DataNode DataAndEqual(class DataArray * array /* r28 */) {
    // Local variables
    class DataArray * property; // r29
    int r; // r30

    // References
    // -> class Object * gDataThis;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805D5EC0 -> 0x805D60B8
static class DataNode DataMaskEqual(class DataArray * array /* r28 */) {
    // Local variables
    class DataArray * property; // r29
    int r; // r30

    // References
    // -> class Object * gDataThis;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805D60B8 -> 0x805D62B0
static class DataNode DataOrEqual(class DataArray * array /* r28 */) {
    // Local variables
    class DataArray * property; // r29
    int r; // r30

    // References
    // -> class Object * gDataThis;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805D62B0 -> 0x805D6380
static class DataNode DataBitOr(class DataArray * array /* r29 */) {
    // Local variables
    int val; // r31
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805D6380 -> 0x805D63F8
static class DataNode DataBitXor(class DataArray * array /* r30 */) {}

// Range: 0x805D63F8 -> 0x805D6450
static class DataNode DataBitNot(class DataArray * array /* r31 */) {}

// Range: 0x805D6450 -> 0x805D64D0
static class DataNode DataLowestBit(class DataArray * array /* r31 */) {
    // Local variables
    int val; // r0
    int bit; // r4
}

// Range: 0x805D64D0 -> 0x805D659C
static class DataNode DataWhile(class DataArray * array /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x805D659C -> 0x805D6600
static class DataNode DataVar(class DataArray * array /* r31 */) {}

// Range: 0x805D6600 -> 0x805D66E4
static class DataNode DataPackColor(class DataArray * array /* r31 */) {}

// Range: 0x805D66E4 -> 0x805D68CC
static class DataNode DataUnpackColor(class DataArray * array /* r30 */) {}

// Range: 0x805D68CC -> 0x805D6A48
static class DataNode DataDo(class DataNode * n /* r26 */, class DataArray * array /* r27 */) {
    // Local variables
    int size; // r30
    int i; // r29
    class DataArray * binding; // r28
    int numVars; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D6A48 -> 0x805D6B4C
static class DataNode DataMin(class DataArray * array /* r30 */) {}

// Range: 0x805D6B4C -> 0x805D6C50
static class DataNode DataMax(class DataArray * array /* r30 */) {}

// Range: 0x805D6C50 -> 0x805D6CE4
static class DataNode DataAbs(class DataArray * array /* r30 */) {
    // Local variables
    float res; // f0
}

// Range: 0x805D6CE4 -> 0x805D6DEC
static class DataNode DataAdd(class DataArray * array /* r28 */) {
    // Local variables
    int isum; // r30
    float fsum; // f31
    int size; // r0
    int i; // r29
}

// Range: 0x805D6DEC -> 0x805D6EB0
static class DataNode DataAddEq(class DataNode * r /* r30 */, class DataArray * array /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
}

// Range: 0x805D6EB0 -> 0x805D6FF0
static class DataNode DataSub(class DataArray * array /* r29 */) {}

// Range: 0x805D6FF0 -> 0x805D70AC
static class DataNode DataMean(class DataArray * array /* r29 */) {
    // Local variables
    float fsum; // f31
    int size; // r0
    int i; // r30
}

// Range: 0x805D70AC -> 0x805D7200
static class DataNode DataClamp(class DataArray * array /* r28 */) {}

// Range: 0x805D7200 -> 0x805D72C4
static class DataNode DataSubEq(class DataNode * r /* r30 */, class DataArray * array /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
}

// Range: 0x805D72C4 -> 0x805D7388
static class DataNode DataClampEq(class DataNode * r /* r30 */, class DataArray * array /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
}

// Range: 0x805D7388 -> 0x805D746C
static class DataNode DataMultiply(class DataArray * array /* r29 */) {}

// Range: 0x805D746C -> 0x805D7530
static class DataNode DataMultiplyEq(class DataNode * r /* r30 */, class DataArray * array /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
}

// Range: 0x805D7530 -> 0x805D75B0
static class DataNode DataDivide(class DataArray * array /* r31 */) {}

// Range: 0x805D75B0 -> 0x805D7674
static class DataNode DataDivideEq(class DataNode * r /* r30 */, class DataArray * array /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
}

// Range: 0x805D7674 -> 0x805D7790
static class DataNode DataMod(class DataArray * array /* r29 */) {}

// Range: 0x805D7790 -> 0x805D78D8
static class DataNode DataDist(class DataArray * array /* r31 */) {
    // Local variables
    class Vector3 v; // r1+0x10
}

// Range: 0x805D78D8 -> 0x805D7934
static class DataNode DataSymbol(class DataArray * array /* r31 */) {}

// Range: 0x805D7934 -> 0x805D79E0
static class DataNode DataInt(class DataArray * array /* r31 */) {}

// Range: 0x805D79E0 -> 0x805D7A3C
static class DataNode DataFloor(class DataArray * array /* r31 */) {}

// Range: 0x805D7A3C -> 0x805D7A98
static class DataNode DataCeil(class DataArray * array /* r31 */) {}

// Range: 0x805D7A98 -> 0x805D7B0C
static class DataNode DataDelete(class DataArray * array /* r31 */) {}

// Range: 0x805D7B0C -> 0x805D7C60
static class DataNode DataNew(class DataArray * array /* r30 */) {
    // Local variables
    class Object * o; // r31

    // References
    // -> class ObjectDir * gDataDir;
}

// Range: 0x805D7C60 -> 0x805D7DE4
static class DataNode DataForEach(class DataArray * array /* r26 */) {
    // Local variables
    class DataArray * values; // r30
    class DataNode * var; // r29
    class DataNode val; // r1+0x10
    int i; // r28
    int j; // r27
}

// Range: 0x805D7DE4 -> 0x805D7F78
static class DataNode DataForEachInt(class DataArray * array /* r29 */) {
    // Local variables
    class DataNode * var; // r30
    int end; // r0
    class DataNode val; // r1+0x18
    int i; // r27
    int j; // r27
}

// Range: 0x805D7F78 -> 0x805D7FF4
static class DataNode DataGetElem(class DataArray * array /* r30 */) {}

// Range: 0x805D7FF4 -> 0x805D80F8
static class DataNode DataObject(class DataArray * array /* r30 */) {
    // Local variables
    const char * name; // r30
    class Object * o; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> class ObjectDir * gDataDir;
}

// Range: 0x805D80F8 -> 0x805D81FC
static class DataNode DataExists(class DataArray * array /* r30 */) {
    // Local variables
    unsigned char exists; // r0
    struct _Rb_tree_iterator func; // r1+0x14

    // References
    // -> class map gDataFuncs;
    // -> class ObjectDir * gDataDir;
}

// Range: 0x805D81FC -> 0x805D82A8
static class DataNode DataLocalize(class DataArray * array /* r30 */) {
    // Local variables
    unsigned char notify; // r31
    const char * str; // r4

    // References
    // -> const char * gNullStr;
}

// Range: 0x805D82A8 -> 0x805D8300
static class DataNode DataLocalizeSeparatedInt(class DataArray * array /* r31 */) {}

// Range: 0x805D8300 -> 0x805D83D4
static class DataNode DataStartsWith(class DataArray * array /* r29 */) {}

// Range: 0x805D83D4 -> 0x805D8608
static class DataNode DataTime(class DataArray * array /* r29 */) {
    // Local variables
    int i; // r28
    class DataNode & n; // r0
    class Timer t; // r1+0x10

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Debug TheDebug;
}

// Range: 0x805D8608 -> 0x805D8684
static class DataNode DataRandomInt(class DataArray * array /* r30 */) {}

// Range: 0x805D8684 -> 0x805D8720
static class DataNode DataRandomFloat(class DataArray * array /* r31 */) {}

// Range: 0x805D8720 -> 0x805D87C8
static class DataNode DataRandomElem(class DataArray * array /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D87C8 -> 0x805D8824
static class DataNode DataRandom(class DataArray * array /* r31 */) {}

// Range: 0x805D8824 -> 0x805D887C
static class DataNode DataRandomSeed(class DataArray * array /* r31 */) {}

// Range: 0x805D887C -> 0x805D8920
static class DataNode DataNotify(class DataArray * array /* r30 */) {
    // Local variables
    class String msg; // r1+0x8
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D8920 -> 0x805D89DC
static class DataNode DataFail(class DataArray * array /* r30 */) {
    // Local variables
    class String msg; // r1+0x8
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D89DC -> 0x805D8AB8
static class DataNode DataCond(class DataArray * array /* r29 */) {
    // Local variables
    int i; // r31
    class DataNode & n; // r0
    class DataArray * a; // r30

    // References
    // -> class Object * gDataThis;
}

// Range: 0x805D8AB8 -> 0x805D8BF0
static class DataNode DataSwitch(class DataArray * array /* r26 */) {
    // Local variables
    const class DataNode & node; // r29
    int i; // r28
    class DataNode & n; // r0
    class DataArray * a; // r27

    // References
    // -> class Object * gDataThis;
}

// Range: 0x805D8BF0 -> 0x805D8C90
static class DataNode DataInsertElems(class DataArray * array /* r29 */) {}

// Range: 0x805D8C90 -> 0x805D8D30
static class DataNode DataInsertElem(class DataArray * array /* r29 */) {}

// Range: 0x805D8D30 -> 0x805D8D98
static class DataNode DataPrintArray(class DataArray * array /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D8D98 -> 0x805D8E68
static class DataNode DataSize(class DataArray * array /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
}

// Range: 0x805D8E68 -> 0x805D8EE4
static class DataNode DataRemoveElem(class DataArray * array /* r30 */) {}

// Range: 0x805D8EE4 -> 0x805D8F60
static class DataNode DataResize(class DataArray * array /* r30 */) {}

// Range: 0x805D8F60 -> 0x805D919C
static class DataNode DataNewArray(class DataArray * array /* r30 */) {
    // Local variables
    class DataArrayPtr a; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x805D919C -> 0x805D9244
static class DataNode DataSetElem(class DataArray * array /* r29 */) {}

// Range: 0x805D9244 -> 0x805D9284
static class DataNode DataQuote() {}

// Range: 0x805D9284 -> 0x805D92CC
static class DataNode DataEval() {}

// Range: 0x805D92CC -> 0x805D93B0
static class DataNode DataReverseInterp(class DataArray * array /* r31 */) {}

// Range: 0x805D93B0 -> 0x805D945C
static class DataNode DataInterp(class DataArray * array /* r31 */) {}

// Range: 0x805D945C -> 0x805D95E8
static class DataNode DataInc(class DataArray * array /* r30 */) {
    // Local variables
    class DataArray * property; // r31
    int r; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
}

// Range: 0x805D95E8 -> 0x805D9774
static class DataNode DataDec(class DataArray * array /* r30 */) {
    // Local variables
    class DataArray * property; // r31
    int r; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
}

// Range: 0x805D9774 -> 0x805D9874
static class DataNode DataHandleType(class DataArray * array /* r29 */) {
    // Local variables
    int i; // r30
    class Object * o; // r0

    // References
    // -> class ObjectDir * gDataDir;
}

// Range: 0x805D9874 -> 0x805D9958
static class DataNode DataExport(class DataArray * arr /* r29 */) {
    // Local variables
    unsigned char callType; // r30
    class Object * o; // r0

    // References
    // -> class ObjectDir * gDataDir;
}

// Range: 0x805D9958 -> 0x805D9A68
static class DataNode DataHandle(class DataArray * array /* r29 */) {
    // Local variables
    int i; // r30
    class Object * o; // r0

    // References
    // -> class ObjectDir * gDataDir;
}

// Range: 0x805D9A68 -> 0x805D9B6C
static class DataNode DataHandleRet(class DataArray * array /* r28 */) {
    // Local variables
    class Object * o; // r29
    class String s; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> class ObjectDir * gDataDir;
}

// Range: 0x805D9B6C -> 0x805D9C60
static class DataNode DataRun(class DataNode * r /* r30 */, class DataArray * array /* r31 */) {
    // Local variables
    const char * path; // r0
    class DataArray * script; // r31

    // References
    // -> class Object * gDataThis;
}

// Range: 0x805D9C60 -> 0x805D9CEC
static class DataNode OnReadFile(class DataNode * n /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x805D9CEC -> 0x805D9D34
static class DataNode DataExit() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D9D34 -> 0x805D9E50
static class DataNode DataFindExists(class DataArray * array /* r28 */) {
    // Local variables
    class DataArray * a; // r30
    int i; // r29
    class String s; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D9E50 -> 0x805D9F04
static class DataNode DataFind(class DataNode * r /* r31 */, class DataArray * array /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D9F04 -> 0x805DA038
static class DataNode DataFindObj(class DataArray * array /* r29 */) {
    // Local variables
    class ObjectDir * d; // r31
    int i; // r30
    const char * name; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x805DA038 -> 0x805DA090
static class DataNode DataBasename(class DataArray * array /* r31 */) {}

// Range: 0x805DA090 -> 0x805DA13C
static class DataNode DataDirname(class DataArray * array /* r30 */) {
    // Local variables
    const char * path; // r30
    int last_slash; // r0

    // References
    // -> unsigned int npos;
}

// Range: 0x805DA13C -> 0x805DA1B8
static class DataNode DataHasSubStr(class DataArray * array /* r30 */) {}

// Range: 0x805DA1B8 -> 0x805DA27C
static class DataNode DataSubStr(class DataArray * array /* r30 */) {
    // Local variables
    class String val; // r1+0x14
    class String ret; // r1+0x8
}

// Range: 0x805DA27C -> 0x805DA2D4
static class DataNode DataStrlen(class DataArray * array /* r31 */) {}

// Range: 0x805DA2D4 -> 0x805DA374
static class DataNode DataStrElem(class DataArray * array /* r30 */) {
    // Local variables
    char buffer[2]; // r1+0x8
}

// Range: 0x805DA374 -> 0x805DA48C
static class DataNode DataSearchReplace(class DataArray * array /* r29 */) {
    // Local variables
    char out[1024]; // r1+0x10
}

// Range: 0x805DA48C -> 0x805DA528
static class DataNode DataPushBack(class DataArray * array /* r29 */) {}

// Range: 0x805DA528 -> 0x805DA580
static class DataNode DataSort(class DataArray * array /* r31 */) {}

// Range: 0x805DA580 -> 0x805DA5C8
static class DataNode DataGetType() {}

// Range: 0x805DA5C8 -> 0x805DA62C
static class DataNode DataWith(class DataArray * array /* r31 */) {}

class DataThisPtr : public ObjPtr {
    // total size: 0xC
};
static class DataThisPtr gDataThisPtr; // size: 0xC, address: 0x80988E9C
// Range: 0x805DA62C -> 0x805DA6CC
static class DataNode OnSetThis(class DataArray * array /* r31 */) {
    // References
    // -> static class DataThisPtr gDataThisPtr;
}

// Range: 0x805DA6CC -> 0x805DA7C4
static class DataNode DataMacroElem(class DataArray * array /* r31 */) {
    // Local variables
    class DataArray * macro; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class DataArrayPtr d; // size: 0x8, address: 0x80988EB8
class DataMergeFilter : public MergeFilter {
    // total size: 0x18
    enum DataType mType; // offset 0x8, size 0x4
    class DataNode (* mFunc)(class DataArray *); // offset 0xC, size 0x4
    class Object * mObj; // offset 0x10, size 0x4
    enum Action mAction; // offset 0x14, size 0x4
};
// Range: 0x805DA7C4 -> 0x805DA9DC
static class DataNode DataMergeDirs(class DataArray * msg /* r31 */) {
    // Local variables
    class DataMergeFilter filter; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class map gDataFuncs;
    // -> class ObjectDir * gDataDir;
    // -> struct [anonymous] __vt__15DataMergeFilter;
}

// Range: 0x805DA9DC -> 0x805DAA60
static class DataNode DataReplaceObject(class DataArray * msg /* r30 */) {}

// Range: 0x805DAA60 -> 0x805DAB08
static class DataNode DataNextName(class DataArray * msg /* r30 */) {
    // Local variables
    class ObjectDir * dir; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> class ObjectDir * gDataDir;
}

static class Symbol unquote; // size: 0x4, address: 0x80A54E6C
static class Symbol unquoteAbbrev; // size: 0x4, address: 0x80A54E74
// Range: 0x805DAB08 -> 0x805DAD3C
static class DataNode Quasiquote(const class DataNode & n /* r28 */) {
    // Local variables
    enum DataType t; // r0
    class DataArray * a; // r29
    class DataArrayPtr d; // r1+0x18
    int i; // r28

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol unquoteAbbrev;
    // -> static class Symbol unquote;
}

// Range: 0x805DAD3C -> 0x805DAD7C
static class DataNode DataQuasiquote() {}

// Range: 0x805DAD7C -> 0x805DADC0
static class DataNode DataUnquote() {}

// Range: 0x805DADC0 -> 0x805DB098
static class DataNode DataGetDateTime(class DataArray * msg /* r31 */) {
    // Local variables
    struct DateTime d; // r1+0x38
}

// Range: 0x805DB098 -> 0x805DB7F4
static class DataNode DataObjectList(class DataArray * msg /* r29 */) {
    // Local variables
    class Symbol className; // r1+0x40
    int count; // r30
    class ObjDirItr o; // r1+0x74
    class DataArrayPtr arr; // r1+0x58
    class ObjDirItr o; // r1+0x60

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
}

// Range: 0x805DB7F4 -> 0x805DC43C
void DataInitFuncs() {
    // Local variables
    char functionName[8]; // r1+0x208
}

// Range: 0x805DC43C -> 0x805DC494
void DataTermFuncs() {
    // References
    // -> class map gDataFuncs;
}

// Range: 0x805DC494 -> 0x805DC520
class Symbol DataFuncName(class DataNode (* func)(class DataArray *) /* r31 */) {
    // Local variables
    struct _Rb_tree_iterator i; // r1+0x14

    // References
    // -> class map gDataFuncs;
}

// Range: 0x805DC520 -> 0x805DC7A4
enum Action DataMergeFilter::Filter(class DataMergeFilter * const this /* r30 */, class Object * from /* r29 */, class Object * to /* r31 */) {
    // References
    // -> class DataArrayPtr d;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

struct {
    // total size: 0x10
} __vt__15DataMergeFilter; // size: 0x10, address: 0x80927E40
struct {
    // total size: 0x8
} __RTTI__15DataMergeFilter; // size: 0x8, address: 0x80927E70
// Range: 0x805DC7A4 -> 0x805DC82C
void DataThisPtr::Replace(class DataThisPtr * const this /* r29 */, class Object * from /* r30 */, class Object * to /* r31 */) {
    // References
    // -> class Object * gDataThis;
}

struct {
    // total size: 0x18
} __vt__11DataThisPtr; // size: 0x18, address: 0x80927E78
struct {
    // total size: 0x8
} __RTTI__11DataThisPtr; // size: 0x8, address: 0x80927EB0
// Range: 0x805DC82C -> 0x805DC844
class DataNode DataFuncObj::Handle() {
    // References
    // -> class Object * gDataThis;
}

// Range: 0x805DC844 -> 0x805DC8D8
void * DataFuncObj::~DataFuncObj(class DataFuncObj * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__11DataFuncObj;
}

struct {
    // total size: 0x54
} __vt__11DataFuncObj; // size: 0x54, address: 0x80927F08
struct {
    // total size: 0x8
} __RTTI__11DataFuncObj; // size: 0x8, address: 0x80927F80
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std70_Rb_tree_node<Q211stlpmtx_std38pair<C6Symbol,PFP9DataArray_8DataNode>>; // size: 0x8, address: 0x809280A8
// Range: 0x805DC8D8 -> 0x805DC9BC
static void __sinit_\DataFunc_cpp() {
    // References
    // -> struct [anonymous] __vt__11DataThisPtr;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> static class DataThisPtr gDataThisPtr;
    // -> class map gDataFuncs;
}


