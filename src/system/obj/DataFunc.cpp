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
#include "macros.h"
#include "math/MathFuncs.h"
#include "obj/DataUtl.h"
#include "utl/Locale.h"
#include <cstring>
#include <list>
#include <map>
#include <stdlib.h>

std::map<Symbol, DataFunc*> gDataFuncs;
DataThisPtr gDataThisPtr;

extern Hmx::Object *gDataThis;
extern ObjectDir* gDataDir;

#define DefDataFunc(name, code) \
static DataNode Data##name(DataArray* da) code

ADD_NOTIFS

static void mfdtor(){
    MergeFilter mf;
}

void DataRegisterFunc(Symbol s, DataFunc* func){
    const std::map<Symbol, DataFunc*>::iterator it = gDataFuncs.find(s);
    if(it != gDataFuncs.end() && it->second != func)
        MILO_FAIL("Can't register different func %s", s);
    gDataFuncs[s] = func;
}

DataNode DataFuncObj::New(DataArray* arr){
    Hmx::Object* o = ObjectDir::Main()->FindObject(arr->Str(1), false);
    if(o) delete o;
    return DataNode(new (_PoolAlloc(0x20, 0x20, FastPool)) DataFuncObj(arr));
}

DefDataFunc(Sprintf, {
    FormatString fs(da->Str(1));
    for (int i = 2; i < da->Size(); i++) {
        fs << da->Evaluate(i);
    }
    return DataNode(fs.Str());
})

static DataNode DataPrintf(DataArray *da) {
    FormatString fs(da->Str(1));
    for (int i = 2; i < da->Size(); i++) {
        fs << da->Evaluate(i);
    }
    TheDebug << fs.Str();
    return DataNode(0);
}

static DataNode DataPrint(DataArray *da) {
    for (int i = 1; i < da->Size(); i++) {
        da->Evaluate(i).Print(TheDebug, true);
    }
    return DataNode(0);
}

static DataNode DataSprint(DataArray *da) {
    String str;
    for (int i = 1; i < da->Size(); i++) {
        da->Evaluate(i).Print(str, true);
    }
    return DataNode(str.c_str());
}

static DataNode DataSet(DataArray *da) {
    const DataArray* a = da;
    DataNode ret(a->Evaluate(2));
    if (a->Type(1) == kDataProperty) {
        MILO_ASSERT(gDataThis, 0x9D);
        gDataThis->SetProperty(a->Node(1).mValue.array, ret);
    }
    else *a->Var(1) = ret;
    return ret;
}

static DataNode DataSetVar(DataArray *da) {
    DataNode ret = da->Evaluate(2);
    *DataVariable(da->ForceSym(1)) = ret;
    return ret;
}

static DataNode DataIfElse(DataArray *da) {
    if(da->Size() != 4) MILO_FAIL("One condition and two alternatives expected (file %s, line %d)", da->File(), da->Line());
    if(da->Node(1).NotNull())
        return DataNode(da->Evaluate(2));
    else return DataNode(da->Evaluate(3));
}

static DataNode DataIf(DataArray *da) {
    if (da->Node(1).NotNull()) {
        for (int i = 2; i < da->Size(); i++) {
            da->Command(i)->Execute();
        }
        return DataNode(0);
    } else
        return DataNode(0);
}

static DataNode DataUnless(DataArray* da){
    bool fart = !da->Node(1).NotNull();
    if(fart){
        for(int i = 2; i < da->Size(); i++){
            da->Command(i)->Execute();
        }
        return DataNode(0);
    }
    return DataNode(0);
}

static DataNode DataEq(DataArray *da) {
    DataNode *dn1 = &da->Evaluate(1);
    DataNode *dn2 = &da->Evaluate(2);
    return DataNode(dn1->operator==(*dn2));
}

static DataNode DataFindElem(DataArray *da) {
    DataArray *arr = da->Array(1);
    arr->AddRef();
    DataNode *dn = &da->Evaluate(2);
    for (int i = 0; i < arr->Size(); i++) {
        if (!(arr->Node(i).operator==(*dn)))
            continue;
        if (da->Size() > 3) {
            da->Var(3)->operator=(DataNode(i));
        }
        arr->Release();
        return DataNode(1);
    }
    arr->Release();
    return DataNode(0);
}

static DataNode DataNe(DataArray* da){
    return DataNode(DataEq(da).mValue.integer == 0);
}

static DataNode DataLe(DataArray *da) {
    return DataNode(da->Float(1) <= da->Float(2));
}

static DataNode DataLt(DataArray *da) {
    return DataNode(da->Float(1) < da->Float(2));
}

static DataNode DataGe(DataArray *da) {
    return DataNode(da->Float(1) >= da->Float(2));
}

static DataNode DataGt(DataArray *da) {
    return DataNode(da->Float(1) > da->Float(2));
}

static DataNode DataNot(DataArray *da) {
    bool ret = !da->Node(1).NotNull();
    return DataNode(ret);
}

static DataNode DataAnd(DataArray *da) {
    for (int i = 1; i < da->Size(); i++) {
        bool ret = !da->Node(i).NotNull();
        if (ret) {
            return DataNode(0);
        }
    }
    return DataNode(1);
}

