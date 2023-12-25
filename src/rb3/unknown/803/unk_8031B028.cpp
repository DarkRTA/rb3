#include "data.hpp"
#include "symbol.hpp"
#include "common.hpp"
#include "file_ops.hpp"
#include "string.hpp"
#include "std/string.h"
#include "std/stdlib.h"
#include "vector3.hpp"
#include "formatstring.hpp"
#include "debug.hpp"
#include "random.hpp"
#include "mergefilter.hpp"
#include "datamergefilter.hpp"
#include "hmx/object.hpp"
#include "datafuncobj.hpp"

extern void DataRegisterFunc(Symbol, DataFunc *);
extern Debug TheDebug;
extern Hmx::Object *gDataThis;
extern void DataPushVar(DataNode *dn);
extern void DataPopVar();

// fn_80320470
extern DataNode DataReplaceObject(DataArray *);
// fn_8032056C
extern DataNode DataNextName(DataArray *);

// fn_8031B6C0
DataNode DataPrintf(DataArray *da) {
    FormatString fs(da->GetStrAtIndex(1));
    for (int i = 2; i < da->GetNodeCount(); i++) {
        fs << *EvaluateNodeAtIndex(da, i);
    }
    TheDebug << fs.Str();
    return DataNode(0);
}

// fn_8031B62C
DataNode DataSprintf(DataArray *da) {
    FormatString fs(da->GetStrAtIndex(1));
    for (int i = 2; i < da->GetNodeCount(); i++) {
        fs << *EvaluateNodeAtIndex(da, i);
    }
    return DataNode(fs.Str());
}

// fn_8031B7DC
DataNode DataSprint(DataArray *da) {
    String str;
    for (int i = 1; i < da->GetNodeCount(); i++) {
        DataNode *dn = EvaluateNodeAtIndex(da, i);
        dn->Print(str, true);
    }
    return DataNode(str.c_str());
}

// fn_8031B504
// extern DataNode DataFuncObj::New(DataArray*);

// fn_8031B5AC
DataFuncObj::DataFuncObj(DataArray* da){
    arr = da;
    da->IncRefCount();
    // SetName(da->GetStrAtIndex(1), sMainDir)
}

// fn_8031DC40
DataNode DataGetElem(DataArray *da) {
    int i = da->GetIntAtIndex(2);
    DataArray *a = da->GetArrayAtIndex(1);
    DataNode *dn = a->GetNodeAtIndex(i);
    return DataNode(*dn);
}

// fn_8031DCA4
DataNode DataGetLastElem(DataArray *da) {
    DataArray *a = da->GetArrayAtIndex(1);
    int b = a->GetNodeCount();
    return DataNode(*a->GetNodeAtIndex(a->GetNodeCount() - 1));
}

// fn_8031DA1C
DataNode DataForEach(DataArray *da) {
    DataArray *arr = da->GetArrayAtIndex(2);
    arr->IncRefCount();
    DataNode *var = da->GetVarAtIndex(1);
    DataNode lol(*var);
    for (int i = 0; i < arr->GetNodeCount(); i++) {
        *var = *EvaluateNodeAtIndex(arr, i);
        for (int j = 3; j < da->GetNodeCount(); j++) {
            da->GetCommandAtIndex(j)->Execute();
        }
    }
    *var = lol;
    arr->DecRefCount();
    return DataNode(0);
}

// fn_8031DB20
DataNode DataForEachInt(DataArray *da) {
    DataNode *var = da->GetVarAtIndex(1);
    int i2 = da->GetIntAtIndex(2);
    int i3 = da->GetIntAtIndex(3);
    int r31 = -1;
    if (i2 > i3)
        r31 = 1;
    DataNode idk(*var);
    while (i2 != i3) {
        *var = DataNode(i2);
        for (int cnt = 4; cnt < da->GetNodeCount(); cnt++) {
            da->GetCommandAtIndex(cnt)->Execute();
        }
        i2 = var->GetDataNodeVal().intVal + r31;
    }
    *var = idk;
    return DataNode(0);
}

// fn_8031CA14
DataNode DataMin(DataArray *da) {
    DataNode *dn1 = EvaluateNodeAtIndex(da, 1);
    DataNode *dn2 = EvaluateNodeAtIndex(da, 2);
    if (dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat) {
        return DataNode(Minimum(dn1->LiteralFloat(da), dn2->LiteralFloat(da)));
    } else
        return DataNode(Minimum(dn1->LiteralInt(da), dn2->LiteralInt(da)));
}

// fn_8031CAF0
DataNode DataMax(DataArray *da) {
    DataNode *dn1 = EvaluateNodeAtIndex(da, 1);
    DataNode *dn2 = EvaluateNodeAtIndex(da, 2);
    if (dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat) {
        return DataNode(Maximum(dn1->LiteralFloat(da), dn2->LiteralFloat(da)));
    } else
        return DataNode(Maximum(dn1->LiteralInt(da), dn2->LiteralInt(da)));
}

// fn_8031CBCC
DataNode DataAbs(DataArray *da) {
    DataNode *dn = EvaluateNodeAtIndex(da, 1);
    float f = AbsThunk(dn->LiteralFloat(da));
    if (dn->GetType() == kDataInt) {
        return DataNode((int)f);
    } else
        return DataNode(f);
}

