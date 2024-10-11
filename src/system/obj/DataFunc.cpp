#include "obj/DataFunc.h"
#include "math/Rand.h"
#include "obj/Data.h"
#include "obj/DataFile.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "os/File.h"
#include "utl/MakeString.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "math/MathFuncs.h"
#include "obj/DataUtl.h"
#include "utl/Locale.h"
#include "os/DateTime.h"
#include "utl/Symbols.h"
#include <cstring>
#include <map>
#include <stdlib.h>

#include "decomp.h"

std::map<Symbol, DataFunc*> gDataFuncs;
DataThisPtr gDataThisPtr;

extern Hmx::Object *gDataThis;
extern class ObjectDir* gDataDir;

// from RBVR PDB build
namespace {
    inline void PrintToStream(TextStream& stream, const DataArray* array, int start) {
        for (int i = start; i < array->Size(); i++){
            array->Evaluate(i).Print(stream, true);
        }
    }

    inline bool SwitchMatch(DataNode& dn1, DataNode& dn2) {
        if (dn1.Type() == kDataArray) {
            DataArray *arr = dn1.mValue.array;
            for (int i = 0; i < arr->Size(); i++) {
                if (arr->Node(i) == dn2) {
                    return true;
                }
            }
            return false;
        } else {
            return dn1 == dn2;
        }
    }
}

// Force ~MergeFilter() to generate here
DECOMP_FORCEDTOR(DataFunc, MergeFilter);

void DataRegisterFunc(Symbol s, DataFunc* func){
#ifdef MILO_DEBUG
    const std::map<Symbol, DataFunc*>::iterator it = gDataFuncs.find(s);
    if(it != gDataFuncs.end() && it->second != func)
        MILO_FAIL("Can't register different func %s", s);
#endif
    gDataFuncs[s] = func;
}

DataNode DataFuncObj::New(DataArray* arr){
    Hmx::Object* o = ObjectDir::Main()->FindObject(arr->Str(1), false);
    if(o) delete o;
    return new DataFuncObj(arr);
}

DEF_DATA_FUNC(DataSprintf) {
    FormatString fs(array->Str(1));
    for (int i = 2; i < array->Size(); i++) {
        fs << array->Evaluate(i);
    }
    return fs.Str();
}

DEF_DATA_FUNC(DataPrintf) {
    FormatString fs(array->Str(1));
    for (int i = 2; i < array->Size(); i++) {
        fs << array->Evaluate(i);
    }
    TheDebug << fs.Str();
    return 0;
}

DEF_DATA_FUNC(DataPrint) {
    PrintToStream(TheDebug, array, 1);
    return 0;
}

DEF_DATA_FUNC(DataSprint) {
    class String str;
    PrintToStream(str, array, 1);
    return str.c_str();
}

DEF_DATA_FUNC(DataSet) {
    const DataArray* a = array;
    DataNode ret(a->Evaluate(2));
    if (a->Type(1) == kDataProperty) {
        MILO_ASSERT(gDataThis, 0x9D);
        gDataThis->SetProperty(a->Node(1).mValue.array, ret);
    }
    else *a->Var(1) = ret;
    return ret;
}

DEF_DATA_FUNC(DataSetVar) {
    DataNode ret = array->Evaluate(2);
    DataVariable(array->ForceSym(1)) = ret;
    return ret;
}

DEF_DATA_FUNC(DataIfElse) {
    if(array->Size() != 4) MILO_FAIL("One condition and two alternatives expected (file %s, line %d)", array->File(), array->Line());
    if(array->Node(1).NotNull())
        return array->Evaluate(2);
    else return array->Evaluate(3);
}

DEF_DATA_FUNC(DataIf) {
    if (array->Node(1).NotNull()) {
        for (int i = 2; i < array->Size(); i++) {
            array->Command(i)->Execute();
        }
        return 0;
    } else
        return 0;
}

DEF_DATA_FUNC(DataUnless){
    bool fart = !array->Node(1).NotNull();
    if(fart){
        for(int i = 2; i < array->Size(); i++){
            array->Command(i)->Execute();
        }
        return 0;
    }
    return 0;
}

DEF_DATA_FUNC(DataEq) {
    DataNode *dn1 = &array->Evaluate(1);
    DataNode *dn2 = &array->Evaluate(2);
    return dn1->operator==(*dn2);
}

DEF_DATA_FUNC(DataFindElem) {
    DataArray *arr = array->Array(1);
    arr->AddRef();
    DataNode *dn = &array->Evaluate(2);
    for (int i = 0; i < arr->Size(); i++) {
        if (!(arr->Node(i).operator==(*dn)))
            continue;
        if (array->Size() > 3) {
            array->Var(3)->operator=(DataNode(i));
        }
        arr->Release();
        return 1;
    }
    arr->Release();
    return 0;
}

DEF_DATA_FUNC(DataNe){
    return DataEq(array).mValue.integer == 0;
}

DEF_DATA_FUNC(DataLe) {
    return array->Float(1) <= array->Float(2);
}

DEF_DATA_FUNC(DataLt) {
    return array->Float(1) < array->Float(2);
}

DEF_DATA_FUNC(DataGe) {
    return array->Float(1) >= array->Float(2);
}

DEF_DATA_FUNC(DataGt) {
    return array->Float(1) > array->Float(2);
}

DEF_DATA_FUNC(DataNot) {
    bool ret = !array->Node(1).NotNull();
    return ret;
}

DEF_DATA_FUNC(DataAnd) {
    for (int i = 1; i < array->Size(); i++) {
        bool ret = !array->Node(i).NotNull();
        if (ret) {
            return 0;
        }
    }
    return 1;
}

DEF_DATA_FUNC(DataOr) {
    for (int i = 1; i < array->Size(); i++) {
        if(array->Node(i).NotNull())
            return 1;
    }
    return 0;
}

DEF_DATA_FUNC(DataXor) {
    return array->Node(1).NotNull() != array->Node(2).NotNull();
}

DEF_DATA_FUNC(DataBitAnd) {
    MILO_ASSERT(array->Size() >= 3, 0x130);
    int res = array->Int(1);
    for (int i = 2; i < array->Size(); i++) {
        res &= array->Int(i);
    }
    return res;
}

DEF_DATA_FUNC(DataAndEqual){
    MILO_ASSERT(array->Size() == 3, 0x13C);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x141);
        DataArray* arr = ((const DataArray*)array)->Node(1).mValue.array;
        int res = gDataThis->Property(arr, true)->Int() & array->Int(2);
        gDataThis->SetProperty(arr, DataNode(res));
        return res;
    }
    else {
        DataNode* var = array->Var(1);
        int res = var->Int() & array->Int(2);
        return (*var = DataNode(res));
    }
}