static DataNode DataOr(DataArray *da) {
    for (int i = 1; i < da->Size(); i++) {
        if(da->Node(i).NotNull())
            return DataNode(1);
    }
    return DataNode(0);
}

static DataNode DataXor(DataArray *da) {
    return DataNode(da->Node(1).NotNull() != da->Node(2).NotNull());
}

static DataNode DataBitAnd(DataArray *array) {
    MILO_ASSERT(array->Size() >= 3, 0x130);
    int res = array->Int(1);
    for (int i = 2; i < array->Size(); i++) {
        res &= array->Int(i);
    }
    return DataNode(res);
}

static DataNode DataAndEqual(DataArray* array){
    MILO_ASSERT(array->Size() == 3, 0x13C);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x141);
        DataArray* arr = ((const DataArray*)array)->Node(1).mValue.array;
        int res = gDataThis->Property(arr, true)->Int(0) & array->Int(2);
        gDataThis->SetProperty(arr, DataNode(res));
        return DataNode(res);
    }
    else {
        DataNode* var = array->Var(1);
        int res = var->Int(0) & array->Int(2);
        return (*var = DataNode(res));
    }
}

static DataNode DataMaskEqual(DataArray* array){
    MILO_ASSERT(array->Size() == 3, 0x152);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x157);
        DataArray* arr = ((const DataArray*)array)->Node(1).mValue.array;
        int res = gDataThis->Property(arr, true)->Int(0) & ~array->Int(2);
        gDataThis->SetProperty(arr, DataNode(res));
        return DataNode(res);
    }
    else {
        DataNode* var = array->Var(1);
        int res = var->Int(0) & ~array->Int(2);
        return (*var = DataNode(res));
    }
}

static DataNode DataOrEqual(DataArray* array){
    MILO_ASSERT(array->Size() == 3, 0x169);
    if(array->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x16E);
        DataArray* arr = ((const DataArray*)array)->Node(1).mValue.array;
        int res = gDataThis->Property(arr, true)->Int(0) | array->Int(2);
        gDataThis->SetProperty(arr, DataNode(res));
        return DataNode(res);
    }
    else {
        DataNode* var = array->Var(1);
        int res = var->Int(0) | array->Int(2);
        return (*var = DataNode(res));
    }
}

static DataNode DataBitOr(DataArray* array){
    MILO_ASSERT(array->Size() >= 3, 0x180);
    int res = array->Int(1);
    for(int i = 2; i < array->Size(); i++)
        res |= array->Int(i);
    return DataNode(res);
}

static DataNode DataBitXor(DataArray* da){
    return DataNode(da->Int(1) ^ da->Int(2));
}

static DataNode DataBitNot(DataArray* da){
    return DataNode(~da->Int(1));
}

static DataNode DataLowestBit(DataArray *da) {
    int num = da->Int(1);
    int res;
    if(num == 0) res = 0;
    else {
        int j = 1;
        while(!(j & num))
            j *= 2;
        res = j;
    }
    return DataNode(res);
}

static DataNode DataCountBits(DataArray *da) {
    return DataNode(CountBits(da->Int(1)));
}

static DataNode DataWhile(DataArray* da){
    while(da->Node(1).NotNull()){
        for(int i = 2; i < da->Size(); i++){
            da->Command(i)->Execute();
        }
    }
    return DataNode(0);
}

static DataNode DataVar(DataArray* da){
    return DataNode(DataVariable(da->ForceSym(1)));
}

static DataNode DataPackColor(DataArray *da) {
    return DataNode(
        ((int)(da->Float(3) * 255.0f) & 0xFF) << 0x10
        | ((int)(da->Float(2) * 255.0f) & 0xFF) << 8
        | ((int)(da->Float(1) * 255.0f) & 0xFF)
    );
}

static DataNode DataUnpackColor(DataArray *da) {
    int packed = da->Int(1);
    *da->Var(2) = DataNode((float)(packed & 0xFF) / 255.0f);
    *da->Var(3) = DataNode((float)(packed >> 8 & 0xFF) / 255.0f);
    *da->Var(4) = DataNode((float)(packed >> 0x10 & 0xFF) / 255.0f);
    return DataNode(0);
}