// fn_8031CC5C
DataNode DataAdd(DataArray *da) {
    float sum_f = 0.0f;
    int sum_int = 0;
    int cnt = da->GetNodeCount();
    int i;
    for (i = 1; i < cnt; i++) {
        DataNode *dn = EvaluateNodeAtIndex(da, i);
        if (dn->GetType() != kDataInt) {
            sum_f = sum_int + dn->LiteralFloat(da);
            break;
        }
        sum_int += dn->GetDataNodeVal().intVal;
    }
    if (i == cnt)
        return DataNode(sum_int);
    for (i++; i < cnt; i++) {
        sum_f += da->GetFloatAtIndex(i);
    }
    return DataNode(sum_f);
}

// fn_8031CD70
DataNode DataAddEq(DataArray *da) {
    DataNode ret = DataAdd(da);
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        gDataThis->SetProperty(da->GetDataNodeValueAtIndex(1).dataArray, ret);
    } else {
        da->GetVarAtIndex(1)->operator=(ret);
    }
    return ret;
}

// fn_8031CDF4
DataNode DataSub(DataArray *da) {
    DataNode *dn = EvaluateNodeAtIndex(da, 1);
    if (da->GetNodeCount() == 2) {
        if (dn->GetType() == kDataFloat) {
            return DataNode(-dn->LiteralFloat(da));
        } else
            return DataNode(-dn->LiteralInt(da));
    } else {
        DataNode *dn2 = EvaluateNodeAtIndex(da, 2);
        if (dn->GetType() == kDataFloat || dn2->GetType() == kDataFloat) {
            return DataNode(dn->LiteralFloat(da) - dn2->LiteralFloat(da));
        } else {
            return DataNode(dn->LiteralInt(da) - dn2->LiteralInt(da));
        }
    }
}

// fn_8031D0FC
DataNode DataSubEq(DataArray *da) {
    DataNode ret = DataSub(da);
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        gDataThis->SetProperty(da->GetDataNodeValueAtIndex(1).dataArray, ret);
    } else {
        da->GetVarAtIndex(1)->operator=(ret);
    }
    return ret;
}

// fn_8031CF24
DataNode DataMean(DataArray *da) {
    float sum = 0.0;
    int cnt = da->GetNodeCount();
    for (int i = 1; i < cnt; i++) {
        sum += da->GetFloatAtIndex(i);
    }
    return DataNode(sum / (cnt - 1));
}

// fn_8031CFD0
DataNode DataClamp(DataArray *da) {
    DataNode *dn1 = EvaluateNodeAtIndex(da, 1);
    DataNode *dn2 = EvaluateNodeAtIndex(da, 2);
    DataNode *dn3 = EvaluateNodeAtIndex(da, 3);
    if (dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat
        || dn3->GetType() == kDataFloat) {
        return DataNode(
            Clamp(dn1->LiteralFloat(da), dn2->LiteralFloat(da), dn3->LiteralFloat(da))
        );
    } else
        return DataNode(
            Clamp(dn1->LiteralInt(da), dn2->LiteralInt(da), dn3->LiteralInt(da))
        );
}

// fn_8031D180
DataNode DataClampEq(DataArray *da) {
    DataNode ret = DataClamp(da);
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        gDataThis->SetProperty(da->GetDataNodeValueAtIndex(1).dataArray, ret);
    } else {
        da->GetVarAtIndex(1)->operator=(ret);
    }
    return ret;
}

// fn_8031D204
DataNode DataMultiply(DataArray *da) {
    DataNode *dn1 = EvaluateNodeAtIndex(da, 1);
    DataNode *dn2 = EvaluateNodeAtIndex(da, 2);
    if (dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat) {
        return DataNode(dn1->LiteralFloat(da) * dn2->LiteralFloat(da));
    } else {
        return DataNode(dn1->LiteralInt(da) * dn2->LiteralInt(da));
    }
}

// fn_8031D2DC
DataNode DataMultiplyEq(DataArray *da) {
    DataNode ret = DataMultiply(da);
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        gDataThis->SetProperty(da->GetDataNodeValueAtIndex(1).dataArray, ret);
    } else {
        da->GetVarAtIndex(1)->operator=(ret);
    }
    return ret;
}

// fn_8031D360
DataNode DataDivide(DataArray *da) {
    return DataNode(da->GetFloatAtIndex(1) / da->GetFloatAtIndex(2));
}

// fn_8031D3CC
DataNode DataDivideEq(DataArray *da) {
    DataNode ret = DataDivide(da);
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        gDataThis->SetProperty(da->GetDataNodeValueAtIndex(1).dataArray, ret);
    } else {
        da->GetVarAtIndex(1)->operator=(ret);
    }
    return ret;
}

// fn_8031D450
DataNode DataSqrt(DataArray *da) {
    return DataNode(GetSqrtAsFloat(da->GetFloatAtIndex(1)));
}

// fn_8031D490
DataNode DataMod(DataArray *da) {
    DataNode *dn1 = EvaluateNodeAtIndex(da, 1);
    DataNode *dn2 = EvaluateNodeAtIndex(da, 2);
    if (dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat) {
        return DataNode(Modulo(dn1->LiteralFloat(da), dn2->LiteralFloat(da)));
    } else
        return DataNode(Modulo(dn1->LiteralInt(da), dn2->LiteralInt(da)));
}