DEF_DATA_FUNC(DataMaskEqual){
    MILO_ASSERT(array->Size() == 3, 0x152);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x157);
        DataArray* arr = ((const DataArray*)array)->Node(1).mValue.array;
        int res = gDataThis->Property(arr, true)->Int() & ~array->Int(2);
        gDataThis->SetProperty(arr, DataNode(res));
        return res;
    }
    else {
        DataNode* var = array->Var(1);
        int res = var->Int() & ~array->Int(2);
        return (*var = DataNode(res));
    }
}

DEF_DATA_FUNC(DataOrEqual){
    MILO_ASSERT(array->Size() == 3, 0x169);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x16E);
        DataArray* arr = ((const DataArray*)array)->Node(1).mValue.array;
        int res = gDataThis->Property(arr, true)->Int() | array->Int(2);
        gDataThis->SetProperty(arr, DataNode(res));
        return res;
    }
    else {
        DataNode* var = array->Var(1);
        int res = var->Int() | array->Int(2);
        return (*var = DataNode(res));
    }
}

DEF_DATA_FUNC(DataBitOr){
    MILO_ASSERT(array->Size() >= 3, 0x180);
    int res = array->Int(1);
    for(int i = 2; i < array->Size(); i++)
        res |= array->Int(i);
    return res;
}

DEF_DATA_FUNC(DataBitXor){
    return array->Int(1) ^ array->Int(2);
}

DEF_DATA_FUNC(DataBitNot){
    return ~array->Int(1);
}

DEF_DATA_FUNC(DataLowestBit) {
    int num = array->Int(1);
    int res;
    if(num == 0) res = 0;
    else {
        int j = 1;
        while(!(j & num))
            j *= 2;
        res = j;
    }
    return res;
}

DEF_DATA_FUNC(DataCountBits) {
    return CountBits(array->Int(1));
}

DEF_DATA_FUNC(DataWhile){
    while(array->Node(1).NotNull()){
        for(int i = 2; i < array->Size(); i++){
            array->Command(i)->Execute();
        }
    }
    return 0;
}

DEF_DATA_FUNC(DataVar){
    return &DataVariable(array->ForceSym(1));
}

DEF_DATA_FUNC(DataPackColor) {
    return
        ((int)(array->Float(3) * 255.0f) & 0xFF) << 0x10
        | ((int)(array->Float(2) * 255.0f) & 0xFF) << 8
        | ((int)(array->Float(1) * 255.0f) & 0xFF);
}

DEF_DATA_FUNC(DataUnpackColor) {
    int packed = array->Int(1);
    *array->Var(2) = DataNode((float)(packed & 0xFF) / 255.0f);
    *array->Var(3) = DataNode((float)(packed >> 8 & 0xFF) / 255.0f);
    *array->Var(4) = DataNode((float)(packed >> 0x10 & 0xFF) / 255.0f);
    return 0;
}

DEF_DATA_FUNC(DataDo){
    int cnt;
    int nodeCnt = array->Size();
    for(cnt = 1; array->Type(cnt) == kDataArray; cnt++){
        DataArray* arr = array->Node(cnt).mValue.array;
        DataNode* n = arr->Var(0);
        DataPushVar(n);
        if(arr->Size() == 2){
            *n = arr->Evaluate(1);
        }
        else if(arr->Size() != 1){
            MILO_FAIL("do var has more than one initializer");
        }
    }
    int delCnt = cnt - 1;
    for(; cnt < nodeCnt - 1; cnt++)
        array->Command(cnt)->Execute();
    DataNode ret(array->Evaluate(cnt));
    while(delCnt-- != 0) DataPopVar();
    return ret;
}

DEF_DATA_FUNC(DataMin){
    DataNode& n1 = array->Evaluate(1);
    DataNode& n2 = array->Evaluate(2);
    if(n1.Type() == kDataFloat || n2.Type() == kDataFloat){
        return Min<float>(n1.LiteralFloat(array), n2.LiteralFloat(array));
    }
    else {
        return Min<int>(n2.LiteralInt(array), n1.LiteralInt(array));
    }
}

DEF_DATA_FUNC(DataMax){
    DataNode& n1 = array->Evaluate(1);
    DataNode& n2 = array->Evaluate(2);
    if(n1.Type() == kDataFloat || n2.Type() == kDataFloat){
        return Max<float>(n1.LiteralFloat(array), n2.LiteralFloat(array));
    }
    else {
        return Max<int>(n2.LiteralInt(array), n1.LiteralInt(array));
    }
}

DEF_DATA_FUNC(DataAbs){
    DataNode& n = array->Evaluate(1);
    float f = std::fabs(n.LiteralFloat(array));
    if(n.Type() == kDataInt)
        return (int)f;
    else return f;
}

DEF_DATA_FUNC(DataAdd) {
    float sum_f = 0.0f;
    int sum_int = 0;
    int cnt = array->Size();
    int i;
    for (i = 1; i < cnt; i++) {
        DataNode& n = array->Evaluate(i);
        if(n.Type() != kDataInt){
            sum_f = sum_int + n.LiteralFloat(array);
            break;
        }
        sum_int += n.mValue.integer;
    }
    if (i == cnt)
        return sum_int;
    for (i++; i < cnt; i++) {
        sum_f += array->Float(i);
    }
    return sum_f;
}

DEF_DATA_FUNC(DataAddEq){
    DataNode ret = DataAdd(array);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x223);
        gDataThis->SetProperty(((const DataArray*)array)->Node(1).mValue.array, ret);
    }
    else *array->Var(1) = ret;
    return ret;
}

DEF_DATA_FUNC(DataSub) {
    DataNode& dn = array->Evaluate(1);
    if (array->Size() == 2) {
        if (dn.Type() == kDataFloat) {
            return -dn.LiteralFloat(array);
        } else
            return -dn.LiteralInt(array);
    } else {
        DataNode& dn2 = array->Evaluate(2);
        if (dn.Type() == kDataFloat || dn2.Type() == kDataFloat) {
            return dn.LiteralFloat(array) - dn2.LiteralFloat(array);
        } else {
            return dn.LiteralInt(array) - dn2.LiteralInt(array);
        }
    }
}

DEF_DATA_FUNC(DataMean) {
    float sum = 0.0;
    int cnt = array->Size();
    for (int i = 1; i < cnt; i++) {
        sum += array->Float(i);
    }
    return sum / (cnt - 1);
}

DEF_DATA_FUNC(DataClamp) {
    DataNode& dn1 = array->Evaluate(1);
    DataNode& dn2 = array->Evaluate(2);
    DataNode& dn3 = array->Evaluate(3);
    if(dn1.Type() == kDataFloat || dn2.Type() == kDataFloat || dn3.Type() == kDataFloat){
        return Clamp<float>(dn1.LiteralFloat(array), dn2.LiteralFloat(array), dn3.LiteralFloat(array));
    }
    else return Clamp<int>(dn1.LiteralInt(array), dn2.LiteralInt(array), dn3.LiteralInt(array));
}