static DataNode DataDo(DataArray* da){
    int cnt;
    int nodeCnt = da->Size();
    for(cnt = 1; da->Type(cnt) == kDataArray; cnt++){
        DataArray* arr = da->Node(cnt).mValue.array;
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
        da->Command(cnt)->Execute();
    DataNode ret(da->Evaluate(cnt));
    while(delCnt-- != 0) DataPopVar();
    return ret;
}

static DataNode DataMin(DataArray* da){
    DataNode& n1 = da->Evaluate(1);
    DataNode& n2 = da->Evaluate(2);
    if(n1.Type() == kDataFloat || n2.Type() == kDataFloat){
        return DataNode(Minimum<float>(n1.LiteralFloat(da), n2.LiteralFloat(da)));
    }
    else {
        return DataNode(Minimum<int>(n2.LiteralInt(da), n1.LiteralInt(da)));
    }
}

static DataNode DataMax(DataArray* da){
    DataNode& n1 = da->Evaluate(1);
    DataNode& n2 = da->Evaluate(2);
    if(n1.Type() == kDataFloat || n2.Type() == kDataFloat){
        return DataNode(Max<float>(n1.LiteralFloat(da), n2.LiteralFloat(da)));
    }
    else {
        return DataNode(Max<int>(n2.LiteralInt(da), n1.LiteralInt(da)));
    }
}

static DataNode DataAbs(DataArray* da){
    DataNode& n = da->Evaluate(1);
    float f = fabs_f(n.LiteralFloat(da));
    if(n.Type() == kDataInt)
        return DataNode((int)f);
    else return DataNode(f);
}

static DataNode DataAdd(DataArray *da) {
    float sum_f = 0.0f;
    int sum_int = 0;
    int cnt = da->Size();
    int i;
    for (i = 1; i < cnt; i++) {
        DataNode& n = da->Evaluate(i);
        if(n.Type() != kDataInt){
            sum_f = sum_int + n.LiteralFloat(da);
            break;
        }
        sum_int += n.mValue.integer;
    }
    if (i == cnt)
        return DataNode(sum_int);
    for (i++; i < cnt; i++) {
        sum_f += da->Float(i);
    }
    return DataNode(sum_f);
}

static DataNode DataAddEq(DataArray* da){
    DataNode ret = DataAdd(da);
    if(da->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x223);
        gDataThis->SetProperty(((const DataArray*)da)->Node(1).mValue.array, ret);
    }
    else *da->Var(1) = ret;
    return ret;
}

static DataNode DataSub(DataArray *da) {
    DataNode& dn = da->Evaluate(1);
    if (da->Size() == 2) {
        if (dn.Type() == kDataFloat) {
            return DataNode(-dn.LiteralFloat(da));
        } else
            return DataNode(-dn.LiteralInt(da));
    } else {
        DataNode& dn2 = da->Evaluate(2);
        if (dn.Type() == kDataFloat || dn2.Type() == kDataFloat) {
            return DataNode(dn.LiteralFloat(da) - dn2.LiteralFloat(da));
        } else {
            return DataNode(dn.LiteralInt(da) - dn2.LiteralInt(da));
        }
    }
}

static DataNode DataMean(DataArray *da) {
    float sum = 0.0;
    int cnt = da->Size();
    for (int i = 1; i < cnt; i++) {
        sum += da->Float(i);
    }
    return DataNode(sum / (cnt - 1));
}

static DataNode DataClamp(DataArray *da) {
    DataNode& dn1 = da->Evaluate(1);
    DataNode& dn2 = da->Evaluate(2);
    DataNode& dn3 = da->Evaluate(3);
    if(dn1.Type() == kDataFloat || dn2.Type() == kDataFloat || dn3.Type() == kDataFloat){
        return DataNode(Clamp<float>(dn1.LiteralFloat(da), dn2.LiteralFloat(da), dn3.LiteralFloat(da)));
    }
    else return DataNode(Clamp<int>(dn1.LiteralInt(da), dn2.LiteralInt(da), dn3.LiteralInt(da)));
}

static DataNode DataSubEq(DataArray* da){
    DataNode ret = DataSub(da);
    if(da->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x259);
        gDataThis->SetProperty(((const DataArray*)da)->Node(1).mValue.array, ret);
    }
    else *da->Var(1) = ret;
    return ret;
}

static DataNode DataClampEq(DataArray* da){
    DataNode ret = DataClamp(da);
    if(da->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x260);
        gDataThis->SetProperty(((const DataArray*)da)->Node(1).mValue.array, ret);
    }
    else *da->Var(1) = ret;
    return ret;
}

static DataNode DataMultiply(DataArray* da){
    DataNode& dn1 = da->Evaluate(1);
    DataNode& dn2 = da->Evaluate(2);
    if(dn1.Type() == kDataFloat || dn2.Type() == kDataFloat){
        return DataNode(dn1.LiteralFloat(da) * dn2.LiteralFloat(da));
    }
    else return DataNode(dn1.LiteralInt(da) * dn2.LiteralInt(da));
}

static DataNode DataMultiplyEq(DataArray* da){
    DataNode ret = DataMultiply(da);
    if(da->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x272);
        gDataThis->SetProperty(((const DataArray*)da)->Node(1).mValue.array, ret);
    }
    else *da->Var(1) = ret;
    return ret;
}

static DataNode DataDivide(DataArray* da){
    return DataNode(da->Float(1) / da->Float(2));
}

static DataNode DataDivideEq(DataArray* da){
    DataNode ret = DataDivide(da);
    if(da->Type(1) == kDataProperty){
        MILO_ASSERT(gDataThis, 0x27E);
        gDataThis->SetProperty(((const DataArray*)da)->Node(1).mValue.array, ret);
    }
    else *da->Var(1) = ret;
    return ret;
}

static DataNode DataSqrt(DataArray* da){
    return DataNode(sqrt(da->Float(1)));
}

DefDataFunc(Mod, {
    DataNode &n1 = da->Evaluate(1);
    DataNode &n2 = da->Evaluate(2);
    if (n1.Type() == kDataFloat || n2.Type() == kDataFloat)
        return DataNode(Mod(n1.LiteralFloat(da), n2.LiteralFloat(da)));
    else
        return DataNode(Mod(n1.LiteralInt(da), n2.LiteralInt(da)));
})