// fn_8031D56C
DataNode DataDist(DataArray *da) {
    Vector3 vec(
        da->GetFloatAtIndex(1) - da->GetFloatAtIndex(4),
        da->GetFloatAtIndex(2) - da->GetFloatAtIndex(5),
        da->GetFloatAtIndex(3) - da->GetFloatAtIndex(6)
    );

    return DataNode(GetSqrtAsFloat(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

// fn_8031D664
DataNode DataSymbol(DataArray *da) {
    return DataNode((da->ForceSymAtIndex(1)));
}

// fn_8031D700
DataNode DataInt(DataArray *da) {
    DataNode *dn = EvaluateNodeAtIndex(da, 1);
    if (dn->GetType() == kDataSymbol) {
        return DataNode(atoi(dn->GetDataNodeVal().strVal));
    } else if (dn->GetType() == kDataObject || dn->GetType() == kDataInt) {
        return DataNode(dn->GetDataNodeVal().intVal);
    } else
        return DataNode((int)(dn->LiteralFloat(da)));
}

extern char lbl_808E4478[2];
// fn_8031D6A8
DataNode DataChar(DataArray *da) {
    DataNode *dn = EvaluateNodeAtIndex(da, 1);
    lbl_808E4478[0] = dn->Int(nullptr);
    lbl_808E4478[1] = 0;
    return DataNode(lbl_808E4478);
}

// fn_8031D7C4
DataNode DataRound(DataArray *da) {
    DataNode *dn = EvaluateNodeAtIndex(da, 1);
    return DataNode(Round(dn->LiteralFloat(nullptr)));
}

// fn_8031D810
DataNode DataFloor(DataArray *da) {
    return DataNode(FloorThunk(da->GetFloatAtIndex(1)));
}

// fn_8031D850
DataNode DataCeil(DataArray *da) {
    return DataNode(CeilThunk(da->GetFloatAtIndex(1)));
}

// fn_8031B86C
DataNode DataSet(DataArray *da) {
    DataNode *dn = EvaluateNodeAtIndex(da, 2);
    DataNode ret(*dn);
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        gDataThis->SetProperty(da->GetDataNodeValueAtIndex(1).dataArray, ret);
    } else
        da->GetVarAtIndex(1)->operator=(ret);
    return ret;
}

// fn_8031B970
DataNode DataIfElse(DataArray *da) {
    DataNode *dn = da->GetNodeAtIndex(1);
    if (dn->NotNull()) {
        return DataNode(*EvaluateNodeAtIndex(da, 2));
    } else {
        return DataNode(*EvaluateNodeAtIndex(da, 3));
    }
}

// fn_8031B9F0
DataNode DataIf(DataArray *da) {
    if (da->GetNodeAtIndex(1)->NotNull()) {
        for (int i = 2; i < da->GetNodeCount(); i++) {
            da->GetCommandAtIndex(i)->Execute();
        }
        return DataNode(0);
    } else
        return DataNode(0);
}

bool DataNodeIsNull(DataNode *dn) {
    return (!dn->NotNull());
}

// fn_8031BA98
DataNode DataUnless(DataArray *da) {
    if (DataNodeIsNull(da->GetNodeAtIndex(1))) {
        for (int i = 2; i < da->GetNodeCount(); i++) {
            da->GetCommandAtIndex(i)->Execute();
        }
        return DataNode(0);
    } else
        return DataNode(0);
}

// fn_8031BB68
DataNode DataEq(DataArray *da) {
    DataNode *dn1 = EvaluateNodeAtIndex(da, 1);
    DataNode *dn2 = EvaluateNodeAtIndex(da, 2);
    return DataNode(dn1->operator==(*dn2));
}

// fn_8031BCC8
DataNode DataNe(DataArray *da) {
    DataNode dn = DataEq(da);
    return DataNode(dn.GetDataNodeVal().intVal == 0);
}

// fn_8031BD1C
DataNode DataLe(DataArray *da) {
    return DataNode(da->GetFloatAtIndex(1) <= da->GetFloatAtIndex(2));
}

// fn_8031BD8C
DataNode DataLt(DataArray *da) {
    return DataNode(da->GetFloatAtIndex(1) < da->GetFloatAtIndex(2));
}

// fn_8031BDF8
DataNode DataGe(DataArray *da) {
    return DataNode(da->GetFloatAtIndex(1) >= da->GetFloatAtIndex(2));
}

// fn_8031BE68
DataNode DataGt(DataArray *da) {
    return DataNode(da->GetFloatAtIndex(1) > da->GetFloatAtIndex(2));
}

// fn_8031BED4
DataNode DataNot(DataArray *da) {
    return DataNode(DataNodeIsNull(da->GetNodeAtIndex(1)));
}

// fn_8031BF18
DataNode DataAnd(DataArray *da) {
    for (int i = 1; i < da->GetNodeCount(); i++) {
        if (DataNodeIsNull(da->GetNodeAtIndex(i))) {
            return DataNode(0);
        }
    }
    return DataNode(1);
}

// fn_8031BF9C
DataNode DataOr(DataArray *da) {
    for (int i = 1; i < da->GetNodeCount(); i++) {
        DataNode *dn = da->GetNodeAtIndex(i);
        if (dn->NotNull())
            return DataNode(1);
    }
    return DataNode(0);
}

// fn_8031C020
DataNode DataXor(DataArray *da) {
    return DataNode(da->GetNodeAtIndex(1)->NotNull() != da->GetNodeAtIndex(2)->NotNull());
}

// fn_8031C08C
DataNode DataBitAnd(DataArray *da) {
    int res = da->GetIntAtIndex(1);
    for (int i = 2; i < da->GetNodeCount(); i++) {
        res &= da->GetIntAtIndex(i);
    }
    return DataNode(res);
}

// fn_8031C108
DataNode DataAndEqual(DataArray *da) {
    void *arr;
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        arr = da->GetDataNodeValueAtIndex(1).dataArray;
        int res =
            gDataThis->Property((DataArray *)arr, true)->Int(0) & da->GetIntAtIndex(2);
        gDataThis->SetProperty((DataArray *)arr, DataNode(res));
        return DataNode(res);
    } else {
        DataNode *dn_var = da->GetVarAtIndex(1);
        int res = dn_var->Int(0) & da->GetIntAtIndex(2);
        return *(*dn_var = DataNode(res));
    }
}

// fn_8031C224
DataNode DataMaskEqual(DataArray *da) {
    void *arr;
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        arr = da->GetDataNodeValueAtIndex(1).dataArray;
        int res =
            gDataThis->Property((DataArray *)arr, true)->Int(0) & ~da->GetIntAtIndex(2);
        gDataThis->SetProperty((DataArray *)arr, DataNode(res));
        return DataNode(res);
    } else {
        DataNode *dn_var = da->GetVarAtIndex(1);
        int res = dn_var->Int(0) & ~da->GetIntAtIndex(2);
        return *(*dn_var = DataNode(res));
    }
}

