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
#include <list>
#include <map>

std::map<Symbol, DataFunc*> gDataFuncs;

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
    gDataFuncs[s] = func;
    MILO_FAIL("Can't register different func %s", s);
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

// // fn_8031C5E4
// DataNode DataCountBits(DataArray *da) {
//     return DataNode(CountBits(da->Int(1)));
// }

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

static DataNode DataMin(DataArray* da){
    DataNode& n1 = da->Evaluate(1);
    DataNode& n2 = da->Evaluate(2);
    if(n1.Type() == kDataFloat || n2.Type() == kDataFloat){
        return DataNode(MIN(n1.LiteralFloat(da), n2.LiteralFloat(da)));
    }
    else return DataNode(MIN(n1.LiteralInt(da), n2.LiteralInt(da)));
}

// // fn_8031CAF0
// DataNode DataMax(DataArray *da) {
//     DataNode *dn1 = &da->Evaluate(1);
//     DataNode *dn2 = &da->Evaluate(2);
//     if (dn1->Type() == kDataFloat || dn2->Type() == kDataFloat) {
//         return DataNode(Maximum(dn1->LiteralFloat(da), dn2->LiteralFloat(da)));
//     } else
//         return DataNode(Maximum(dn1->LiteralInt(da), dn2->LiteralInt(da)));
// }

// // fn_8031CBCC
// DataNode DataAbs(DataArray *da) {
//     DataNode *dn = &da->Evaluate(1);
//     float f = AbsThunk(dn->LiteralFloat(da));
//     if (dn->Type() == kDataInt) {
//         return DataNode((int)f);
//     } else
//         return DataNode(f);
// }

void DataTermFuncs(){
    gDataFuncs.clear();
}