// // fn_8031D490
// DataNode DataMod(DataArray *da) {
//     DataNode *dn1 = &da->Evaluate(1);
//     DataNode *dn2 = &da->Evaluate(2);
//     if (dn1->Type() == kDataFloat || dn2->Type() == kDataFloat) {
//         return DataNode(Modulo(dn1->LiteralFloat(da), dn2->LiteralFloat(da)));
//     } else
//         return DataNode(Modulo(dn1->LiteralInt(da), dn2->LiteralInt(da)));
// }

static DataNode DataDist(DataArray *da) {
    float x, y, z;

    z = da->Float(3) - da->Float(6);
    y = da->Float(2) - da->Float(5);
    x = da->Float(1) - da->Float(4);
    return DataNode(sqrt(x*x+y*y+z*z));
}

static DataNode DataSymbol(DataArray* da){
    return DataNode(da->ForceSym(1));
}

static DataNode DataChar(DataArray* da){
    static char newChar[2];
    DataNode& n = da->Evaluate(1);
    newChar[0] = n.Int(0);
    newChar[1] = '\0';
    return DataNode(newChar);
}

static DataNode DataInt(DataArray* da){
    DataNode& n = da->Evaluate(1);
    if(n.Type() == kDataSymbol)
        return DataNode(atoi(n.mValue.symbol));
    else if(n.Type() == kDataObject || n.Type() == kDataInt)
        return DataNode(n.mValue.integer);
    else return DataNode((int)n.LiteralFloat(da));
}

static DataNode DataRound(DataArray* da){
    return DataNode(Round(da->Evaluate(1).LiteralFloat(0)));
}

static DataNode DataFloor(DataArray* da){
    return DataNode(floor_f(da->Float(1)));
}

static DataNode DataCeil(DataArray* da){
    return DataNode(ceil_f(da->Float(1)));
}

static DataNode DataDelete(DataArray* da){
    Hmx::Object* obj = da->GetObj(1);
    delete obj;
    return DataNode(0);
}

static DataNode DataNew(DataArray* da){
    Hmx::Object* obj = Hmx::Object::NewObject(da->Sym(1));
    if(da->Size() > 2){
        if(da->Type(2) == kDataArray){
            obj->SetTypeDef(da);
        }
        else {
            obj->SetName(da->Str(2), gDataDir);
            if(da->Size() > 3){
                if(da->Type(3) == kDataArray){
                    obj->SetTypeDef(da);
                }
                else {
                    obj->SetType(da->Sym(3));
                }
            }
        }
    }
    return DataNode(obj);
}

static DataNode DataForEach(DataArray *da) {
    DataArray *arr = da->Array(2);
    arr->AddRef();
    DataNode *var = da->Var(1);
    DataNode lol(*var);
    for (int i = 0; i < arr->Size(); i++) {
        *var = arr->Evaluate(i);
        for (int j = 3; j < da->Size(); j++) {
            da->Command(j)->Execute();
        }
    }
    *var = lol;
    arr->Release();
    return DataNode(0);
}

static DataNode DataForEachInt(DataArray *da) {
    DataNode *var = da->Var(1);
    int i2 = da->Int(2);
    int i3 = da->Int(3);
    int r31 = -1;
    if (i2 > i3)
        r31 = 1;
    DataNode idk(*var);
    while (i2 != i3) {
        *var = DataNode(i2);
        for (int cnt = 4; cnt < da->Size(); cnt++) {
            da->Command(cnt)->Execute();
        }
        i2 = var->mValue.integer + r31;
    }
    *var = idk;
    return DataNode(0);
}

static DataNode DataGetElem(DataArray *da) {
    int i = da->Int(2);
    DataArray *a = da->Array(1);
    return DataNode(a->Node(i));
}

static DataNode DataGetLastElem(DataArray *da) {
    DataArray *arr = da->Array(1);
    MILO_ASSERT(arr->Size() > 0, 0x3A8);
    return DataNode(arr->Node(arr->Size() - 1));
}

DefDataFunc(Object, {
    DataNode& n = da->Evaluate(1);
    if (n.Type() == kDataObject) return n;
    else {
        const char* s = n.LiteralStr(da);
        Hmx::Object* o = gDataDir->FindObject(s, true);
        if (!o && s[0]) {
            MILO_FAIL(kNotObjectMsg, s, PathName(gDataDir) ? PathName(gDataDir) : "**no file**");
        }
        return DataNode(o);
    }
})

static DataNode DataExists(DataArray* da){
    const char* s = da->Str(1);
    bool does_exist = gDataDir->FindObject(s, true);
    if (!does_exist) {
        Symbol sym(s);
        std::map<Symbol, DataFunc*>::iterator it = gDataFuncs.find(sym);
        does_exist = it != gDataFuncs.end();
    }
    return DataNode(does_exist);
}

static DataNode DataLocalize(DataArray* da){
    const char* loc = Localize(da->ForceSym(1), false);
    const char* ret = (loc) ? loc : gNullStr;
    return DataNode(ret);
}

static DataNode DataLocalizeSeparatedInt(DataArray* da){
    return DataNode(LocalizeSeparatedInt(da->Int(1)));
}