// fn_8031C45C
DataNode DataBitOr(DataArray *da) {
    int res = da->GetIntAtIndex(1);
    for (int i = 2; i < da->GetNodeCount(); i++) {
        res |= da->GetIntAtIndex(i);
    }
    return DataNode(res);
}

// fn_8031C340
DataNode DataOrEqual(DataArray *da) {
    void *arr;
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        arr = da->GetDataNodeValueAtIndex(1).dataArray;
        int res =
            gDataThis->Property((DataArray *)arr, true)->Int(0) | da->GetIntAtIndex(2);
        gDataThis->SetProperty((DataArray *)arr, DataNode(res));
        return DataNode(res);
    } else {
        DataNode *dn_var = da->GetVarAtIndex(1);
        int res = dn_var->Int(0) | da->GetIntAtIndex(2);
        return *(*dn_var = DataNode(res));
    }
}

// fn_8031C4D8
DataNode DataBitXor(DataArray *da) {
    return DataNode(da->GetIntAtIndex(1) ^ da->GetIntAtIndex(2));
}

// fn_8031C534
DataNode DataBitNot(DataArray *da) {
    return DataNode(~da->GetIntAtIndex(1));
}

// fn_8031C5B8
int GetLowestBit(int i) {
    if (i == 0)
        return 0;
    int j = 1;
    while (!(j & i))
        j *= 2;
    return j;
}

// fn_8031C574
DataNode DataLowestBit(DataArray *da) {
    return DataNode(GetLowestBit(da->GetIntAtIndex(1)));
}

// fn_8031C5E4
DataNode DataCountBits(DataArray *da) {
    return DataNode(CountBits(da->GetIntAtIndex(1)));
}

// fn_8031C628
DataNode DataWhile(DataArray *da) {
    while (da->GetNodeAtIndex(1)->NotNull()) {
        for (int i = 2; i < da->GetNodeCount(); i++) {
            da->GetCommandAtIndex(i)->Execute();
        }
    }
    return DataNode(0);
}

// fn_8031C904
DataNode DataDo(DataArray *da) {
    int cnt;
    int nodeCnt = da->GetNodeCount();
    for (cnt = 1; da->GetTypeAtIndex(cnt) == kDataArray; cnt++) {
        void *arr;
        DataNode *node;
        arr = da->GetDataNodeValueAtIndex(cnt).dataArray;
        node = ((DataArray *)arr)->GetVarAtIndex(0);
        DataPushVar(node);
        if (((DataArray *)arr)->GetNodeCount() == 2) {
            *node = *EvaluateNodeAtIndex((DataArray *)arr, 1);
        }
    }
    int delCnt = cnt - 1;
    for (; cnt < nodeCnt - 1; cnt++) {
        da->GetCommandAtIndex(cnt)->Execute();
    }
    DataNode ret(*EvaluateNodeAtIndex(da, cnt));
    while (delCnt-- != 0) {
        DataPopVar();
    }
    return ret;
}

// fn_8031D8EC
extern DataNode DataNew(DataArray *);

// fn_8031D890
DataNode DataDelete(DataArray* da){
    Hmx::Object* obj = da->GetObjAtIndex(1);
    delete obj;
    return DataNode(0);
}

// fn_8031DD0C
extern DataNode DataObject(DataArray *);
// fn_8031DE08
extern DataNode DataExists(DataArray *);

extern char *Localize(Symbol, bool *);
extern char *gNullStr;
// fn_8031DEB8
DataNode DataLocalize(DataArray *da) {
    char *loc = Localize(da->ForceSymAtIndex(1), false);
    char *ret = gNullStr;
    if (loc != nullptr) {
        ret = loc;
    }
    return DataNode(ret);
}

