#include "data.hpp"
#include "symbol.hpp"

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
extern DataNode DataSprint(DataArray*);
// fn_8031B504
// extern DataNode DataFuncObj::New(DataArray*);
// fn_8031DC40
extern DataNode DataGetElem(DataArray*);
// fn_8031DCA4
extern DataNode DataGetLastElem(DataArray*);
// fn_8031DA1C
extern DataNode DataForEach(DataArray*);
// fn_8031DB20
extern DataNode DataForEachInt(DataArray*);
// fn_8031CA14
extern DataNode DataMin(DataArray*);
// fn_8031CAF0
extern DataNode DataMax(DataArray*);
// fn_8031CBCC
extern DataNode DataAbs(DataArray*);
// fn_8031CC5C
extern DataNode DataAdd(DataArray*);
// fn_8031CD70
extern DataNode DataAddEq(DataArray*);
// fn_8031CDF4
extern DataNode DataSub(DataArray*);
// fn_8031D0FC
extern DataNode DataSubEq(DataArray*);
// fn_8031CF24
extern DataNode DataMean(DataArray*);
// fn_8031CFD0
extern DataNode DataClamp(DataArray*);
// fn_8031D180
extern DataNode DataClampEq(DataArray*);
// fn_8031D204
extern DataNode DataMultiply(DataArray*);
// fn_8031D2DC
extern DataNode DataMultiplyEq(DataArray*);
// fn_8031D360
extern DataNode DataDivide(DataArray*);
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
// fn_8031D6A8
extern DataNode DataChar(DataArray*);
// fn_8031D7C4
extern DataNode DataRound(DataArray*);
// fn_8031D810
extern DataNode DataFloor(DataArray*);
// fn_8031D850
extern DataNode DataCeil(DataArray*);
// fn_8031B86C
extern DataNode DataSet(DataArray*);
// fn_8031B970
extern DataNode DataIfElse(DataArray*);
// fn_8031B9F0
extern DataNode DataIf(DataArray*);
// fn_8031BA98
extern DataNode DataUnless(DataArray*);
// fn_8031BB68
extern DataNode DataEq(DataArray*);
// fn_8031BCC8
extern DataNode DataNe(DataArray*);
// fn_8031BD1C
extern DataNode DataLe(DataArray*);
// fn_8031BD8C
extern DataNode DataLt(DataArray*);
// fn_8031BDF8
extern DataNode DataGe(DataArray*);
// fn_8031BE68
extern DataNode DataGt(DataArray*);
// fn_8031BED4
extern DataNode DataNot(DataArray*);
// fn_8031BF18
extern DataNode DataAnd(DataArray*);
// fn_8031BF9C
extern DataNode DataOr(DataArray*);
// fn_8031C020
extern DataNode DataXor(DataArray*);
// fn_8031C08C
extern DataNode DataBitAnd(DataArray*);
// fn_8031C108
extern DataNode DataAndEqual(DataArray*);
// fn_8031C224
extern DataNode DataMaskEqual(DataArray*);
// fn_8031C45C
extern DataNode DataBitOr(DataArray*);
// fn_8031C340
extern DataNode DataOrEqual(DataArray*);
// fn_8031C4D8
extern DataNode DataBitXor(DataArray*);
// fn_8031C534
extern DataNode DataBitNot(DataArray*);
// fn_8031C574
extern DataNode DataLowestBit(DataArray*);
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
extern DataNode DataStartsWith(DataArray*);
// fn_8031B764
extern DataNode DataPrint(DataArray*);
// fn_8031E06C
extern DataNode DataTime(DataArray*);
// fn_8031E170
extern DataNode DataRandomInt(DataArray*);
// fn_8031E1D4
extern DataNode DataRandomFloat(DataArray*);
// fn_8031E25C
extern DataNode DataRandomElem(DataArray*);
// fn_8031E2CC
extern DataNode DataRandom(DataArray*);
// fn_8031E32C
extern DataNode DataRandomSeed(DataArray*);
// fn_8031E370
extern DataNode DataNotify(DataArray*);
// fn_8031E378
extern DataNode DataNotifyBeta(DataArray*);
// fn_8031E380
extern DataNode DataFail(DataArray*);
// fn_8031E388
extern DataNode DataNotifyOnce(DataArray*);
// fn_8031E470
extern DataNode DataSwitch(DataArray*);
// fn_8031E390
extern DataNode DataCond(DataArray*);
// fn_8031E5FC
extern DataNode DataInsertElems(DataArray*);
// fn_8031E674
extern DataNode DataInsertElem(DataArray*);
// fn_8031E6F0
extern DataNode DataPrintArray(DataArray*);
// fn_8031E744
extern DataNode DataSize(DataArray*);
// fn_8031E7D4
extern DataNode DataRemoveElem(DataArray*);
// fn_8031E83C
extern DataNode DataResize(DataArray*);
// fn_8031E8A0
extern DataNode DataNewArray(DataArray*);
// fn_8031E9A0
extern DataNode DataSetElem(DataArray*);
// fn_8031EA64
extern DataNode DataEval(DataArray*);

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
}