static DataNode DataLocalizeFloat(DataArray* da){
    return DataNode(LocalizeFloat(da->Str(1), da->Float(2)));
}

static DataNode DataSyncReloadLocale(DataArray* da){
    SyncReloadLocale();
    return DataNode(1);
}

static DataNode DataPrintUnused(DataArray* da){
    return DataNode(SystemConfig(da->Sym(1))->PrintUnused(TheDebug, kDataArray, true));
}

static DataNode DataStartsWith(DataArray *da) {
    return DataNode(!strncmp(da->Str(1), da->Str(2), (da->Size() > 3) ? da->Int(3) : strlen(da->Str(2))));
}

DefDataFunc(Time, {
    int i;
    for (i = 1; i < da->Size(); i++) {
        if (da->Node(i).Type() == kDataCommand) break;
        da->Node(i).Print(TheDebug, true);
    }
    if (i == 1) TheDebug << MakeString("Timing %s, line %d:", da->File(), da->Line());
    Timer time;
    time.Start();
    for (; i < da->Size();) {
        da->Command(i++)->Execute();
    }
    time.Split();
    TheDebug << MakeString(" %f ms\n", time.Ms());
    return DataNode(time.Ms());
});

static DataNode DataRandomInt(DataArray *da) {
    return DataNode(RandomInt(da->Int(1), da->Int(2)));
}

static DataNode DataRandomFloat(DataArray *da) {
    if (da->Size() > 1) {
        return DataNode(RandomFloat(da->Float(1), da->Float(2)));
    } else
        return DataNode(RandomFloat());
}

static DataNode DataRandomElem(DataArray *da) {
    DataArray *a = da->Array(1);
    MILO_ASSERT_FMT(a->Size() != 0, "Empty array (file %s, line %d)", a->File(), a->Line());
    return DataNode(a->Node(RandomInt(0, a->Size())));
}

static DataNode DataRandom(DataArray *da) {
    return DataNode(da->Evaluate(RandomInt(1, da->Size())));
}

static DataNode DataRandomSeed(DataArray *da) {
    SeedRand(da->Int(1));
    return DataNode(0);
}

static DataNode DataNotify(DataArray* da){
    String str;
    for(int i = 1; i < da->Size(); i++){
        da->Evaluate(i).Print(str, true);
    }
    TheDebug.Notify(str.c_str());
    return DataNode(0);
}

