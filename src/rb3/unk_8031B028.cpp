#include "data.hpp"
#include "symbol.hpp"
#include "common.hpp"
#include "file_ops.hpp"
#include "string.hpp"
#include "std/string.h"

extern "C" void DataRegisterFunc(Symbol, DataNode (*)(DataArray*));

// fn_80320470
extern DataNode DataReplaceObject(DataArray*);
// fn_8032056C
extern DataNode DataNextName(DataArray*);
// fn_8031B6C0
extern DataNode DataPrintf(DataArray*);
// fn_8031B62C
extern DataNode DataSprintf(DataArray*);

// fn_8031B7DC
DataNode DataSprint(DataArray* da){
    String str;
    for(int i = 1; i < da->GetNodeCount(); i++){
        DataNode* dn = EvaluateNodeAtIndex(da, i);
        dn->Print(str, true);
    }
    return DataNode(str.c_str());
}

// fn_8031B504
// extern DataNode DataFuncObj::New(DataArray*);

// fn_8031DC40
DataNode DataGetElem(DataArray* da){
    int i = da->GetIntAtIndex(2);
    DataArray* a = da->GetArrayAtIndex(1);
    DataNode* dn = a->GetNodeAtIndex(i);
    return DataNode(*dn);
}

// fn_8031DCA4
DataNode DataGetLastElem(DataArray* da){
    DataArray* a = da->GetArrayAtIndex(1);
    int b = a->GetNodeCount();
    return DataNode(*a->GetNodeAtIndex(a->GetNodeCount() - 1));
}

// fn_8031DA1C
extern DataNode DataForEach(DataArray*);
// fn_8031DB20
extern DataNode DataForEachInt(DataArray*);
// fn_8031CA14
extern DataNode DataMin(DataArray*);
// fn_8031CAF0
extern DataNode DataMax(DataArray*);

// fn_8031CBCC
DataNode DataAbs(DataArray* da){
    DataNode* dn = EvaluateNodeAtIndex(da, 1);
    float f = AbsThunk(dn->LiteralFloat(da));
    if(dn->GetType() == kDataInt){
        return DataNode((int)f);
    }
    else return DataNode(f);
}

// fn_8031CC5C
DataNode DataAdd(DataArray* da){
    float sum_f = 0.0;
    int sum_int = 0;
    for(int i = 1; i < da->GetNodeCount(); i++){
        DataNode* dn = EvaluateNodeAtIndex(da, i);
        if(dn->GetType() == kDataInt){
            sum_int += dn->GetIntVal();
        }
        else {
            sum_f += dn->LiteralFloat(da);
        }
    }
}

// fn_8031CD70
extern DataNode DataAddEq(DataArray*);

// fn_8031CDF4
DataNode DataSub(DataArray* da){
    DataNode* dn = EvaluateNodeAtIndex(da, 1);
    if(da->GetNodeCount() == 2){
        if(dn->GetType() == kDataFloat){
            return DataNode(-dn->LiteralFloat(da));
        }
        else return DataNode(-dn->LiteralInt(da));
    }
    else {
        DataNode* dn2 = EvaluateNodeAtIndex(da, 2);
        if(dn->GetType() == kDataFloat || dn2->GetType() == kDataFloat){
            return DataNode(dn->LiteralFloat(da) - dn2->LiteralFloat(da));
        }
        else {
            return DataNode(dn->LiteralInt(da) - dn2->LiteralInt(da));
        }
    }
}

// fn_8031D0FC
extern DataNode DataSubEq(DataArray*);

// fn_8031CF24
DataNode DataMean(DataArray* da){
    float sum = 0.0;
    int cnt = da->GetNodeCount();
    for(int i = 1; i < cnt; i++){
        sum += da->GetFloatAtIndex(i);
    }
    return DataNode(sum / (cnt - 1));
}

// fn_8031CFD0
extern DataNode DataClamp(DataArray*);
// fn_8031D180
extern DataNode DataClampEq(DataArray*);