extern char *LocalizeSeparatedInt(int);
// fn_8031DF18
DataNode DataLocalizeSeparatedInt(DataArray *da) {
    return DataNode(LocalizeSeparatedInt(da->GetIntAtIndex(1)));
}

extern char *LocalizeFloat(const char *, float);
// fn_8031DF5C
DataNode DataLocalizeFloat(DataArray *da) {
    return DataNode(LocalizeFloat(da->GetStrAtIndex(1), da->GetFloatAtIndex(2)));
}

// fn_8031DFC8
DataNode DataStartsWith(DataArray *da) {
    int i;
    if (da->GetNodeCount() > 3)
        i = da->GetIntAtIndex(3);
    else
        i = strlen(da->GetStrAtIndex(2));
    return DataNode(!strncmp(da->GetStrAtIndex(1), da->GetStrAtIndex(2), i));
}

// fn_8031B764
DataNode DataPrint(DataArray *da) {
    for (int i = 1; i < da->GetNodeCount(); i++) {
        DataNode *dn = EvaluateNodeAtIndex(da, i);
        dn->Print(TheDebug, true);
    }
    return DataNode(0);
}

// fn_8031E06C
extern DataNode DataTime(DataArray *);

// fn_8031E170
DataNode DataRandomInt(DataArray *da) {
    return DataNode(RandomInt(da->GetIntAtIndex(1), da->GetIntAtIndex(2)));
}

// fn_8031E1D4
DataNode DataRandomFloat(DataArray *da) {
    if (da->GetNodeCount() > 1) {
        return DataNode(RandomFloat(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2)));
    } else
        return DataNode(RandomFloat());
}

// fn_8031E25C
DataNode DataRandomElem(DataArray *da) {
    DataArray *a = da->GetArrayAtIndex(1);
    int b = a->GetNodeCount();
    int c_a = a->GetNodeCount();
    DataNode *dn = a->GetNodeAtIndex(RandomInt(0, c_a));
    return DataNode(*dn);
}

// fn_8031E2CC
DataNode DataRandom(DataArray *da) {
    int i = da->GetNodeCount();
    int j = RandomInt(1, i);
    DataNode *dn = EvaluateNodeAtIndex(da, j);
    return DataNode(*dn);
}

// fn_8031E32C
DataNode DataRandomSeed(DataArray *da) {
    SeedRand(da->GetIntAtIndex(1));
    return DataNode(0);
}

// fn_8031E370
DataNode DataNotify(DataArray *da) {
    return DataNode(0);
}

// fn_8031E378
DataNode DataNotifyBeta(DataArray *da) {
    return DataNode(0);
}

// fn_8031E380
DataNode DataFail(DataArray *da) {
    return DataNode(0);
}

// fn_8031E388
DataNode DataNotifyOnce(DataArray *da) {
    return DataNode(0);
}

// fn_8031E564
bool DNArrayNodeEquals(DataNode *dn1, DataNode *dn2) {
    if (dn1->GetType() == kDataArray) {
        void *arr = dn1->value.dataArray;
        for (int i = 0; i < ((DataArray *)arr)->GetNodeCount(); i++) {
            if (*(((DataArray *)arr)->GetNodeAtIndex(i)) == *dn2) {
                return true;
            }
        }
        return false;
    } else
        return *dn1 == *dn2;
}

// fn_8031E470
DataNode DataSwitch(DataArray *da) {
    DataNode *eval = EvaluateNodeAtIndex(da, 1);
    for (int i = 2; i < da->GetNodeCount(); i++) {
        DataNode *node = da->GetNodeAtIndex(i);
        if (node->GetType() == kDataArray) {
            void *arr = node->GetDataNodeVal().dataArray;
            if (DNArrayNodeEquals(((DataArray *)arr)->GetNodeAtIndex(0), eval)) {
                return ((DataArray *)arr)->ExecuteScript(1, gDataThis, nullptr, 1);
            }
        } else
            return da->ExecuteScript(i, gDataThis, nullptr, 1);
    }
    return DataNode(0);
}

// fn_8031E390
DataNode DataCond(DataArray *da) {
    for (int i = 1; i < da->GetNodeCount(); i++) {
        DataNode *node = da->GetNodeAtIndex(i);
        if (node->GetType() == kDataArray) {
            void *arr = node->GetDataNodeVal().dataArray;
            if (((DataArray *)arr)->GetNodeAtIndex(0)->NotNull()) {
                return ((DataArray *)arr)->ExecuteScript(1, gDataThis, nullptr, 1);
            }
        } else {
            return da->ExecuteScript(i, gDataThis, nullptr, 1);
        }
    }
    return DataNode(0);
}

// fn_8031E5FC
DataNode DataInsertElems(DataArray *da) {
    da->GetArrayAtIndex(1)->InsertNodes(da->GetIntAtIndex(2), da->GetArrayAtIndex(3));
    return DataNode(0);
}

// fn_8031E674
DataNode DataInsertElem(DataArray *da) {
    DataArray *a = da->GetArrayAtIndex(1);
    int i = da->GetIntAtIndex(2);
    DataNode *dn = EvaluateNodeAtIndex(da, 3);
    a->Insert(i, *dn);
    return DataNode(0);
}

// fn_8031E6F0
DataNode DataPrintArray(DataArray *da) {
    DataArray *a = da->GetArrayAtIndex(1);
    a->Print(TheDebug, (DataType)0x10, false);
    return DataNode(0);
}