DEF_DATA_FUNC(DataSubEq){
    DataNode ret = DataSub(array);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x259);
        gDataThis->SetProperty(((const DataArray*)array)->Node(1).mValue.array, ret);
    }
    else *array->Var(1) = ret;
    return ret;
}

DEF_DATA_FUNC(DataClampEq){
    DataNode ret = DataClamp(array);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x260);
        gDataThis->SetProperty(((const DataArray*)array)->Node(1).mValue.array, ret);
    }
    else *array->Var(1) = ret;
    return ret;
}

DEF_DATA_FUNC(DataMultiply){
    DataNode& dn1 = array->Evaluate(1);
    DataNode& dn2 = array->Evaluate(2);
    if(dn1.Type() == kDataFloat || dn2.Type() == kDataFloat){
        return dn1.LiteralFloat(array) * dn2.LiteralFloat(array);
    }
    else return dn1.LiteralInt(array) * dn2.LiteralInt(array);
}

DEF_DATA_FUNC(DataMultiplyEq){
    DataNode ret = DataMultiply(array);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x272);
        gDataThis->SetProperty(((const DataArray*)array)->Node(1).mValue.array, ret);
    }
    else *array->Var(1) = ret;
    return ret;
}

DEF_DATA_FUNC(DataDivide){
    return array->Float(1) / array->Float(2);
}

DEF_DATA_FUNC(DataDivideEq){
    DataNode ret = DataDivide(array);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x27E);
        gDataThis->SetProperty(((const DataArray*)array)->Node(1).mValue.array, ret);
    }
    else *array->Var(1) = ret;
    return ret;
}

DEF_DATA_FUNC(DataSqrt){
    return std::sqrt(array->Float(1));
}

DEF_DATA_FUNC(DataMod) {
    DataNode &n1 = array->Evaluate(1);
    DataNode &n2 = array->Evaluate(2);
    if (n1.Type() == kDataFloat || n2.Type() == kDataFloat)
        return Mod(n1.LiteralFloat(array), n2.LiteralFloat(array));
    else
        return Mod(n1.LiteralInt(array), n2.LiteralInt(array));
}

// // fn_8031D490
// DataNode DataMod(DataArray *da) {
//     DataNode *dn1 = &da->Evaluate(1);
//     DataNode *dn2 = &da->Evaluate(2);
//     if (dn1->Type() == kDataFloat || dn2->Type() == kDataFloat) {
//         return Modulo(dn1->LiteralFloat(da), dn2->LiteralFloat(da));
//     } else
//         return Modulo(dn1->LiteralInt(da), dn2->LiteralInt(da));
// }

DEF_DATA_FUNC(DataDist) {
    float x, y, z;

    z = array->Float(3) - array->Float(6);
    y = array->Float(2) - array->Float(5);
    x = array->Float(1) - array->Float(4);
    return std::sqrt(x*x+y*y+z*z);
}

DEF_DATA_FUNC(DataSymbol){
    return array->ForceSym(1);
}

DEF_DATA_FUNC(DataChar){
    static char newChar[2];
    DataNode& n = array->Evaluate(1);
    newChar[0] = n.Int();
    newChar[1] = '\0';
    return newChar;
}

DEF_DATA_FUNC(DataInt){
    DataNode& n = array->Evaluate(1);
    if(n.Type() == kDataSymbol)
        return atoi(n.mValue.symbol);
    else if(n.Type() == kDataObject || n.Type() == kDataInt)
        return n.mValue.integer;
    else return (int)n.LiteralFloat(array);
}

DEF_DATA_FUNC(DataRound){
    return Round(array->Evaluate(1).LiteralFloat());
}

DEF_DATA_FUNC(DataFloor){
    return std::floor(array->Float(1));
}

DEF_DATA_FUNC(DataCeil){
    return std::ceil(array->Float(1));
}

DEF_DATA_FUNC(DataDelete){
    Hmx::Object* obj = array->GetObj(1);
    delete obj;
    return 0;
}

DEF_DATA_FUNC(DataNew){
    Hmx::Object* obj = Hmx::Object::NewObject(array->Sym(1));
    if(array->Size() > 2){
        if(array->Type(2) == kDataArray){
            obj->SetTypeDef(array);
        }
        else {
            obj->SetName(array->Str(2), gDataDir);
            if(array->Size() > 3){
                if(array->Type(3) == kDataArray){
                    obj->SetTypeDef(array);
                }
                else {
                    obj->SetType(array->Sym(3));
                }
            }
        }
    }
    return obj;
}

DEF_DATA_FUNC(DataForEach) {
    DataArray *arr = array->Array(2);
    arr->AddRef();
    DataNode *var = array->Var(1);
    DataNode lol(*var);
    for (int i = 0; i < arr->Size(); i++) {
        *var = arr->Evaluate(i);
        for (int j = 3; j < array->Size(); j++) {
            array->Command(j)->Execute();
        }
    }
    *var = lol;
    arr->Release();
    return 0;
}

DEF_DATA_FUNC(DataForEachInt) {
    DataNode *var = array->Var(1);
    int i2 = array->Int(2);
    int i3 = array->Int(3);
    int r31 = -1;
    if (i2 > i3)
        r31 = 1;
    DataNode idk(*var);
    while (i2 != i3) {
        *var = DataNode(i2);
        for (int cnt = 4; cnt < array->Size(); cnt++) {
            array->Command(cnt)->Execute();
        }
        i2 = var->mValue.integer + r31;
    }
    *var = idk;
    return 0;
}

DEF_DATA_FUNC(DataGetElem) {
    int i = array->Int(2);
    DataArray *a = array->Array(1);
    return a->Node(i);
}

DEF_DATA_FUNC(DataGetLastElem) {
    DataArray *arr = array->Array(1);
    MILO_ASSERT(arr->Size() > 0, 0x3A8);
    return arr->Node(arr->Size() - 1);
}

DEF_DATA_FUNC(DataObject) {
    DataNode& n = array->Evaluate(1);
    if (n.Type() == kDataObject) return n;
    else {
        const char* s = n.LiteralStr(array);
        Hmx::Object* o = gDataDir->FindObject(s, true);
        if (!o && s[0]) {
            MILO_FAIL(kNotObjectMsg, s, PathName(gDataDir) ? PathName(gDataDir) : "**no file**");
        }
        return o;
    }
}

DEF_DATA_FUNC(DataExists){
    const char* s = array->Str(1);
    bool does_exist = gDataDir->FindObject(s, true);
    if (!does_exist) {
        Symbol sym(s);
        std::map<Symbol, DataFunc*>::iterator it = gDataFuncs.find(sym);
        does_exist = it != gDataFuncs.end();
    }
    return does_exist;
}

DEF_DATA_FUNC(DataLocalize){
    const char* loc = Localize(array->ForceSym(1), nullptr);
    const char* ret = (loc) ? loc : gNullStr;
    return ret;
}