// fn_8031D204
DataNode DataMultiply(DataArray* da){
    DataNode* dn1 = EvaluateNodeAtIndex(da, 1);
    DataNode* dn2 = EvaluateNodeAtIndex(da, 2);
    if(dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat){
        return DataNode(dn1->LiteralFloat(da) * dn2->LiteralFloat(da));
    }
    else {
        return DataNode(dn1->LiteralInt(da) * dn2->LiteralInt(da));
    }
}

// fn_8031D2DC
extern DataNode DataMultiplyEq(DataArray*);

// fn_8031D360
DataNode DataDivide(DataArray* da){
    return DataNode(da->GetFloatAtIndex(1) / da->GetFloatAtIndex(2));
}

// fn_8031D3CC
extern DataNode DataDivideEq(DataArray*);
// fn_8031D450
extern DataNode DataSqrt(DataArray*);
// fn_8031D490
extern DataNode DataMod(DataArray*);
// fn_8031D56C
extern DataNode DataDist(DataArray*);
// fn_8031D664
extern DataNode DataSymbol(DataArray*);
// fn_8031D700
extern DataNode DataInt(DataArray*);

extern char lbl_808E4478[2];
// fn_8031D6A8
DataNode DataChar(DataArray* da){
    DataNode* dn = EvaluateNodeAtIndex(da, 1);
    lbl_808E4478[0] = dn->Int(nullptr);
    lbl_808E4478[1] = 0;
    return DataNode(lbl_808E4478);
}

// fn_8031D7C4
DataNode DataRound(DataArray* da){
    DataNode* dn = EvaluateNodeAtIndex(da, 1);
    return DataNode(Round(dn->LiteralFloat(nullptr)));
}

// fn_8031D810
DataNode DataFloor(DataArray* da){
    return DataNode(FloorThunk(da->GetFloatAtIndex(1)));
}

// fn_8031D850
DataNode DataCeil(DataArray* da){
    return DataNode(CeilThunk(da->GetFloatAtIndex(1)));
}

// fn_8031B86C
extern DataNode DataSet(DataArray*);

// fn_8031B970
DataNode DataIfElse(DataArray* da){
    DataNode* dn = da->GetNodeAtIndex(1);
    if(dn->NotNull()){
        return DataNode(*EvaluateNodeAtIndex(da, 2));
    }
    else {
        return DataNode(*EvaluateNodeAtIndex(da, 3));
    }
}

// fn_8031B9F0
extern DataNode DataIf(DataArray*);
// fn_8031BA98
extern DataNode DataUnless(DataArray*);

bool DataNodeIsNull(DataNode* dn){
    return (!dn->NotNull());
}

// fn_8031BB68
DataNode DataEq(DataArray* da){
    DataNode* dn1 = EvaluateNodeAtIndex(da, 1);
    DataNode* dn2 = EvaluateNodeAtIndex(da, 2);
    return DataNode(dn1->operator==(*dn2));
}

// fn_8031BCC8
DataNode DataNe(DataArray* da){
    DataNode dn = DataEq(da);
    return DataNode(dn.GetIntVal() == 0);
}

// fn_8031BD1C
DataNode DataLe(DataArray* da){
    return DataNode(da->GetFloatAtIndex(1) <= da->GetFloatAtIndex(2));
}

// fn_8031BD8C
DataNode DataLt(DataArray* da){
    return DataNode(da->GetFloatAtIndex(1) < da->GetFloatAtIndex(2));
}

// fn_8031BDF8
DataNode DataGe(DataArray* da){
    return DataNode(da->GetFloatAtIndex(1) >= da->GetFloatAtIndex(2));
}

// fn_8031BE68
DataNode DataGt(DataArray* da){
    return DataNode(da->GetFloatAtIndex(1) > da->GetFloatAtIndex(2));
}

// fn_8031BED4
DataNode DataNot(DataArray* da){
    return DataNode(DataNodeIsNull(da->GetNodeAtIndex(1)));
}

// fn_8031BF18
DataNode DataAnd(DataArray* da){
    for(int i = 1; i < da->GetNodeCount(); i++){
        if(DataNodeIsNull(da->GetNodeAtIndex(i))){
            return DataNode(0);
        }
    }
    return DataNode(1);
}