static DataNode DataNotifyBeta(DataArray* da) {
    String s;
    for (int i = 1; i < da->Size(); i++) {
        da->Evaluate(i).Print(s, true);
    }
    TheDebug << MakeString(s.c_str());
    return DataNode();
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

static DataNode DataFail(DataArray* da){
    String str;
    for(int i = 1; i < da->Size(); i++){
        da->Evaluate(i).Print(str, true);
    }
    TheDebug << MakeString("%d\n", da->Line());
    TheDebug.Fail(str.c_str());
    return DataNode(0);
}

static DataNode DataNotifyOnce(DataArray *da) {
    String s;
    for (int i = 1; i < da->Size(); i++) {
        da->Evaluate(i).Print(s, true);
    }
    static DebugNotifyOncer _dw;
    const char *ms = MakeString(s.c_str());
    if (AddToNotifies(ms, _dw.mNotifies))
        TheDebug.Notify(ms);
    return DataNode();
}

static DataNode DataCond(DataArray* da){
    for(int i = 1; i < da->Size(); i++){
        DataNode& node = da->Node(i);
        if(node.Type() == kDataArray){
            DataArray* arr = node.mValue.array;
            if(arr->Node(0).NotNull()){
                return arr->ExecuteScript(1, gDataThis, 0, 1);
            }
        }
        else return da->ExecuteScript(i, gDataThis, 0, 1);
    }
    return DataNode(0);
}

inline bool DNArrayNodeEquals(DataNode& dn1, DataNode& dn2) {
    if (dn1.Type() == kDataArray) {
        void *arr = dn1.mValue.array;
        for (int i = 0; i < ((DataArray *)arr)->Size(); i++) {
            if ((((DataArray *)arr)->Node(i)) == dn2) {
                return true;
            }
        }
        return false;
    } else return dn1 == dn2;
}

static DataNode DataSwitch(DataArray* da){
    DataNode& n = da->Evaluate(1);
    for (int i = 2; i < da->Size(); i++) {
        DataNode& work = da->Node(i);
        if(work.Type() == kDataArray){
            DataArray* nextarr = work.mValue.array;
            DataNode& next = nextarr->Node(0);
            if(DNArrayNodeEquals(next, n)){
                return nextarr->ExecuteScript(1, gDataThis, 0, 1);
            }
        }
        else return da->ExecuteScript(i, gDataThis, 0, 1); 
    }
    return DataNode(0);
}

static DataNode DataInsertElems(DataArray* da) {
    da->Array(1)->InsertNodes(da->Int(2), da->Array(3));
    return DataNode();

}

static DataNode DataInsertElem(DataArray* da) {
    DataArray* a = da->Array(1);
    int idx = da->Int(2);
    a->Insert(idx, da->Evaluate(3));
    return DataNode();
}

static DataNode DataPrintArray(DataArray* da) {
    da->Array(1)->Print(TheDebug, kDataArray, false);
    return DataNode();
}

static DataNode DataSize(DataArray* da) {
    if (da->Type(1) == kDataProperty) {
        MILO_ASSERT(gDataThis, 1213); // dammit hmx why couldn't it've been 1312
        return DataNode(gDataThis->PropertySize(CONST_ARRAY(da)->Node(1).mValue.array)); // TODO figure out what this actually is
    }
    return DataNode(da->Array(1)->Size());
}

static DataNode DataRemoveElem(DataArray* da) {
    DataArray* a = da->Array(1);
    a->Remove(da->Evaluate(2));
    return DataNode();
}

static DataNode DataResize(DataArray* da) {
    da->Array(1)->Resize(da->Int(2));
    return DataNode();
}

static DataNode DataNewArray(DataArray* da){
    DataNode& n = da->Evaluate(1);
    DataArrayPtr ptr;
    if(n.Type() == kDataInt){
        UNCONST_ARRAY(ptr)->Resize(n.LiteralInt(0));
    }
    else if(n.Type() == kDataArray){
        ptr = n.LiteralArray(0)->Clone(true, true, 0);
    }
    else MILO_FAIL("DataNewArray wrong argument for %s %d", da->File(), da->Line());
    return DataNode(ptr);
}

static DataNode DataSetElem(DataArray* da) {
    DataArray* aaaa = da->Array(1);
    int i = da->Int(2);
    DataNode& n = da->Evaluate(3);
    return aaaa->Node(i) = n;

}

static DataNode DataQuote(DataArray* da) {
    return da->Node(1);
}

static DataNode DataEval(DataArray* da) {
    return da->Evaluate(1).Evaluate();
}

inline float InverseLerp(float f1, float f2, float f3) {
    if (f2 != f1)
        return (f3 - f1) / (f2 - f1);
    else
        return 1.0f;
}

static DataNode DataReverseInterp(DataArray* da){
    float ext = InverseLerp(da->Float(1), da->Float(2), da->Float(3));
    return DataNode(Clamp(0.0f, 1.0f, ext));
}

static DataNode DataInterp(DataArray* da) {
    float st, end, pct;
    pct = da->Float(3);
    end = da->Float(2);
    st = da->Float(1);
    return DataNode(((end - st) * pct) + st);
}

static DataNode DataInc(DataArray* da) {
    const DataNode& n = CONST_ARRAY(da)->Node(1);
    if (n.Type() == kDataProperty) {
        MILO_ASSERT(gDataThis, 1286);
        DataArray* a = CONST_ARRAY(da)->Node(1).mValue.array;
        int x = gDataThis->Property(a, true)->Int(NULL) + 1;
        gDataThis->SetProperty(a, x);
        return DataNode(x);

    } else {
        DataNode* Pn = da->Var(1);
        int i = Pn->Int(NULL);
        return DataNode(*Pn = DataNode(i+1));
    }
}

DefDataFunc(Dec, {
    const DataNode& n = CONST_ARRAY(da)->Node(1);
    if (n.Type() == kDataProperty) {
        MILO_ASSERT(gDataThis, 1303);
        DataArray* a = CONST_ARRAY(da)->Node(1).mValue.array;
        int x = gDataThis->Property(a, true)->Int(NULL) - 1;
        gDataThis->SetProperty(a, x);
        return DataNode(x);

    } else {
        DataNode* Pn = da->Var(1);
        int i = Pn->Int(NULL);
        return DataNode(*Pn = DataNode(i-1));
    }
})

DefDataFunc(HandleType, {
    for (int i = 1; i < da->Size(); i++) {
        DataArray* a = da->Array(i);
        Hmx::Object* o;
        DataNode& n = a->Evaluate(0);
        if (n.Type() == kDataObject) o = n.mValue.object;
        else o = gDataDir->FindObject(n.LiteralStr(da), true);
        if (o) o->HandleType(a);
    }
    return DataNode();
})

DefDataFunc(HandleTypeRet, {
    DataArray* a = da->Array(1);
    Hmx::Object* o;
    DataNode& n = a->Evaluate(0);
    if (n.Type() == kDataObject) o = n.mValue.object;
    else o = gDataDir->FindObject(n.LiteralStr(da), true);
    if (!o) {
        String str;
        n.Print(str, true);
        MILO_FAIL("Object %s not found (file %s, line %d)", str.c_str(), da->File(), da->Line());
    }
    return o->HandleType(a);
})

DefDataFunc(Export, {
    DataArray* a = da->Array(1);
    bool i = da->Int(2);
    DataNode& n = a->Evaluate(0);
    Hmx::Object* obj;
    if (n.Type() == kDataObject) obj = n.mValue.object;
    else obj = gDataDir->FindObject(n.LiteralStr(da), true);
    if (obj) obj->Export(a, i);
    return DataNode();
})

static DataNode DataHandle(DataArray* da) {
    for (int i = 1; i < da->Size(); i++) {
        DataArray* handlo = da->Array(i);
        DataNode& n = handlo->Evaluate(0);
        Hmx::Object* obj;
        if (n.Type() == kDataObject) obj = n.mValue.object;
        else if (n.Type() == kDataInt) obj = NULL;
        else obj = gDataDir->FindObject(n.LiteralStr(da), true);
        if (obj) obj->Handle(handlo, false);
        // read->mRefs -= 1; if (read->mRefs == 0) delete read;
    }
    return DataNode(0);
}

DefDataFunc(HandleRet, {
    DataArray* a = da->Array(1);
    Hmx::Object* o;
    DataNode& n = a->Evaluate(0);
    if (n.Type() == kDataObject) o = n.mValue.object;
    else o = gDataDir->FindObject(n.LiteralStr(da), true);
    if (!o) {
        String str;
        n.Print(str, true);
        MILO_FAIL("Object %s not found (file %s, line %d)", str.c_str(), da->File(), da->Line());
    }
    return o->Handle(a, false);
})

static DataNode DataRun(DataArray* da) {
    const char* e = FileMakePath(FileExecRoot(), da->Str(1), NULL);
    DataArray* read = DataReadFile(e, true);
    DataNode ret;
    if (read) {
        ret = read->ExecuteScript(0, gDataThis, NULL, 1);
        read->mRefs -= 1; if (read->mRefs == 0) delete read;
    }
    return ret;
}

static DataNode OnReadFile(DataArray* da) {
    DataArray* read = DataReadFile(da->Str(1), true);
    if (read == 0) return DataNode();
    else {
        DataNode dn(read, kDataArray);
        read->mRefs -= 1; if (read->mRefs == 0) delete read;
        return dn;
    }
}

static DataNode OnWriteFile(DataArray* da) {
    DataArray* write_me = da->Array(2);
    DataWriteFile(da->Str(1), write_me, false);
    return DataNode();
}

static DataNode OnFileExists(DataArray* da) {
    return DataNode(FileExists(da->Str(1), 0));
}

static DataNode OnFileReadOnly(DataArray* da) {
    return DataNode(FileReadOnly(da->Str(1)));
}

static DataNode DataExit(DataArray*) { TheDebug.Exit(0, true); return DataNode(); }

static DataNode DataContains(DataArray* da) {
    DataArray* w = da->Array(1);
    DataNode& n = da->Evaluate(2);
    bool b = !w->Contains(DataNode(n.mValue.integer));
    if (b) return DataNode(kDataUnhandled, 0);
    else return DataNode(1);
}

static DataNode DataFindExists(DataArray* da){
    DataArray* a = da->Array(1);
    for (int i = 2; i < da->Size(); i++) {
        DataNode& n = da->Evaluate(i);
        if (n.Type() == kDataInt || n.Type() == kDataSymbol) {
            a = a->FindArray(n.mValue.integer, false);
            if(!a){
                return DataNode(kDataUnhandled, 0);
            }
        }
        else {
            String str;
            n.Print(str, true);
            MILO_FAIL("Bad key %s (file %s, line %d)", str.c_str(), da->File(), da->Line());
        }
    }
    return DataNode(a, kDataArray);
}

static DataNode DataFind(DataArray* da) {
    DataNode ret = DataFindExists(da);
    if(ret == DataNode(kDataUnhandled, 0)){
        MILO_FAIL("Couldn't find key (file %s, line %d)", da->File(), da->Line());
    }
    return ret;
}

static DataNode DataFindObj(DataArray* da){
    ObjectDir* d = ObjectDir::Main();
    int i;
    for (i = 1; i < da->Size() - 1; i++) {
        DataNode& n = da->Evaluate(i);
        if(n.Type() == kDataObject) d = n.Obj<ObjectDir>(0);
        else d = dynamic_cast<ObjectDir*>(d->FindObject(n.LiteralStr(0), false));
        if(!d) return DataNode(d);
    }
    return DataNode(d->FindObject(da->Str(i), false));
}

static DataNode DataBasename(DataArray* da) {
    return DataNode(FileGetBase(da->Str(1), NULL));
}

static DataNode DataDirname(DataArray* da) {
    const char* s = FileGetPath(da->Str(1), NULL);
    String str(s);
    uint x = str.find_last_of("/");
    return DataNode(x != String::npos);
}

DefDataFunc(HasSubStr, {
    return DataNode((int)strstr(da->Str(1), da->Str(2)));
})

DefDataFunc(HasAnySubStr, {
    DataArray* a = da->Array(2);
    for (int i = 0; i < a->Size(); i++) {
        const char* haystack = a->Str(i);
        if (strstr(da->Str(1), haystack)) return DataNode(1);
    }
    return DataNode(0);
})

DefDataFunc(FindSubStr, {
    String s(da->Str(1));
    return DataNode((int)s.find(da->Str(2)));
})

DefDataFunc(StrElem, {
    char s[2] = {'A'};
    int off = da->Int(2);
    s[0] = da->Str(1)[off];
    return DataNode((Symbol)s);
})

DefDataFunc(SubStr, {
    String s(da->Str(1));
    int i1 = da->Int(2);
    int i2 = da->Int(3);
    return DataNode(s.substr(i1, i2));
})


DefDataFunc(StrCat, {
    DataNode n = da->Var(1);
    String s(n.Str(NULL));
    for (int i = 2; i < da->Size(); i++) {
        s += da->Str(i);
    }
    n = s.c_str();
    return n;
})

DefDataFunc(StringFlags, {
    int x = da->Int(1);
    DataArray* d = da->Array(2);
    String s("");
    for (int i = 1; i < da->Size(); i++) {
        bool b = 0;
        DataArray* macro = DataGetMacro(da->Str(i));
        if (macro) {
            MILO_ASSERT(macro && macro->Size() == 1, 1626);
            macro->Int(0);
        }
    }
    return DataNode(s);
})

char* test = "|";

DefDataFunc(StrToLower, {
    String s = da->Str(1);
    s.ToLower();
    return DataNode(s);
})

DefDataFunc(StrToUpper, {
    String s = da->Str(1);
    s.ToUpper();
    return DataNode(s);
})

DefDataFunc(Strlen, {
    return DataNode((int)strlen(da->Str(1)));
})

static DataNode DataStrieq(DataArray* da) {
    return DataNode(!stricmp(da->Str(1), da->Str(2)));
}

DefDataFunc(SearchReplace, {
    const char* s3 = da->Str(3);
    const char* s2 = da->Str(2);
    const char* s1 = da->Str(1);
    char beeg[0x800];
    bool ret = SearchReplace(s1, s2, s3, beeg);
    DataNode n(beeg);
    da->Var(4);
    return DataNode(ret);
})

DefDataFunc(PushBack, {
    DataArray* work = da->Array(1);
    int nu_size = work->Size();
    work->Resize(nu_size + 1);
    work->Node(nu_size) = da->Evaluate(2);
    return DataNode();
})

static DataNode DataSort(DataArray* da) {
    da->Array(1)->SortNodes();
    return DataNode();
}

DefDataFunc(GetType, {
    return DataNode(da->Evaluate(1).Type());
})

static DataNode DataWith(DataArray* da) {
    return da->ExecuteScript(2, da->GetObj(1), NULL, 1);
}

static DataNode OnSetThis(DataArray* da) {
    Hmx::Object* new_this;
    new_this = da->GetObj(1);
    // gDataThisPtr.Replace(gDataThis, new_this);
    DataSetThis(new_this);
    return DataNode();
}

DefDataFunc(MacroElem, {
    DataArray* macro = DataGetMacro(da->Str(1));
    int i;
    if (da->Size() > 2) {
        i = da->Int(2);
    } else i = 0;
    MILO_ASSERT(macro && macro->Size() > i, 1748);
    return da->Node(i);
})

static DataNode DataMergeDirs(DataArray*) {
    return DataNode();
}

static DataNode DataReplaceObject(DataArray* da) {
    int x, y, z;
    bool a,b,c;
    if (da->Size() > 3) x = da->Int(3);
    else x = 1;
    a = x;
    if (da->Size() > 4) y = da->Int(4);
    else y = 1;
    b = y;
    if (da->Size() > 5) y = da->Int(5);
    else z = 1;
    c = z;
    ReplaceObject(da->GetObj(1), da->GetObj(2), a, b, c);
    return DataNode();
}

static DataNode DataNextName(DataArray* da) {
    ObjectDir* d = gDataDir;
    if (da->Size() > 2) {
        d = da->Obj<ObjectDir>(2);
    }
    return DataNode(NextName(da->Str(1), d));
}

DataNode Quasiquote(const DataNode&) {

}

static DataNode DataQuasiquote(DataArray* da) { return Quasiquote(da->Node(1)); }

DefDataFunc(Unquote, { return DataNode(da->Evaluate(1)); })

static DataNode DataGetDateTime(DataArray* da) {
    return DataNode();
}

static DataArray* sFileMsg;

bool FileListCallBack(char* s) {
    bool ret;
    DataArray* da = sFileMsg;
    DataNode* n = da->Var(3);
    DataNode n2 = *n; {DataNode n3 = s; *n = n3;}
    ret = (bool)sFileMsg->ExecuteBlock(4).Int(NULL);
    if (ret) {
        strcpy(s, n->Str(0));
    }
    *n = n2;
    return ret;
}

static DataNode DataFileList(DataArray* da) {
    sFileMsg = da;
    bool (*x)(char*) = NULL;
    int i, s = da->Size();
    if (s > 3) x = (&FileListCallBack);
    if (s > 2) i = da->Int(2); else i = 1;
    return MakeFileList(da->Str(1), i, x);
}

DefDataFunc(FileListPaths, {
    sFileMsg = da;
    return MakeFileListFullPath(da->Str(1));
})

static DataNode DataObjectList(DataArray* da) {
    ObjectDir* dir = da->Obj<ObjectDir>(1);
    Symbol s = da->Sym(2);
    int x;
    if (da->Size() > 3) x = (bool)da->Int(3); else x = 1;
    return ObjectList(dir, s, x);
}

void ScriptDebugModal(bool&, char*, bool) { }

const char* sgjhfjhadslkgjhasdg = ",";

DefDataFunc(DisableNotify, {
    if (da->Size() > 1) {
        TheDebug.SetDisabled(true);
        for (int i = 1; i < da->Size(); i++) {
            da->Command(i)->Execute();
        }
        TheDebug.SetDisabled(false);
    } else {
        TheDebug << MakeString("invalid # of arguments...\n");
    }
    return DataNode();
})

static DataNode DataFilterNotify(DataArray*) {
    return DataNode();
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