DEF_DATA_FUNC(DataLocalizeSeparatedInt){
    return LocalizeSeparatedInt(array->Int(1));
}

DEF_DATA_FUNC(DataLocalizeFloat){
    return LocalizeFloat(array->Str(1), array->Float(2));
}

DEF_DATA_FUNC(DataSyncReloadLocale){
    SyncReloadLocale();
    return 1;
}

DEF_DATA_FUNC(DataPrintUnused){
    return SystemConfig(array->Sym(1))->PrintUnused(TheDebug, kDataArray, true);
}

DEF_DATA_FUNC(DataStartsWith) {
    return !strncmp(array->Str(1), array->Str(2), (array->Size() > 3) ? array->Int(3) : strlen(array->Str(2)));
}

DEF_DATA_FUNC(DataTime) {
    int i;
    for (i = 1; i < array->Size(); i++) {
        DataNode& eval = array->Node(i);
        if (eval.Type() == kDataCommand) break;
        eval.Print(TheDebug, true);
    }
    if (i == 1) TheDebug << MakeString("Timing %s, line %d:", array->File(), array->Line());
    Timer time;
    time.Start();
    while (i < array->Size()) {
        array->Command(i++)->Execute();
    }
    time.Split();
    TheDebug << MakeString(" %f ms\n", time.Ms());
    return time.Ms();
};

DEF_DATA_FUNC(DataRandomInt) {
    return RandomInt(array->Int(1), array->Int(2));
}

DEF_DATA_FUNC(DataRandomFloat) {
    if (array->Size() > 1) {
        return RandomFloat(array->Float(1), array->Float(2));
    } else
        return RandomFloat();
}

DEF_DATA_FUNC(DataRandomElem) {
    DataArray *a = array->Array(1);
    MILO_ASSERT_FMT(a->Size() != 0, "Empty array (file %s, line %d)", a->File(), a->Line());
    return a->Node(RandomInt(0, a->Size()));
}

DEF_DATA_FUNC(DataRandom) {
    return array->Evaluate(RandomInt(1, array->Size()));
}

DEF_DATA_FUNC(DataRandomSeed) {
    SeedRand(array->Int(1));
    return 0;
}

DEF_DATA_FUNC(DataNotify){
#ifdef MILO_DEBUG
    class String str;
    PrintToStream(str, array, 1);
    TheDebug.Notify(str.c_str());
#endif
    return 0;
}

DEF_DATA_FUNC(DataNotifyBeta) {
#ifdef MILO_DEBUG
    class String str;
    PrintToStream(str, array, 1);
    TheDebug << MakeString(str.c_str());
#endif
    return 0;
}

// DataNode DataNotifyBeta(DataArray *da)

// {
//   DataNode *pDVar1;
//   char *pcVar2;
//   int iVar3;
//   undefined local_938 [4];
//   String SStack_934;
//   char acStack_928 [256];
//   FormatString aFStack_828 [2076];

//   String::String(&SStack_934);
//   for (iVar3 = 1; iVar3 < da->mSize; iVar3 = iVar3 + 1) {
//     pDVar1 = (DataNode *)DataArray::Node(da,iVar3);
//     pDVar1 = (DataNode *)DataNode::Evaluate(pDVar1);
//     DataNode::Print(pDVar1,(TextStream *)&SStack_934,true);
//   }
//   FormatString::FormatString(aFStack_828,SStack_934.mStr);
//   pcVar2 = (char *)FormatString::Str(aFStack_828);
//   if (TheDebug._28_4_ == 0) {
//     pcVar2 = MakeString(@STRING@__ls__9DebugBetaFPCc@0,pcVar2);
//     TextStream::operator_<<((TextStream *)TheDebug,pcVar2);
//   }
//   else {
//     local_938[0] = 0;
//     pcVar2 = MakeString(@STRING@__ls__9DebugBetaFPCc,pcVar2);
//     strncpy(acStack_928,pcVar2,0xfe);
//     (*(code *)TheDebug._28_4_)(local_938,acStack_928,0);
//   }
//   param_1->mNodes = (DataNode *)0x0;
//   param_1->mFile = 6;
//   String::~String(&SStack_934);
//   return;
// }

DEF_DATA_FUNC(DataFail){
#ifdef MILO_DEBUG
    class String str;
    PrintToStream(str, array, 1);
    TheDebug << MakeString("%d\n", array->Line());
    TheDebug.Fail(str.c_str());
#endif
    return 0;
}

DEF_DATA_FUNC(DataNotifyOnce) {
#ifdef MILO_DEBUG
    class String str;
    PrintToStream(str, array, 1);
    MILO_NOTIFY_ONCE(str.c_str())
#endif
    return 0;
}

DEF_DATA_FUNC(DataCond){
    for(int i = 1; i < array->Size(); i++){
        DataNode& node = array->Node(i);
        if(node.Type() == kDataArray){
            DataArray* arr = node.mValue.array;
            if(arr->Node(0).NotNull()){
                return arr->ExecuteScript(1, gDataThis, 0, 1);
            }
        }
        else return array->ExecuteScript(i, gDataThis, 0, 1);
    }
    return 0;
}

DEF_DATA_FUNC(DataSwitch){
    DataNode& n = array->Evaluate(1);
    for (int i = 2; i < array->Size(); i++) {
        DataNode& work = array->Node(i);
        if(work.Type() == kDataArray){
            DataArray* nextarr = work.mValue.array;
            DataNode& next = nextarr->Node(0);
            if(SwitchMatch(next, n)){
                return nextarr->ExecuteScript(1, gDataThis, 0, 1);
            }
        }
        else return array->ExecuteScript(i, gDataThis, 0, 1);
    }
    return 0;
}

DEF_DATA_FUNC(DataInsertElems) {
    array->Array(1)->InsertNodes(array->Int(2), array->Array(3));
    return 0;

}

DEF_DATA_FUNC(DataInsertElem) {
    DataArray* a = array->Array(1);
    int idx = array->Int(2);
    a->Insert(idx, array->Evaluate(3));
    return 0;
}

DEF_DATA_FUNC(DataPrintArray) {
    array->Array(1)->Print(TheDebug, kDataArray, false);
    return 0;
}

DEF_DATA_FUNC(DataSize) {
    if (array->Type(1) == kDataProperty) {
        MILO_ASSERT(gDataThis, 1213); // dammit hmx why couldn't it've been 1312
        return gDataThis->PropertySize(CONST_ARRAY(array)->Node(1).mValue.array); // TODO figure out what this actually is
    }
    return array->Array(1)->Size();
}

DEF_DATA_FUNC(DataRemoveElem) {
    DataArray* a = array->Array(1);
    a->Remove(array->Evaluate(2));
    return 0;
}

DEF_DATA_FUNC(DataResize) {
    array->Array(1)->Resize(array->Int(2));
    return 0;
}