// fn_8031BF9C
DataNode DataOr(DataArray* da){
    for(int i = 1; i < da->GetNodeCount(); i++){
        DataNode* dn = da->GetNodeAtIndex(i);
        if(dn->NotNull()) return DataNode(1);
    }
    return DataNode(0);
}

// fn_8031C020
DataNode DataXor(DataArray* da){
    return DataNode(da->GetNodeAtIndex(1)->NotNull() !=
        da->GetNodeAtIndex(2)->NotNull());
}

// fn_8031C08C
DataNode DataBitAnd(DataArray* da){
    int res = da->GetIntAtIndex(1);
    for(int i = 2; i < da->GetNodeCount(); i++){
        res &= da->GetIntAtIndex(i);
    }
    return DataNode(res);
}

// fn_8031C108
extern DataNode DataAndEqual(DataArray*);
// fn_8031C224
extern DataNode DataMaskEqual(DataArray*);

// fn_8031C45C
DataNode DataBitOr(DataArray* da){
    int res = da->GetIntAtIndex(1);
    for(int i = 2; i < da->GetNodeCount(); i++){
        res |= da->GetIntAtIndex(i);
    }
    return DataNode(res);
}

// fn_8031C340
extern DataNode DataOrEqual(DataArray*);

// fn_8031C4D8
DataNode DataBitXor(DataArray* da){
    return DataNode(da->GetIntAtIndex(1) ^ da->GetIntAtIndex(2));
}

// fn_8031C534
DataNode DataBitNot(DataArray* da){
    return DataNode(~da->GetIntAtIndex(1));
}

extern "C" int fn_8031C5B8(int);

// fn_8031C5B8
int GetLowestBit(int i){
    if(i == 0) return 0;
    int j = 1;
    while(!(j & i)) j *= 2;
    return j;
}

// fn_8031C574
extern DataNode DataLowestBit(DataArray*);
DataNode DataLowestBit(DataArray* da){
    return DataNode(GetLowestBit(da->GetIntAtIndex(1)));
}

// fn_8031C5E4
extern DataNode DataCountBits(DataArray*);
// fn_8031C628
extern DataNode DataWhile(DataArray*);
// fn_8031C904
extern DataNode DataDo(DataArray*);
// fn_8031D8EC
extern DataNode DataNew(DataArray*);
// fn_8031D890
extern DataNode DataDelete(DataArray*);
// fn_8031DD0C
extern DataNode DataObject(DataArray*);
// fn_8031DE08
extern DataNode DataExists(DataArray*);
// fn_8031DEB8
extern DataNode DataLocalize(DataArray*);
// fn_8031DF18
extern DataNode DataLocalizeSeparatedInt(DataArray*);
// fn_8031DF5C
extern DataNode DataLocalizeFloat(DataArray*);

// fn_8031DFC8
DataNode DataStartsWith(DataArray* da){
    int i;
    if(da->GetNodeCount() > 3) i = da->GetIntAtIndex(3);
    else i = strlen(da->GetStrAtIndex(2));
    return DataNode(!strncmp(da->GetStrAtIndex(1), da->GetStrAtIndex(2), i));
}

// fn_8031B764
extern DataNode DataPrint(DataArray*);
// fn_8031E06C
extern DataNode DataTime(DataArray*);

extern int RandomInt(int, int);
// fn_8031E170
DataNode DataRandomInt(DataArray* da){
    return DataNode(RandomInt(da->GetIntAtIndex(1), da->GetIntAtIndex(2)));
}

extern float RandomFloat();
extern float RandomFloat(float, float);
// fn_8031E1D4
DataNode DataRandomFloat(DataArray* da){
    if(da->GetNodeCount() > 1){
        return DataNode(RandomFloat(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2)));
    }
    else return DataNode(RandomFloat());
}

// fn_8031E25C
DataNode DataRandomElem(DataArray* da){
    DataArray* a = da->GetArrayAtIndex(1);
    int b = a->GetNodeCount();
    int c_a = a->GetNodeCount();
    DataNode* dn = a->GetNodeAtIndex(RandomInt(0, c_a));
    return DataNode(*dn);
}

