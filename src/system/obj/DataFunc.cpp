#include "obj/DataFunc.h"
#include "math/Rand.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/MakeString.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include "macros.h"
#include "math/MathFuncs.h"
#include "obj/DataUtl.h"
#include "utl/Locale.h"
#include <list>
#include <map>
#include <stdlib.h>

std::map<Symbol, DataFunc*> gDataFuncs;
DataThisPtr gDataThisPtr;

extern Hmx::Object *gDataThis;
extern ObjectDir* gDataDir;

namespace {
    bool AddToNotifies(const char* str, std::list<String>& list){
        if(list.size() > 0x10) return false;
        for(std::list<String>::iterator it = list.begin(); it != list.end(); it++){
            bool strFound = !strcmp(it->c_str(), str);
            if(strFound) return false;
        }
        list.push_back(str);
        return true;
    }
}

void DataRegisterFunc(Symbol s, DataFunc* func){
    const std::map<Symbol, DataFunc*>::iterator it = gDataFuncs.find(s);
    if(it != gDataFuncs.end() && it->second != func)
        MILO_FAIL("Can't register different func %s", s);
    gDataFuncs[s] = func;
}

DataNode DataFuncObj::New(DataArray* arr){
    Hmx::Object* o = ObjectDir::sMainDir->FindObject(arr->Str(1), false);
    if(o) delete o;
    return DataNode(new (_PoolAlloc(0x20, 0x20, FastPool)) DataFuncObj(arr));
}

static DataNode DataSprintf(DataArray *da) {
    FormatString fs(da->Str(1));
    for (int i = 2; i < da->Size(); i++) {
        fs << da->Evaluate(i);
    }
    return DataNode(fs.Str());
}

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
    if(da->Size() != 4) MILO_FAIL("One condition and two alternatives expected (file %s, line %d)", da->mFile.mStr, (int)da->mLine);
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

static DataNode DataMod(DataArray* da);

// // fn_8031D490
// DataNode DataMod(DataArray *da) {
//     DataNode *dn1 = &da->Evaluate(1);
//     DataNode *dn2 = &da->Evaluate(2);
//     if (dn1->Type() == kDataFloat || dn2->Type() == kDataFloat) {
//         return DataNode(Modulo(dn1->LiteralFloat(da), dn2->LiteralFloat(da)));
//     } else
//         return DataNode(Modulo(dn1->LiteralInt(da), dn2->LiteralInt(da)));
// }

static DataNode DataDist(DataArray* da);

// // fn_8031D56C
// DataNode DataDist(DataArray *da) {
//     Vector3 vec;
//     vec.Set(
//         da->Float(1) - da->Float(4),
//         da->Float(2) - da->Float(5),
//         da->Float(3) - da->Float(6)
//     );

//     return DataNode(GetSqrtAsFloat(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
// }

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

static DataNode DataObject(DataArray* da);

static DataNode DataExists(DataArray* da);

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

static DataNode DataTime(DataArray *);

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

static DataNode DataNotifyBeta(DataArray* da);

// void DataNotifyBeta(DataArray *param_1)

// {
//   DataNode *pDVar1;
//   char *pcVar2;
//   DataArray *in_r4;
//   int iVar3;
//   undefined local_938 [4];
//   String SStack_934;
//   char acStack_928 [256];
//   FormatString aFStack_828 [2076];
  
//   String::String(&SStack_934);
//   for (iVar3 = 1; iVar3 < in_r4->mSize; iVar3 = iVar3 + 1) {
//     pDVar1 = (DataNode *)DataArray::Node(in_r4,iVar3);
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
    TheDebug << MakeString("%d", da->Line());
    TheDebug.Fail(str.c_str());
    return DataNode(0);
}

static DataNode DataNotifyOnce(DataArray* da);

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

static DataNode DataSwitch(DataArray* da);

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