DEF_DATA_FUNC(DataNewArray){
    DataNode& n = array->Evaluate(1);
    DataArrayPtr ptr;
    if(n.Type() == kDataInt){
        UNCONST_ARRAY(ptr)->Resize(n.LiteralInt());
    }
    else if(n.Type() == kDataArray){
        ptr = n.LiteralArray()->Clone(true, true, 0);
    }
    else MILO_FAIL("DataNewArray wrong argument for %s %d", array->File(), array->Line());
    return ptr;
}

DEF_DATA_FUNC(DataSetElem) {
    DataArray* aaaa = array->Array(1);
    int i = array->Int(2);
    DataNode& n = array->Evaluate(3);
    return aaaa->Node(i) = n;

}

DEF_DATA_FUNC(DataQuote) {
    return array->Node(1);
}

DEF_DATA_FUNC(DataEval) {
    return array->Evaluate(1).Evaluate();
}

inline float InverseLerp(float f1, float f2, float f3) {
    if (f2 != f1)
        return (f3 - f1) / (f2 - f1);
    else
        return 1.0f;
}

DEF_DATA_FUNC(DataReverseInterp){
    float ext = InverseLerp(array->Float(1), array->Float(2), array->Float(3));
    return Clamp(0.0f, 1.0f, ext);
}

DEF_DATA_FUNC(DataInterp) {
    float st, end, pct;
    pct = array->Float(3);
    end = array->Float(2);
    st = array->Float(1);
    return ((end - st) * pct) + st;
}

DEF_DATA_FUNC(DataInc) {
    const DataNode& n = CONST_ARRAY(array)->Node(1);
    if (n.Type() == kDataProperty) {
        MILO_ASSERT(gDataThis, 1286);
        DataArray* a = CONST_ARRAY(array)->Node(1).mValue.array;
        int x = gDataThis->Property(a, true)->Int() + 1;
        gDataThis->SetProperty(a, x);
        return x;

    } else {
        DataNode* Pn = array->Var(1);
        int i = Pn->Int();
        return *Pn = DataNode(i+1);
    }
}

DEF_DATA_FUNC(DataDec) {
    const DataNode& n = CONST_ARRAY(array)->Node(1);
    if (n.Type() == kDataProperty) {
        MILO_ASSERT(gDataThis, 1303);
        DataArray* a = CONST_ARRAY(array)->Node(1).mValue.array;
        int x = gDataThis->Property(a, true)->Int() - 1;
        gDataThis->SetProperty(a, x);
        return x;

    } else {
        DataNode* Pn = array->Var(1);
        int i = Pn->Int();
        return *Pn = DataNode(i-1);
    }
}

DEF_DATA_FUNC(DataHandleType) {
    for (int i = 1; i < array->Size(); i++) {
        DataArray* a = array->Array(i);
        Hmx::Object* o;
        DataNode& n = a->Evaluate(0);
        if (n.Type() == kDataObject) o = n.mValue.object;
        else o = gDataDir->FindObject(n.LiteralStr(array), true);
        if (o) o->HandleType(a);
    }
    return 0;
}

DEF_DATA_FUNC(DataHandleTypeRet) {
    DataArray* a = array->Array(1);
    Hmx::Object* o;
    DataNode& n = a->Evaluate(0);
    if (n.Type() == kDataObject) o = n.mValue.object;
    else o = gDataDir->FindObject(n.LiteralStr(array), true);
    if (!o) {
        class String str;
        n.Print(str, true);
        MILO_FAIL("Object %s not found (file %s, line %d)", str.c_str(), array->File(), array->Line());
    }
    return o->HandleType(a);
}

DEF_DATA_FUNC(DataExport) {
    DataArray* a = array->Array(1);
    bool i = array->Int(2);
    DataNode& n = a->Evaluate(0);
    Hmx::Object* obj;
    if (n.Type() == kDataObject) obj = n.mValue.object;
    else obj = gDataDir->FindObject(n.LiteralStr(array), true);
    if (obj) obj->Export(a, i);
    return 0;
}

DEF_DATA_FUNC(DataHandle) {
    for (int i = 1; i < array->Size(); i++) {
        DataArray* handlo = array->Array(i);
        DataNode& n = handlo->Evaluate(0);
        Hmx::Object* obj;
        if (n.Type() == kDataObject) obj = n.RawVal().object;
        else if (n.Type() == kDataInt) obj = NULL;
        else obj = gDataDir->FindObject(n.LiteralStr(array), true);
        if (obj) obj->Handle(handlo, false);
        // read->mRefs -= 1; if (read->mRefs == 0) delete read;
    }
    return 0;
}

DEF_DATA_FUNC(DataHandleRet) {
    DataArray *a = array->Array(1);
    Hmx ::Object *o;
    DataNode &n = a->Evaluate(0);
    if (n.Type() == kDataObject) o = n.RawVal().object;
    else o = gDataDir->FindObject(n.LiteralStr(array), true);
#ifdef MILO_DEBUG
    if (!o) {
        class String str;
        n.Print(str, true);
        MILO_FAIL("Object %s not found (file %s, line %d)", str.c_str(), array->File(), array->Line());
    }
#endif
    return o->Handle(a, false);
}

DEF_DATA_FUNC(DataRun) {
    const char* e = FileMakePath(FileExecRoot(), array->Str(1), NULL);
    DataArray* read = DataReadFile(e, true);
    DataNode ret;
    if (read) {
        ret = read->ExecuteScript(0, gDataThis, NULL, 1);
        read->Release();
    }
    return ret;
}

DEF_DATA_FUNC(OnReadFile) {
    DataArray* read = DataReadFile(array->Str(1), true);
    if (read == 0) {
        return 0;
    } else {
        DataNode dn(read, kDataArray);
        read->mRefs -= 1; if (read->mRefs == 0) delete read;
        return dn;
    }
}

DEF_DATA_FUNC(OnWriteFile) {
    DataArray* write_me = array->Array(2);
    DataWriteFile(array->Str(1), write_me, false);
    return 0;
}

DEF_DATA_FUNC(OnFileExists) {
    return FileExists(array->Str(1), 0);
}

DEF_DATA_FUNC(OnFileReadOnly) {
    return FileReadOnly(array->Str(1));
}

DEF_DATA_FUNC(DataExit) {
    TheDebug.Exit(0, true);
    return DataNode();
}

DEF_DATA_FUNC(DataContains) {
    DataArray* w = array->Array(1);
    DataNode& n = array->Evaluate(2);
    bool b = !w->Contains(DataNode(n.mValue.integer));
    if (b) return DataNode(kDataUnhandled, 0);
    else return 1;
}

DEF_DATA_FUNC(DataFindExists){
    DataArray* a = array->Array(1);
    for (int i = 2; i < array->Size(); i++) {
        DataNode& n = array->Evaluate(i);
        if (n.Type() == kDataInt || n.Type() == kDataSymbol) {
            a = a->FindArray(n.mValue.integer, false);
            if(!a){
                return DataNode(kDataUnhandled, 0);
            }
        }
        else {
            class String str;
            n.Print(str, true);
            MILO_FAIL("Bad key %s (file %s, line %d)", str.c_str(), array->File(), array->Line());
        }
    }
    return DataNode(a, kDataArray);
}