// fn_8031E2CC
DataNode DataRandom(DataArray* da){
    int i = da->GetNodeCount();
    int j = RandomInt(1, i);
    DataNode* dn = EvaluateNodeAtIndex(da, j);
    return DataNode(*dn);
}

extern void SeedRand(int);
// fn_8031E32C
DataNode DataRandomSeed(DataArray* da){
    SeedRand(da->GetIntAtIndex(1));
    return DataNode(0);
}

// fn_8031E370
DataNode DataNotify(DataArray* da){
    return DataNode(0);
}

// fn_8031E378
DataNode DataNotifyBeta(DataArray* da){
    return DataNode(0);
}

// fn_8031E380
DataNode DataFail(DataArray* da){
    return DataNode(0);
}

// fn_8031E388
DataNode DataNotifyOnce(DataArray* da){
    return DataNode(0);
}


// fn_8031E470
extern DataNode DataSwitch(DataArray*);
// fn_8031E390
extern DataNode DataCond(DataArray*);

// fn_8031E5FC
DataNode DataInsertElems(DataArray* da){
    da->GetArrayAtIndex(1)->InsertNodes(da->GetIntAtIndex(2), da->GetArrayAtIndex(3));
    return DataNode(0);
}

// fn_8031E674
DataNode DataInsertElem(DataArray* da){
    DataArray* a = da->GetArrayAtIndex(1);
    int i = da->GetIntAtIndex(2);
    DataNode* dn = EvaluateNodeAtIndex(da, 3);
    a->Insert(i, *dn);
    return DataNode(0);
}

// fn_8031E6F0
extern TextStream* TheDebug;
extern DataNode DataPrintArray(DataArray*);
DataNode DataPrintArray(DataArray* da){
    DataArray* a = da->GetArrayAtIndex(1);
    a->Print(*TheDebug, (DataType)0x10, false);
    return DataNode(0);
}

// fn_8031E744
extern DataNode DataSize(DataArray*);

// fn_8031E7D4
DataNode DataRemoveElem(DataArray* da){
    DataArray* a = da->GetArrayAtIndex(1);
    DataNode* dn = EvaluateNodeAtIndex(da, 2);
    a->Remove(*dn);
    return DataNode(0);
}

// fn_8031E83C
DataNode DataResize(DataArray* da){
    int i = da->GetIntAtIndex(2);
    DataArray* a = da->GetArrayAtIndex(1);
    a->Resize(i);
    return DataNode(0);
}

// fn_8031E8A0
extern DataNode DataNewArray(DataArray*);

// fn_8031E9A0
DataNode DataSetElem(DataArray* da){
    DataArray* a = da->GetArrayAtIndex(1);
    int i = da->GetIntAtIndex(2);
    DataNode* dn = EvaluateNodeAtIndex(da, 3);
    DataNode* dn2 = a->GetNodeAtIndex(i);
    dn2->operator=(*dn);
    return DataNode(*dn2);
}

// fn_8031EA64
DataNode DataEval(DataArray* da){
    DataNode* dn = EvaluateNodeAtIndex(da, 1);
    return DataNode(*dn->Evaluate());
}

// fn_8031EAA8
extern DataNode DataReverseInterp(DataArray*);
// fn_8031EB78
extern DataNode DataInterp(DataArray*);
// fn_8031EBFC
extern DataNode DataInc(DataArray*);
// fn_8031ECF8
extern DataNode DataDec(DataArray*);
// fn_8031F1D0
extern DataNode DataRun(DataArray*);

// fn_8031F27C
extern DataNode OnReadFile(DataArray*);


// fn_8031F30C
extern DataNode OnWriteFile(DataArray*);
// fn_8031F374
extern DataNode OnFileExists(DataArray*);
// fn_8031F3BC
extern DataNode OnFileReadOnly(DataArray*);
// fn_8031EDF4
extern DataNode DataHandleType(DataArray*);
// fn_8031EEC8
extern DataNode DataHandleTypeRet(DataArray*);
// fn_8031F02C
extern DataNode DataHandle(DataArray*);
// fn_8031F128
extern DataNode DataHandleRet(DataArray*);
// fn_8031F448
extern DataNode DataContains(DataArray*);
// fn_8031EF60
extern DataNode DataExport(DataArray*);
// fn_8031F400
extern DataNode DataExit(DataArray*);
// fn_8031F5F8
extern DataNode DataFind(DataArray*);
// fn_8031F4F0
extern DataNode DataFindExists(DataArray*);
// fn_8031BBD0
extern DataNode DataFindElem(DataArray*);
// fn_8031F690
extern DataNode DataFindObj(DataArray*);