// fn_8031E744
DataNode DataSize(DataArray *da) {
    if (da->GetTypeAtIndex(1) == kDataProperty) {
        return DataNode(gDataThis->PropertySize(da->GetDataNodeValueAtIndex(1).dataArray)
        );
    } else
        return DataNode(da->GetArrayAtIndex(1)->GetNodeCount());
}

// fn_8031E7D4
DataNode DataRemoveElem(DataArray *da) {
    DataArray *a = da->GetArrayAtIndex(1);
    DataNode *dn = EvaluateNodeAtIndex(da, 2);
    a->Remove(*dn);
    return DataNode(0);
}

// fn_8031E83C
DataNode DataResize(DataArray *da) {
    int i = da->GetIntAtIndex(2);
    DataArray *a = da->GetArrayAtIndex(1);
    a->Resize(i);
    return DataNode(0);
}

// fn_8031E8A0
extern DataNode DataNewArray(DataArray *);

// fn_8031E9A0
DataNode DataSetElem(DataArray *da) {
    DataArray *a = da->GetArrayAtIndex(1);
    int i = da->GetIntAtIndex(2);
    DataNode *dn = EvaluateNodeAtIndex(da, 3);
    DataNode *dn2 = a->GetNodeAtIndex(i);
    dn2->operator=(*dn);
    return DataNode(*dn2);
}

// fn_8031EA64
DataNode DataEval(DataArray *da) {
    DataNode *dn = EvaluateNodeAtIndex(da, 1);
    return DataNode(*dn->Evaluate());
}

// fn_8031EB54
float InverseLerp(float f1, float f2, float f3) {
    if (f2 != f1)
        return (f3 - f1) / (f2 - f1);
    else
        return 1.0f;
}

// fn_8031EAA8
DataNode DataReverseInterp(DataArray *da) {
    float ext = InverseLerp(
        da->GetFloatAtIndex(1), da->GetFloatAtIndex(2), da->GetFloatAtIndex(3)
    );
    return DataNode(Clamp(0.0f, 1.0f, ext));
}

// fn_8031EB78
DataNode DataInterp(DataArray *da) {
    return DataNode(
        Interp(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2), da->GetFloatAtIndex(3))
    );
}

// fn_8031EBFC
DataNode DataInc(DataArray* da){
    if(da->GetTypeAtIndex(1) == kDataProperty){
        void* arr = da->GetDataNodeValueAtIndex(1).dataArray;
        DataNode* prop = gDataThis->Property((DataArray*)arr, true);
        int i = prop->Int(nullptr) + 1;
        {
        DataNode inc(i);
        gDataThis->SetProperty((DataArray*)arr, inc);
        }
        return DataNode(i);
    }
    else {
        DataNode* var = da->GetVarAtIndex(1);
        int i = var->Int(nullptr);
        DataNode inc(i + 1);
        return DataNode(*(var->operator=(inc)));
    }
}

// fn_8031ECF8
DataNode DataDec(DataArray* da){
    if(da->GetTypeAtIndex(1) == kDataProperty){
        void* arr = da->GetDataNodeValueAtIndex(1).dataArray;
        DataNode* prop = gDataThis->Property((DataArray*)arr, true);
        int i = prop->Int(nullptr) - 1;
        {
        DataNode inc(i);
        gDataThis->SetProperty((DataArray*)arr, inc);
        }
        return DataNode(i);
    }
    else {
        DataNode* var = da->GetVarAtIndex(1);
        int i = var->Int(nullptr);
        DataNode inc(i - 1);
        return DataNode(*(var->operator=(inc)));
    }
}


// fn_8031F1D0
extern DataNode DataRun(DataArray *);

extern DataArray* DataReadFile(const char*, bool);
// fn_8031F27C
DataNode OnReadFile(DataArray* da){
    DataArray* res = DataReadFile(da->GetStrAtIndex(1), true);
    if(res == nullptr) return DataNode(0);
    else {
        DataNode node(res, kDataArray);
        res->DecRefCount();
        return DataNode(node);
    }
}

// fn_8031F30C
extern DataNode OnWriteFile(DataArray *);
// fn_8031F374
extern DataNode OnFileExists(DataArray *);
// fn_8031F3BC
extern DataNode OnFileReadOnly(DataArray *);
// fn_8031EDF4
extern DataNode DataHandleType(DataArray *);
// fn_8031EEC8
extern DataNode DataHandleTypeRet(DataArray *);
// fn_8031F02C
extern DataNode DataHandle(DataArray *);
// fn_8031F128
extern DataNode DataHandleRet(DataArray *);
// fn_8031F448
extern DataNode DataContains(DataArray *);
// fn_8031EF60
extern DataNode DataExport(DataArray *);
// fn_8031F400
extern DataNode DataExit(DataArray *);
// fn_8031F5F8
extern DataNode DataFind(DataArray *);
// fn_8031F4F0
extern DataNode DataFindExists(DataArray *);

// fn_8031BBD0
DataNode DataFindElem(DataArray *da) {
    DataArray *arr = da->GetArrayAtIndex(1);
    arr->IncRefCount();
    DataNode *dn = EvaluateNodeAtIndex(da, 2);
    for (int i = 0; i < arr->GetNodeCount(); i++) {
        if (!(arr->GetNodeAtIndex(i)->operator==(*dn)))
            continue;
        if (da->GetNodeCount() > 3) {
            da->GetVarAtIndex(3)->operator=(DataNode(i));
        }
        arr->DecRefCount();
        return DataNode(1);
    }
    arr->DecRefCount();
    return DataNode(0);
}