DEF_DATA_FUNC(DataFind) {
    DataNode ret = DataFindExists(array);
    if(ret == DataNode(kDataUnhandled, 0)){
        MILO_FAIL("Couldn't find key (file %s, line %d)", array->File(), array->Line());
    }
    return ret;
}

DEF_DATA_FUNC(DataFindObj){
    class ObjectDir* d = ObjectDir::Main();
    int i;
    for (i = 1; i < array->Size() - 1; i++) {
        DataNode& n = array->Evaluate(i);
        if(n.Type() == kDataObject) d = n.Obj<class ObjectDir>();
        else d = dynamic_cast<class ObjectDir*>(d->FindObject(n.LiteralStr(), false));
        if(!d) return d;
    }
    return d->FindObject(array->Str(i), false);
}

DEF_DATA_FUNC(DataBasename) {
    return FileGetBase(array->Str(1), NULL);
}

DEF_DATA_FUNC(DataDirname) {
    const char* s = FileGetPath(array->Str(1), NULL);
    class String str(s);
    uint x = str.find_last_of("/");
    return x != String::npos;
}

DEF_DATA_FUNC(DataHasSubStr) {
    return (int)strstr(array->Str(1), array->Str(2));
}

DEF_DATA_FUNC(DataHasAnySubStr) {
    DataArray* a = array->Array(2);
    for (int i = 0; i < a->Size(); i++) {
        const char* haystack = a->Str(i);
        if (strstr(array->Str(1), haystack)) return 1;
    }
    return 0;
}

DEF_DATA_FUNC(DataFindSubStr) {
    class String s(array->Str(1));
    return (int)s.find(array->Str(2));
}

DEF_DATA_FUNC(DataStrElem) {
    char s[2] = {'A'};
    int off = array->Int(2);
    s[0] = array->Str(1)[off];
    return (Symbol)s;
}

DEF_DATA_FUNC(DataSubStr) {
    class String s(array->Str(1));
    int i1 = array->Int(2);
    int i2 = array->Int(3);
    return s.substr(i1, i2);
}


DEF_DATA_FUNC(DataStrCat) {
    DataNode& n = *array->Var(1);
    class String s(n.Str());
    for (int i = 2; i < array->Size(); i++) {
        s += array->Str(i);
    }
    n = DataNode(s.c_str());
    return n.Str();
}

DEF_DATA_FUNC(DataStringFlags){
    int x = array->Int(1);
    DataArray* arr = array->Array(2);
    class String s("");
    for (int i = 0; i < arr->Size(); i++) {
        DataArray* macro = DataGetMacro(arr->Str(i));
        MILO_ASSERT(macro && macro->Size() == 1, 1626);
        if(x & macro->Int(0)){
            if(s != ""){
                s += "|";
            }
            s += arr->Str(i);
        }
    }
    return s;
}

DEF_DATA_FUNC(DataStrToLower) {
    class String s = array->Str(1);
    s.ToLower();
    return s;
}

DEF_DATA_FUNC(DataStrToUpper) {
    class String s = array->Str(1);
    s.ToUpper();
    return s;
}

DEF_DATA_FUNC(DataStrlen) {
    return (int)strlen(array->Str(1));
}

DEF_DATA_FUNC(DataStrieq) {
    return !stricmp(array->Str(1), array->Str(2));
}

DEF_DATA_FUNC(DataSearchReplace){
    const char* s3 = array->Str(3);
    const char* s2 = array->Str(2);
    const char* s1 = array->Str(1);
    char beeg[0x800];
    bool ret = SearchReplace(s1, s2, s3, beeg);
    *array->Var(4) = DataNode(beeg);
    return ret;
}

DEF_DATA_FUNC(DataPushBack) {
    DataArray* work = array->Array(1);
    int nu_size = work->Size();
    work->Resize(nu_size + 1);
    work->Node(nu_size) = array->Evaluate(2);
    return 0;
}

DEF_DATA_FUNC(DataSort) {
    array->Array(1)->SortNodes();
    return 0;
}

DEF_DATA_FUNC(DataGetType) {
    return array->Evaluate(1).Type();
}

DEF_DATA_FUNC(DataWith) {
    return array->ExecuteScript(2, array->GetObj(1), NULL, 1);
}

DEF_DATA_FUNC(OnSetThis) {
    // Hmx::Object* new_this;
    // new_this = array->GetObj(1);
    // // gDataThisPtr.Replace(gDataThis, new_this);
    // DataSetThis(new_this);
    gDataThisPtr.Replace(gDataThis, array->GetObj(1));
    return 0;
}

DEF_DATA_FUNC(DataMacroElem){
    DataArray* macro = DataGetMacro(array->Str(1));
    int i = array->Size() > 2 ? array->Int(2) : 0;
    MILO_ASSERT(macro && macro->Size() > i, 1748);
    return macro->Node(i);
}

DataMergeFilter::DataMergeFilter(const DataNode& node, Subdirs subs) : MergeFilter(kMerge, subs), mType(node.Type()) {
    if(mType == kDataInt) mInt = node.Int();
    else if(mType == kDataFunc) mFunc = node.Func();
    else if(mType == kDataObject) mObj = node.GetObj();
    else if(mType == kDataSymbol){
        mObj = gDataDir->FindObject(node.mValue.symbol, true);
        if(!mObj){
            const std::map<Symbol, DataFunc*>::iterator func = gDataFuncs.find(node.mValue.symbol);
            MILO_ASSERT(func != gDataFuncs.end(), 0x6ED);
            mFunc = func->second;
            mType = kDataFunc;
        }
        else mType = kDataObject;
    }
}

DEF_DATA_FUNC(DataMergeDirs) {
    DataMergeFilter filt(array->Evaluate(3), (MergeFilter::Subdirs)array->Int(4));
    MergeDirs(array->Obj<class ObjectDir>(1), array->Obj<class ObjectDir>(2), filt);
    return 0;
}

DEF_DATA_FUNC(DataReplaceObject) {
    int x, y, z;
    bool a,b,c;
    if (array->Size() > 3) x = array->Int(3);
    else x = 1;
    a = x;
    if (array->Size() > 4) y = array->Int(4);
    else y = 1;
    b = y;
    if (array->Size() > 5) y = array->Int(5);
    else z = 1;
    c = z;
    ReplaceObject(array->GetObj(1), array->GetObj(2), a, b, c);
    return 0;
}

DEF_DATA_FUNC(DataNextName) {
    class ObjectDir* d = gDataDir;
    if (array->Size() > 2) {
        d = array->Obj<class ObjectDir>(2);
    }
    return NextName(array->Str(1), d);
}