// fn_8031F7C0
DataNode DataBasename(DataArray* da){
    char* base = FileGetBase((char*)da->GetStrAtIndex(1), '\0');
    return DataNode(base);
}

// fn_8031F808
DataNode DataDirname(DataArray* da){
    String s(FileGetPath((char*)da->GetStrAtIndex(1), '\0'));
    int i = s.find_last_of("/");
    return DataNode(s[i]);
}

// fn_8031F8A8
DataNode DataHasSubStr(DataArray* da){
    return DataNode((int)strstr(da->GetStrAtIndex(1), da->GetStrAtIndex(2)));
}

// fn_8031F90C
DataNode DataHasAnySubStr(DataArray* da){
    DataArray* arr = da->GetArrayAtIndex(2);
    for(int i = 0; i < arr->GetNodeCount(); i++){
        if(strstr(da->GetStrAtIndex(1), arr->GetStrAtIndex(i))){
            return DataNode(1);
        }
    }
    return DataNode(0);
}

// fn_8031F9B4
DataNode DataFindSubStr(DataArray* da){
    String str(da->GetStrAtIndex(1));
    return DataNode(str.find(da->GetStrAtIndex(2)));
}

// fn_8031FD80
DataNode DataStrlen(DataArray* da){
    int len = strlen(da->GetStrAtIndex(1));
    return DataNode(len);
}

extern char lbl_808E5860;
// fn_8031FDC4
DataNode DataStrElem(DataArray* da){
    Symbol s(&lbl_808E5860);
    int i = da->GetIntAtIndex(2);
    const char* c = da->GetStrAtIndex(1);
    return DataNode(s);
}

extern "C" DataNode* fn_800E7878(DataArray*, int);

// fn_8031FED0
DataNode DataSearchReplace(DataArray* da){
    char* str;
    bool changed = SearchReplace(da->GetStrAtIndex(1), da->GetStrAtIndex(2), da->GetStrAtIndex(3), str);
    DataNode dn(str);
    DataNode* asdf = fn_800E7878(da, 4);
    return DataNode(changed);
}

// fn_8031FA30
DataNode DataSubStr(DataArray* da){
    String str(da->GetStrAtIndex(1));
    int i = da->GetIntAtIndex(2);
    int j = da->GetIntAtIndex(3);
    return DataNode(str.substr(i, j));
}

// fn_8031FAD0
extern DataNode DataStrCat(DataArray*);

// fn_8031FBAC
DataNode DataStringFlags(DataArray* da){
    int i = da->GetIntAtIndex(1);
    DataArray* a = da->GetArrayAtIndex(2);
    String s('\0');
    for(int j = 0; j < a->GetNodeCount(); j++){
        Symbol sym((char*)a->GetStrAtIndex(j));
    }
    return DataNode(s);
}

// fn_8031FCC0
DataNode DataStrToLower(DataArray* da){
    String str(da->GetStrAtIndex(1));
    str.ToLower();
    return DataNode(str);
}

// fn_8031FD20
DataNode DataStrToUpper(DataArray* da){
    String str(da->GetStrAtIndex(1));
    str.ToUpper();
    return DataNode(str);
}

// fn_8031FEA8
bool StrICmpIsDifferent(const char* c, const char* d){
    return !stricmp(c, d);
}

// fn_8031FE44
DataNode DataStrIEq(DataArray* da){
    return DataNode(StrICmpIsDifferent(da->GetStrAtIndex(1), da->GetStrAtIndex(2)));
}

// fn_8031FF7C
DataNode DataPushBack(DataArray* da){
    DataArray* a = da->GetArrayAtIndex(1);
    int cnt = a->GetNodeCount();
    a->Resize(cnt + 1);
    *a->GetNodeAtIndex(cnt) = *EvaluateNodeAtIndex(da, 2);
    return DataNode(0);
}