// fn_8031F690
extern DataNode DataFindObj(DataArray *);

// fn_8031F7C0
DataNode DataBasename(DataArray *da) {
    char *base = FileGetBase((char *)da->GetStrAtIndex(1), '\0');
    return DataNode(base);
}

// fn_8031F808
DataNode DataDirname(DataArray *da) {
    char *pFilepath = FileGetPath((char *)da->GetStrAtIndex(1), '\0');
    int i = String(pFilepath).find_last_of("/");
    return DataNode(&pFilepath[i == String::npos ? 0 : i + 1]);
}

// fn_8031F8A8
DataNode DataHasSubStr(DataArray *da) {
    return DataNode((int)strstr(da->GetStrAtIndex(1), da->GetStrAtIndex(2)));
}

// fn_8031F90C
DataNode DataHasAnySubStr(DataArray *da) {
    DataArray *arr = da->GetArrayAtIndex(2);
    for (int i = 0; i < arr->GetNodeCount(); i++) {
        if (strstr(da->GetStrAtIndex(1), arr->GetStrAtIndex(i))) {
            return DataNode(1);
        }
    }
    return DataNode(0);
}

// fn_8031F9B4
DataNode DataFindSubStr(DataArray *da) {
    String str(da->GetStrAtIndex(1));
    return DataNode(str.find(da->GetStrAtIndex(2)));
}

// fn_8031FD80
DataNode DataStrlen(DataArray *da) {
    int len = strlen(da->GetStrAtIndex(1));
    return DataNode(len);
}

extern unsigned short lbl_808E5860;
// fn_8031FDC4
DataNode DataStrElem(DataArray *da) {
    unsigned short c = lbl_808E5860;
    *(char *)&c = da->GetStrAtIndex(1)[da->GetIntAtIndex(2)];
    return DataNode(Symbol((char *)&c));
}

extern "C" DataNode *fn_800E7878(DataArray *, int);

// fn_8031FED0
DataNode DataSearchReplace(DataArray *da) {
    char str[0x800];
    bool changed = SearchReplace(
        da->GetStrAtIndex(1), da->GetStrAtIndex(2), da->GetStrAtIndex(3), str
    );
    da->GetVarAtIndex(4)->operator=(DataNode(str));
    return DataNode(changed);
}

// fn_8031FA30
DataNode DataSubStr(DataArray *da) {
    String str(da->GetStrAtIndex(1));
    int i = da->GetIntAtIndex(2);
    int j = da->GetIntAtIndex(3);
    return DataNode(str.substr(i, j));
}

// fn_8031FAD0
DataNode DataStrCat(DataArray *da) {
    DataNode *dn = da->GetVarAtIndex(1);
    String str(dn->Str(nullptr));
    for (int i = 2; i < da->GetNodeCount(); i++) {
        str += da->GetStrAtIndex(i);
    }
    *dn = DataNode(str.c_str());
    return DataNode(dn->Str(nullptr));
}

extern DataArray *DataGetMacro(Symbol);
// fn_8031FBAC
DataNode DataStringFlags(DataArray *da) {
    int i = da->GetIntAtIndex(1);
    DataArray *a = da->GetArrayAtIndex(2);
    String s('\0');
    for (int j = 0; j < a->GetNodeCount(); j++) {
        DataArray *macro_arr = DataGetMacro(a->GetStrAtIndex(j));
        if (macro_arr != nullptr) {
            macro_arr->GetNodeCount();
            if ((i & macro_arr->GetIntAtIndex(0)) != 0) {
                if (s != '\0') {
                    s += "|";
                }
                s += a->GetStrAtIndex(j);
            }
        }
    }
    return DataNode(s);
}

// fn_8031FCC0
DataNode DataStrToLower(DataArray *da) {
    String str(da->GetStrAtIndex(1));
    str.ToLower();
    return DataNode(str);
}

// fn_8031FD20
DataNode DataStrToUpper(DataArray *da) {
    String str(da->GetStrAtIndex(1));
    str.ToUpper();
    return DataNode(str);
}

// fn_8031FEA8
bool StrICmpIsDifferent(const char *c, const char *d) {
    return !stricmp(c, d);
}

// fn_8031FE44
DataNode DataStrIEq(DataArray *da) {
    return DataNode(StrICmpIsDifferent(da->GetStrAtIndex(1), da->GetStrAtIndex(2)));
}

// fn_8031FF7C
DataNode DataPushBack(DataArray *da) {
    DataArray *a = da->GetArrayAtIndex(1);
    int cnt = a->GetNodeCount();
    a->Resize(cnt + 1);
    *a->GetNodeAtIndex(cnt) = *EvaluateNodeAtIndex(da, 2);
    return DataNode(0);
}

// fn_80320004
DataNode DataSort(DataArray *da) {
    DataArray *a = da->GetArrayAtIndex(1);
    a->SortNodes();
    return DataNode(0);
}

extern DataNode *DataVariable(Symbol);

// fn_8031C6C4
DataNode DataVar(DataArray *da){
    return DataNode(DataVariable(da->ForceSymAtIndex(1)));
}