DataNode Quasiquote(const DataNode& node) {
    static Symbol unquoteAbbrev(",");
    DataType nodeType = node.Type();
    if(nodeType - 0x10 <= 1U){
        DataArray* nodeArr = node.mValue.array;
        if(nodeType == kDataCommand && nodeArr->Type(0) == kDataSymbol){
            char* str = (char*)nodeArr->Node(0).mValue.symbol;
            if(STR_TO_SYM(str) == unquote || STR_TO_SYM(str) == unquoteAbbrev){
                return nodeArr->Evaluate(1);
            }
        }
        DataArrayPtr ptr(new DataArray(nodeArr->Size()));
        for(int i = 0; i < nodeArr->Size(); i++){
            ptr.Node(i) = Quasiquote(nodeArr->Node(i));
        }
        return DataNode(UNCONST_ARRAY(ptr), nodeType);
    }
    else return node;
}

DEF_DATA_FUNC(DataQuasiquote) {
    return Quasiquote(array->Node(1));
}

DEF_DATA_FUNC(DataUnquote) {
    return array->Evaluate(1);
}

DEF_DATA_FUNC(DataGetDateTime) {
    DateTime dt;
    GetDateAndTime(dt);
    if(array->Size() > 1){
        *array->Var(1) = DataNode(dt.mYear + 1900);
    }
    if(array->Size() > 2){
        *array->Var(2) = DataNode(dt.mMonth + 1);
    }
    if(array->Size() > 3){
        *array->Var(3) = DataNode(dt.mDay);
    }
    if(array->Size() > 4){
        *array->Var(4) = DataNode(dt.mHour);
    }
    if(array->Size() > 5){
        *array->Var(5) = DataNode(dt.mMin);
    }
    if(array->Size() > 6){
        *array->Var(6) = DataNode(dt.mSec);
    }
    return (int)dt.ToCode();
}

static DataArray* sFileMsg;

bool FileListCallBack(char* s) {
    bool ret;
    DataArray* array = sFileMsg;
    DataNode* n = array->Var(3);
    DataNode n2 = *n; {DataNode n3 = s; *n = n3;}
    ret = (bool)sFileMsg->ExecuteBlock(4).Int();
    if (ret) {
        strcpy(s, n->Str());
    }
    *n = n2;
    return ret;
}

DEF_DATA_FUNC(DataFileList) {
    sFileMsg = array;
    bool (*x)(char*) = NULL;
    int i, s = array->Size();
    if (s > 3) x = (&FileListCallBack);
    if (s > 2) i = array->Int(2); else i = 1;
    return MakeFileList(array->Str(1), i, x);
}

DEF_DATA_FUNC(DataFileListPaths) {
    sFileMsg = array;
    return MakeFileListFullPath(array->Str(1));
}

DEF_DATA_FUNC(DataObjectList) {
    class ObjectDir* dir = array->Obj<class ObjectDir>(1);
    Symbol s = array->Sym(2);
    int x;
    if (array->Size() > 3) x = (bool)array->Int(3); else x = 1;
    return ObjectList(dir, s, x);
}

void ScriptDebugModal(bool&, char*, bool) { }

DECOMP_FORCEACTIVE(DataFunc, ",")

DEF_DATA_FUNC(DataDisableNotify) {
    if (array->Size() > 1) {
        TheDebug.SetDisabled(true);
        for (int i = 1; i < array->Size(); i++) {
            array->Command(i)->Execute();
        }
        TheDebug.SetDisabled(false);
    } else {
        TheDebug << MakeString("invalid # of arguments...\n");
    }
    return 0;
}

DEF_DATA_FUNC(DataFilterNotify) {
    return 0;
}