// fn_80320004
DataNode DataSort(DataArray* da){
    DataArray* a = da->GetArrayAtIndex(1);
    a->SortNodes();
    return DataNode(0);
}

// fn_8031C6C4
extern DataNode DataVar(DataArray*);
// fn_8031B904
extern DataNode DataSetVar(DataArray*);
// fn_8031C710
extern DataNode DataPackColor(DataArray*);
// fn_8031C7C4
extern DataNode DataUnpackColor(DataArray*);
// fn_803200E8
extern DataNode OnSetThis(DataArray*);
// fn_80320150
extern DataNode DataMacroElem(DataArray*);
// fn_8032024C
extern DataNode DataMergeDirs(DataArray*);

// fn_8031EA24
DataNode DataQuote(DataArray* da){
    return DataNode(*da->GetNodeAtIndex(1));
}

// fn_8032080C
extern DataNode DataQuasiquote(DataArray*);

// fn_8032084C
DataNode DataUnquote(DataArray* da){
    return DataNode(*EvaluateNodeAtIndex(da, 1));
}

// fn_8032088C
extern DataNode DataGetDateTime(DataArray*);
// fn_8032008C
extern DataNode DataWith(DataArray*);

// fn_80320048
DataNode DataGetType(DataArray* da){
    DataNode* dn = EvaluateNodeAtIndex(da, 1);
    return DataNode(dn->GetType());
}

// fn_80320C20
extern DataNode DataObjectList(DataArray*);
// fn_80320B34
extern DataNode DataFileList(DataArray*);
// fn_80320BD8
extern DataNode DataFileListPaths(DataArray*);

// fn_80320CCC
DataNode DataDisableNotify(DataArray* da){
    return DataNode(0);
}

// fn_80320CD4
DataNode DataFilterNotify(DataArray* da){
    return DataNode(0);
}