// fn_8031B904
DataNode DataSetVar(DataArray *da) {
    DataNode ret = *EvaluateNodeAtIndex(da, 2);
    DataNode *dn = DataVariable(da->ForceSymAtIndex(1));
    dn->operator=(ret);
    return ret;
}

// fn_8031C710
DataNode DataPackColor(DataArray *da) {
    return DataNode(
        ((int)(da->GetFloatAtIndex(3) * 255.0f) & 0xFF) << 0x10
        | ((int)(da->GetFloatAtIndex(2) * 255.0f) & 0xFF) << 8
        | ((int)(da->GetFloatAtIndex(1) * 255.0f) & 0xFF)
    );
}

// fn_8031C7C4
DataNode DataUnpackColor(DataArray *da) {
    int packed = da->GetIntAtIndex(1);
    *da->GetVarAtIndex(2) = DataNode((float)(packed & 0xFF) / 255.0f);
    *da->GetVarAtIndex(3) = DataNode((float)(packed >> 8 & 0xFF) / 255.0f);
    *da->GetVarAtIndex(4) = DataNode((float)(packed >> 0x10 & 0xFF) / 255.0f);
    return DataNode(0);
}

// fn_803200E8
extern DataNode OnSetThis(DataArray *);
// fn_80320150
extern DataNode DataMacroElem(DataArray *);
// fn_8032024C
extern DataNode DataMergeDirs(DataArray *);

// fn_8031EA24
DataNode DataQuote(DataArray *da) {
    return DataNode(*da->GetNodeAtIndex(1));
}

// fn_8032080C
extern DataNode DataQuasiquote(DataArray *);

// fn_8032084C
DataNode DataUnquote(DataArray *da) {
    return DataNode(*EvaluateNodeAtIndex(da, 1));
}

// fn_8032088C
extern DataNode DataGetDateTime(DataArray *);

// fn_8032008C
DataNode DataWith(DataArray *da) {
    return da->ExecuteScript(2, da->GetObjAtIndex(1), nullptr, 1);
}

// fn_80320048
DataNode DataGetType(DataArray *da) {
    DataNode *dn = EvaluateNodeAtIndex(da, 1);
    return DataNode(dn->GetType());
}

// fn_80320C20
extern DataNode DataObjectList(DataArray *);
// fn_80320B34
extern DataNode DataFileList(DataArray *);
// fn_80320BD8
extern DataNode DataFileListPaths(DataArray *);

// fn_80320CCC
DataNode DataDisableNotify(DataArray *da) {
    return DataNode(0);
}

// fn_80320CD4
DataNode DataFilterNotify(DataArray *da) {
    return DataNode(0);
}

// fn_80320458
MergeFilter::MergeFilter(DataNode *dn, int asdf) {
    node = dn;
    i = asdf;
}

// fn_80320CDC
void DataInitFuncs() {
    DataRegisterFunc("replace_object", DataReplaceObject);
    DataRegisterFunc("next_name", DataNextName);
    DataRegisterFunc("printf", DataPrintf);
    DataRegisterFunc("sprintf", DataSprintf);
    DataRegisterFunc("sprint", DataSprint);
    // DataRegisterFunc("func", DataFuncObj::New);
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
    DataRegisterFunc("/", DataDivide);
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
    DataRegisterFunc("strieq", DataStrIEq);
    DataRegisterFunc("push_back", DataPushBack);
    DataRegisterFunc("sort", DataSort);
    DataRegisterFunc("var", DataVar);
    DataRegisterFunc("set_var", DataSetVar);
    DataRegisterFunc("pack_color", DataPackColor);
    DataRegisterFunc("unpack_color", DataUnpackColor);
    DataRegisterFunc("set_this", OnSetThis);
    DataRegisterFunc("macro_elem", DataMacroElem);
    DataRegisterFunc("merge_dirs", DataMergeDirs);
    DataRegisterFunc("quote", DataQuote);
    DataRegisterFunc("'", DataQuote);
    DataRegisterFunc("quasiquote", DataQuasiquote);
    DataRegisterFunc("`", DataQuasiquote);
    DataRegisterFunc("unquote", DataUnquote);
    DataRegisterFunc(",", DataUnquote);
    DataRegisterFunc("get_date_time", DataGetDateTime);
    DataRegisterFunc("with", DataWith);
    DataRegisterFunc("type", DataGetType);
    DataRegisterFunc("object_list", DataObjectList);
    DataRegisterFunc("file_list", DataFileList);
    DataRegisterFunc("file_list_paths", DataFileListPaths);
    DataRegisterFunc("disable_notify", DataDisableNotify);
    DataRegisterFunc("filter_notify", DataFilterNotify);
    char c[8];
    memset(&c, 0, sizeof(c));
    c[0] = 'O';
    c[1] = '6';
    c[2] = '4';
    DataRegisterFunc(c, DataWhile);
    c[2] = '5';
    DataRegisterFunc(c, DataSize);
    c[2] = '6';
    DataRegisterFunc(c, DataSwitch);
    c[2] = '7';
    DataRegisterFunc(c, DataGetElem);
    c[2] = '8';
    DataRegisterFunc(c, DataDo);
    c[2] = '9';
    DataRegisterFunc(c, DataSet);
    c[1] = '7';
    c[2] = '0';
    DataRegisterFunc(c, DataInc);
}