void DataInitFuncs() {
    DataRegisterFunc("replace_object", DataReplaceObject);
    DataRegisterFunc("next_name", DataNextName);
    DataRegisterFunc("printf", DataPrintf);
    DataRegisterFunc("sprintf", DataSprintf);
    DataRegisterFunc("sprint", DataSprint);
    DataRegisterFunc("func", DataFuncObj::New);
    DataRegisterFunc("elem", DataGetElem);
    DataRegisterFunc("last_elem", DataGetLastElem);
    DataRegisterFunc("foreach", DataForEach);
    DataRegisterFunc("foreach_int", DataForEachInt);
    DataRegisterFunc("min", DataMin);
    DataRegisterFunc("max", DataMax);
    DataRegisterFunc("abs", DataAbs);
    DataRegisterFunc("+", DataAdd);
    DataRegisterFunc("+=", DataAddEq);
    DataRegisterFunc("-", DataSub);
    DataRegisterFunc("-=", DataSubEq);
    DataRegisterFunc("mean", DataMean);
    DataRegisterFunc("clamp", DataClamp);
    DataRegisterFunc("clamp_eq", DataClampEq);
    DataRegisterFunc("*", DataMultiply);
    DataRegisterFunc("*=", DataMultiplyEq);
    DataRegisterFunc("/", DataDivide); // this one's strbase isn't inline with the others
    DataRegisterFunc("/=", DataDivideEq);
    DataRegisterFunc("sqrt", DataSqrt);
    DataRegisterFunc("mod", DataMod);
    DataRegisterFunc("dist", DataDist);
    DataRegisterFunc("symbol", DataSymbol);
    DataRegisterFunc("int", DataInt);
    DataRegisterFunc("char", DataChar);
    DataRegisterFunc("round", DataRound);
    DataRegisterFunc("floor", DataFloor);
    DataRegisterFunc("ceil", DataCeil);
    DataRegisterFunc("set", DataSet);
    DataRegisterFunc("if_else", DataIfElse);
    DataRegisterFunc("if", DataIf);
    DataRegisterFunc("unless", DataUnless);
    DataRegisterFunc("==", DataEq);
    DataRegisterFunc("!=", DataNe);
    DataRegisterFunc("<=", DataLe);
    DataRegisterFunc("<", DataLt);
    DataRegisterFunc(">=", DataGe);
    DataRegisterFunc(">", DataGt);
    DataRegisterFunc("!", DataNot);
    DataRegisterFunc("&&", DataAnd);
    DataRegisterFunc("||", DataOr);
    DataRegisterFunc("^^", DataXor);
    DataRegisterFunc("&", DataBitAnd);
    DataRegisterFunc("&=", DataAndEqual);
    DataRegisterFunc("mask_eq", DataMaskEqual);
    DataRegisterFunc("|", DataBitOr);
    DataRegisterFunc("|=", DataOrEqual);
    DataRegisterFunc("^", DataBitXor);
    DataRegisterFunc("~", DataBitNot);
    DataRegisterFunc("lowest_bit", DataLowestBit);
    DataRegisterFunc("count_bits", DataCountBits);
    DataRegisterFunc("while", DataWhile);
    DataRegisterFunc("do", DataDo);
    DataRegisterFunc("new", DataNew);
    DataRegisterFunc("delete", DataDelete);
    DataRegisterFunc("object", DataObject);
    DataRegisterFunc("exists", DataExists);
    DataRegisterFunc("localize", DataLocalize);
    DataRegisterFunc("localize_separated_int", DataLocalizeSeparatedInt);
    DataRegisterFunc("localize_float", DataLocalizeFloat);
    DataRegisterFunc("sync_reload_locale", DataSyncReloadLocale);
    DataRegisterFunc("print_unused", DataPrintUnused);
    DataRegisterFunc("startswith", DataStartsWith);
    DataRegisterFunc("print", DataPrint);
    DataRegisterFunc("time", DataTime);
    DataRegisterFunc("random_int", DataRandomInt);
    DataRegisterFunc("random_float", DataRandomFloat);
    DataRegisterFunc("random_elem", DataRandomElem);
    DataRegisterFunc("random", DataRandom);
    DataRegisterFunc("random_seed", DataRandomSeed);
    DataRegisterFunc("notify", DataNotify);
    DataRegisterFunc("notify_beta", DataNotifyBeta);
    DataRegisterFunc("fail", DataFail);
    DataRegisterFunc("notify_once", DataNotifyOnce);
    DataRegisterFunc("switch", DataSwitch);
    DataRegisterFunc("cond", DataCond);
    DataRegisterFunc("insert_elems", DataInsertElems);
    DataRegisterFunc("insert_elem", DataInsertElem);
    DataRegisterFunc("print_array", DataPrintArray);
    DataRegisterFunc("size", DataSize);
    DataRegisterFunc("remove_elem", DataRemoveElem);
    DataRegisterFunc("resize", DataResize);
    DataRegisterFunc("array", DataNewArray);
    DataRegisterFunc("set_elem", DataSetElem);
    DataRegisterFunc("eval", DataEval);
    DataRegisterFunc("reverse_interp", DataReverseInterp);
    DataRegisterFunc("interp", DataInterp);
    DataRegisterFunc("++", DataInc);
    DataRegisterFunc("--", DataDec);
    DataRegisterFunc("run", DataRun);
    DataRegisterFunc("read_file", OnReadFile);
    DataRegisterFunc("write_file", OnWriteFile);
    DataRegisterFunc("file_exists", OnFileExists);
    DataRegisterFunc("file_read_only", OnFileReadOnly);
    DataRegisterFunc("handle_type", DataHandleType);
    DataRegisterFunc("handle_type_ret", DataHandleTypeRet);
    DataRegisterFunc("handle", DataHandle);
    DataRegisterFunc("handle_ret", DataHandleRet);
    DataRegisterFunc("contains", DataContains);
    DataRegisterFunc("export", DataExport);
    DataRegisterFunc("exit", DataExit);
    DataRegisterFunc("find", DataFind);
    DataRegisterFunc("find_exists", DataFindExists);
    DataRegisterFunc("find_elem", DataFindElem);
    DataRegisterFunc("find_obj", DataFindObj);
    DataRegisterFunc("basename", DataBasename);
    DataRegisterFunc("dirname", DataDirname);
    DataRegisterFunc("has_substr", DataHasSubStr);
    DataRegisterFunc("has_any_substr", DataHasAnySubStr);
    DataRegisterFunc("find_substr", DataFindSubStr);
    DataRegisterFunc("strlen", DataStrlen);
    DataRegisterFunc("str_elem", DataStrElem);
    DataRegisterFunc("search_replace", DataSearchReplace);
    DataRegisterFunc("substr", DataSubStr);
    DataRegisterFunc("strcat", DataStrCat);
    DataRegisterFunc("string_flags", DataStringFlags);
    DataRegisterFunc("tolower", DataStrToLower);
    DataRegisterFunc("toupper", DataStrToUpper);
    DataRegisterFunc("strieq", DataStrieq);
    DataRegisterFunc("push_back", DataPushBack);
    DataRegisterFunc("sort", DataSort);
    DataRegisterFunc("var", DataVar);
    DataRegisterFunc("set_var", DataSetVar);
    DataRegisterFunc("pack_color", DataPackColor);
    DataRegisterFunc("unpack_color", DataUnpackColor);
    DataRegisterFunc("set_this", OnSetThis);
    DataRegisterFunc("macro_elem", DataMacroElem);
    DataRegisterFunc("merge_dirs", DataMergeDirs);
    DataRegisterFunc("quote", DataQuote); DataRegisterFunc("'", DataQuote);
    DataRegisterFunc("quasiquote", DataQuasiquote); DataRegisterFunc("`", DataQuasiquote);
    DataRegisterFunc("unquote", DataUnquote); DataRegisterFunc(",", DataUnquote);
    DataRegisterFunc("get_date_time", DataGetDateTime);
    DataRegisterFunc("with", DataWith);
    DataRegisterFunc("type", DataGetType);
    DataRegisterFunc("object_list", DataObjectList);
    DataRegisterFunc("file_list", DataFileList);
    DataRegisterFunc("file_list_paths", DataFileListPaths);
    DataRegisterFunc("disable_notify", DataDisableNotify);
    DataRegisterFunc("filter_notify", DataFilterNotify);
    // key deriv dta
    char magic[8];
    memset(magic, 0, 8);
    magic[0] = 'O';
    magic[1] = '6';
    magic[2] = '4';
    DataRegisterFunc(magic, DataWhile);
    magic[2] = '5';
    DataRegisterFunc(magic, DataSize);
    magic[2] = '6';
    DataRegisterFunc(magic, DataSwitch);
    magic[2] = '7';
    DataRegisterFunc(magic, DataGetElem);
    magic[2] = '8';
    DataRegisterFunc(magic, DataDo);
    magic[2] = '9';
    DataRegisterFunc(magic, DataSet);
    magic[1] = '7';
    magic[2] = '0';
    DataRegisterFunc(magic, DataInc);
}

void DataTermFuncs(){
    gDataFuncs.clear();
}

Symbol DataFuncName(DataFunc* func){
    for(std::map<Symbol, DataFunc*>::iterator it = gDataFuncs.begin(); it != gDataFuncs.end(); it++ ){
        if(it->second == func){
            return it->first;
        }
    }
    return Symbol("");
}

// Force FilterSubdir to generate here
DECOMP_FORCEFUNC(DataFunc, MergeFilter, FilterSubdir(0, 0))

MergeFilter::Action DataMergeFilter::Filter(Hmx::Object* from, Hmx::Object* to, class ObjectDir* dir){
    if(mType == kDataInt){
        return (MergeFilter::Action)mInt;
    }
    else {
        static DataArrayPtr d(new DataArray(3));
        d.Node(1) = DataNode(from);
        d.Node(2) = DataNode(to);
        if(mType == kDataFunc){
            return (MergeFilter::Action) mFunc(UNCONST_ARRAY(d)).Int();
        }
        else return (MergeFilter::Action) mObj->Handle(UNCONST_ARRAY(d), true).Int();
    }
}