// fn_80320CDC
void DataInitFuncs(){
    DataRegisterFunc(Symbol("replace_object"), DataReplaceObject);
    DataRegisterFunc(Symbol("next_name"), DataNextName);
    DataRegisterFunc(Symbol("printf"), DataPrintf);
    DataRegisterFunc(Symbol("sprintf"), DataSprintf);
    DataRegisterFunc(Symbol("sprint"), DataSprint);
    // DataRegisterFunc(Symbol("func"), DataFuncObj::New);
    DataRegisterFunc(Symbol("elem"), DataGetElem);
    DataRegisterFunc(Symbol("last_elem"), DataGetLastElem);
    DataRegisterFunc(Symbol("foreach"), DataForEach);
    DataRegisterFunc(Symbol("foreach_int"), DataForEachInt);
    DataRegisterFunc(Symbol("min"), DataMin);
    DataRegisterFunc(Symbol("max"), DataMax);
    DataRegisterFunc(Symbol("abs"), DataAbs);
    DataRegisterFunc(Symbol("+"), DataAdd);
    DataRegisterFunc(Symbol("+="), DataAddEq);
    DataRegisterFunc(Symbol("-"), DataSub);
    DataRegisterFunc(Symbol("-="), DataSubEq);
    DataRegisterFunc(Symbol("mean"), DataMean);
    DataRegisterFunc(Symbol("clamp"), DataClamp);
    DataRegisterFunc(Symbol("clamp_eq"), DataClampEq);
    DataRegisterFunc(Symbol("*"), DataMultiply);
    DataRegisterFunc(Symbol("*="), DataMultiplyEq);
    DataRegisterFunc(Symbol("/"), DataDivide);
    DataRegisterFunc(Symbol("/="), DataDivideEq);
    DataRegisterFunc(Symbol("sqrt"), DataSqrt);
    DataRegisterFunc(Symbol("mod"), DataMod);
    DataRegisterFunc(Symbol("dist"), DataDist);
    DataRegisterFunc(Symbol("symbol"), DataSymbol);
    DataRegisterFunc(Symbol("int"), DataInt);
    DataRegisterFunc(Symbol("char"), DataChar);
    DataRegisterFunc(Symbol("round"), DataRound);
    DataRegisterFunc(Symbol("floor"), DataFloor);
    DataRegisterFunc(Symbol("ceil"), DataCeil);
    DataRegisterFunc(Symbol("set"), DataSet);
    DataRegisterFunc(Symbol("if_else"), DataIfElse);
    DataRegisterFunc(Symbol("if"), DataIf);
    DataRegisterFunc(Symbol("unless"), DataUnless);
    DataRegisterFunc(Symbol("=="), DataEq);
    DataRegisterFunc(Symbol("!="), DataNe);
    DataRegisterFunc(Symbol("<="), DataLe);
    DataRegisterFunc(Symbol("<"), DataLt);
    DataRegisterFunc(Symbol(">="), DataGe);
    DataRegisterFunc(Symbol(">"), DataGt);
    DataRegisterFunc(Symbol("!"), DataNot);
    DataRegisterFunc(Symbol("&&"), DataAnd);
    DataRegisterFunc(Symbol("||"), DataOr);
    DataRegisterFunc(Symbol("^^"), DataXor);
    DataRegisterFunc(Symbol("&"), DataBitAnd);
    DataRegisterFunc(Symbol("&="), DataAndEqual);
    DataRegisterFunc(Symbol("mask_eq"), DataMaskEqual);
    DataRegisterFunc(Symbol("|"), DataBitOr);
    DataRegisterFunc(Symbol("|="), DataOrEqual);
    DataRegisterFunc(Symbol("^"), DataBitXor);
    DataRegisterFunc(Symbol("~"), DataBitNot);
    DataRegisterFunc(Symbol("lowest_bit"), DataLowestBit);
    DataRegisterFunc(Symbol("count_bits"), DataCountBits);
    DataRegisterFunc(Symbol("while"), DataWhile);
    DataRegisterFunc(Symbol("do"), DataDo);
    DataRegisterFunc(Symbol("new"), DataNew);
    DataRegisterFunc(Symbol("delete"), DataDelete);
    DataRegisterFunc(Symbol("object"), DataObject);
    DataRegisterFunc(Symbol("exists"), DataExists);
    DataRegisterFunc(Symbol("localize"), DataLocalize);
    DataRegisterFunc(Symbol("localize_separated_int"), DataLocalizeSeparatedInt);
    DataRegisterFunc(Symbol("localize_float"), DataLocalizeFloat);
    DataRegisterFunc(Symbol("startswith"), DataStartsWith);
    DataRegisterFunc(Symbol("print"), DataPrint);
    DataRegisterFunc(Symbol("time"), DataTime);
    DataRegisterFunc(Symbol("random_int"), DataRandomInt);
    DataRegisterFunc(Symbol("random_float"), DataRandomFloat);
    DataRegisterFunc(Symbol("random_elem"), DataRandomElem);
    DataRegisterFunc(Symbol("random"), DataRandom);
    DataRegisterFunc(Symbol("random_seed"), DataRandomSeed);
    DataRegisterFunc(Symbol("notify"), DataNotify);
    DataRegisterFunc(Symbol("notify_beta"), DataNotifyBeta);
    DataRegisterFunc(Symbol("fail"), DataFail);
    DataRegisterFunc(Symbol("notify_once"), DataNotifyOnce);
    DataRegisterFunc(Symbol("switch"), DataSwitch);
    DataRegisterFunc(Symbol("cond"), DataCond);
    DataRegisterFunc(Symbol("insert_elems"), DataInsertElems);
    DataRegisterFunc(Symbol("insert_elem"), DataInsertElem);
    DataRegisterFunc(Symbol("print_array"), DataPrintArray);
    DataRegisterFunc(Symbol("size"), DataSize);
    DataRegisterFunc(Symbol("remove_elem"), DataRemoveElem);
    DataRegisterFunc(Symbol("resize"), DataResize);
    DataRegisterFunc(Symbol("array"), DataNewArray);
    DataRegisterFunc(Symbol("set_elem"), DataSetElem);
    DataRegisterFunc(Symbol("eval"), DataEval);
    DataRegisterFunc(Symbol("reverse_interp"), DataReverseInterp);
    DataRegisterFunc(Symbol("interp"), DataInterp);
    DataRegisterFunc(Symbol("++"), DataInc);
    DataRegisterFunc(Symbol("--"), DataDec);
    DataRegisterFunc(Symbol("run"), DataRun);
    DataRegisterFunc(Symbol("read_file"), OnReadFile);
    DataRegisterFunc(Symbol("write_file"), OnWriteFile);
    DataRegisterFunc(Symbol("file_exists"), OnFileExists);
    DataRegisterFunc(Symbol("file_read_only"), OnFileReadOnly);
    DataRegisterFunc(Symbol("handle_type"), DataHandleType);
    DataRegisterFunc(Symbol("handle_type_ret"), DataHandleTypeRet);
    DataRegisterFunc(Symbol("handle"), DataHandle);
    DataRegisterFunc(Symbol("handle_ret"), DataHandleRet);
    DataRegisterFunc(Symbol("contains"), DataContains);
    DataRegisterFunc(Symbol("export"), DataExport);
    DataRegisterFunc(Symbol("exit"), DataExit);
    DataRegisterFunc(Symbol("find"), DataFind);
    DataRegisterFunc(Symbol("find_exists"), DataFindExists);
    DataRegisterFunc(Symbol("find_elem"), DataFindElem);
    DataRegisterFunc(Symbol("find_obj"), DataFindObj);
    DataRegisterFunc(Symbol("basename"), DataBasename);
    DataRegisterFunc(Symbol("dirname"), DataDirname);
    DataRegisterFunc(Symbol("has_substr"), DataHasSubStr);
    DataRegisterFunc(Symbol("has_any_substr"), DataHasAnySubStr);
    DataRegisterFunc(Symbol("find_substr"), DataFindSubStr);
    DataRegisterFunc(Symbol("strlen"), DataStrlen);
    DataRegisterFunc(Symbol("str_elem"), DataStrElem);
    DataRegisterFunc(Symbol("search_replace"), DataSearchReplace);
    DataRegisterFunc(Symbol("substr"), DataSubStr);
    DataRegisterFunc(Symbol("strcat"), DataStrCat);
    DataRegisterFunc(Symbol("string_flags"), DataStringFlags);
    DataRegisterFunc(Symbol("tolower"), DataStrToLower);
    DataRegisterFunc(Symbol("toupper"), DataStrToUpper);
    DataRegisterFunc(Symbol("strieq"), DataStrIEq);
    DataRegisterFunc(Symbol("push_back"), DataPushBack);
    DataRegisterFunc(Symbol("sort"), DataSort);
    DataRegisterFunc(Symbol("var"), DataVar);
    DataRegisterFunc(Symbol("set_var"), DataSetVar);
    DataRegisterFunc(Symbol("pack_color"), DataPackColor);
    DataRegisterFunc(Symbol("unpack_color"), DataUnpackColor);
    DataRegisterFunc(Symbol("set_this"), OnSetThis);
    DataRegisterFunc(Symbol("macro_elem"), DataMacroElem);
    DataRegisterFunc(Symbol("merge_dirs"), DataMergeDirs);
    DataRegisterFunc(Symbol("quote"), DataQuote);
    DataRegisterFunc(Symbol("'"), DataQuote);
    DataRegisterFunc(Symbol("quasiquote"), DataQuasiquote);
    DataRegisterFunc(Symbol("`"), DataQuasiquote);
    DataRegisterFunc(Symbol("unquote"), DataUnquote);
    DataRegisterFunc(Symbol(","), DataUnquote);
    DataRegisterFunc(Symbol("get_date_time"), DataGetDateTime);
    DataRegisterFunc(Symbol("with"), DataWith);
    DataRegisterFunc(Symbol("type"), DataGetType);
    DataRegisterFunc(Symbol("object_list"), DataObjectList);
    DataRegisterFunc(Symbol("file_list"), DataFileList);
    DataRegisterFunc(Symbol("file_list_paths"), DataFileListPaths);
    DataRegisterFunc(Symbol("disable_notify"), DataDisableNotify);
    DataRegisterFunc(Symbol("filter_notify"), DataFilterNotify);
}