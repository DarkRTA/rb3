#include "data.hpp"
#include "symbol.hpp"
#include "common.hpp"
#include "file_ops.hpp"
#include "string.hpp"
#include "std/string.h"
#include "vector3.hpp"

extern void DataRegisterFunc(Symbol, DataNode (*)(DataArray *));

// fn_80320470
extern DataNode DataReplaceObject(DataArray *);
// fn_8032056C
extern DataNode DataNextName(DataArray *);
// fn_8031B6C0
extern DataNode DataPrintf(DataArray *);
// fn_8031B62C
extern DataNode DataSprintf(DataArray *);

// fn_8031B7DC
DataNode DataSprint(DataArray *da)
{
	String str;
	for (int i = 1; i < da->GetNodeCount(); i++) {
		DataNode *dn = EvaluateNodeAtIndex(da, i);
		dn->Print(str, true);
	}
	return DataNode(str.c_str());
}

// fn_8031B504
// extern DataNode DataFuncObj::New(DataArray*);

// fn_8031DC40
DataNode DataGetElem(DataArray *da)
{
	int i = da->GetIntAtIndex(2);
	DataArray *a = da->GetArrayAtIndex(1);
	DataNode *dn = a->GetNodeAtIndex(i);
	return DataNode(*dn);
}

// fn_8031DCA4
DataNode DataGetLastElem(DataArray *da)
{
	DataArray *a = da->GetArrayAtIndex(1);
	int b = a->GetNodeCount();
	return DataNode(*a->GetNodeAtIndex(a->GetNodeCount() - 1));
}

// fn_8031DA1C
extern DataNode DataForEach(DataArray *);
// fn_8031DB20
extern DataNode DataForEachInt(DataArray *);

// fn_8031CA14
DataNode DataMin(DataArray* da){
	DataNode* dn1 = EvaluateNodeAtIndex(da, 1);
	DataNode* dn2 = EvaluateNodeAtIndex(da, 2);
	if(dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat){
		return DataNode(Minimum(dn1->LiteralFloat(da), dn2->LiteralFloat(da)));
	}
	else return DataNode(Minimum(dn1->LiteralInt(da), dn2->LiteralInt(da)));
}

// fn_8031CAF0
DataNode DataMax(DataArray* da){
	DataNode* dn1 = EvaluateNodeAtIndex(da, 1);
	DataNode* dn2 = EvaluateNodeAtIndex(da, 2);
	if(dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat){
		return DataNode(Maximum(dn1->LiteralFloat(da), dn2->LiteralFloat(da)));
	}
	else return DataNode(Maximum(dn1->LiteralInt(da), dn2->LiteralInt(da)));
}

// fn_8031CBCC
DataNode DataAbs(DataArray *da)
{
	DataNode *dn = EvaluateNodeAtIndex(da, 1);
	float f = AbsThunk(dn->LiteralFloat(da));
	if (dn->GetType() == kDataInt) {
		return DataNode((int)f);
	} else
		return DataNode(f);
}

// fn_8031CC5C
DataNode DataAdd(DataArray *da)
{
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
        sum_int += dn->GetIntVal();
    }
    if(i == cnt) return DataNode(sum_int);
    for(i++; i < cnt; i++){
        sum_f += da->GetFloatAtIndex(i);
    }
    return DataNode(sum_f);
}

// fn_8031CD70
extern DataNode DataAddEq(DataArray *);

// fn_8031CDF4
DataNode DataSub(DataArray *da)
{
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
extern DataNode DataSubEq(DataArray *);

// fn_8031CF24
DataNode DataMean(DataArray *da)
{
	float sum = 0.0;
	int cnt = da->GetNodeCount();
	for (int i = 1; i < cnt; i++) {
		sum += da->GetFloatAtIndex(i);
	}
	return DataNode(sum / (cnt - 1));
}

// fn_8031CFD0
DataNode DataClamp(DataArray* da){
	DataNode* dn1 = EvaluateNodeAtIndex(da, 1);
	DataNode* dn2 = EvaluateNodeAtIndex(da, 2);
	DataNode* dn3 = EvaluateNodeAtIndex(da, 3);
	if(dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat || dn3->GetType() == kDataFloat){
		return DataNode(Clamp(dn1->LiteralFloat(da), dn2->LiteralFloat(da), dn3->LiteralFloat(da)));
	}
	else return DataNode(Clamp(dn1->LiteralInt(da), dn2->LiteralInt(da), dn3->LiteralInt(da)));
}

// fn_8031D180
extern DataNode DataClampEq(DataArray *);

// fn_8031D204
DataNode DataMultiply(DataArray *da)
{
	DataNode *dn1 = EvaluateNodeAtIndex(da, 1);
	DataNode *dn2 = EvaluateNodeAtIndex(da, 2);
	if (dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat) {
		return DataNode(dn1->LiteralFloat(da) * dn2->LiteralFloat(da));
	} else {
		return DataNode(dn1->LiteralInt(da) * dn2->LiteralInt(da));
	}
}

// fn_8031D2DC
extern DataNode DataMultiplyEq(DataArray *);

// fn_8031D360
DataNode DataDivide(DataArray *da)
{
	return DataNode(da->GetFloatAtIndex(1) / da->GetFloatAtIndex(2));
}

// fn_8031D3CC
extern DataNode DataDivideEq(DataArray *);

// fn_8031D450
DataNode DataSqrt(DataArray* da){
	return DataNode(GetSqrtAsFloat(da->GetFloatAtIndex(1)));
}

// fn_8031D490
DataNode DataMod(DataArray* da){
	DataNode* dn1 = EvaluateNodeAtIndex(da, 1);
	DataNode* dn2 = EvaluateNodeAtIndex(da, 2);
	if(dn1->GetType() == kDataFloat || dn2->GetType() == kDataFloat){
		return DataNode(Modulo(dn1->LiteralFloat(da), dn2->LiteralFloat(da)));
	}
	else return DataNode(Modulo(dn1->LiteralInt(da), dn2->LiteralInt(da)));
}

// fn_8031D56C
DataNode DataDist(DataArray* da){
	Vector3 vec(da->GetFloatAtIndex(1) - da->GetFloatAtIndex(4), 
         da->GetFloatAtIndex(2) - da->GetFloatAtIndex(5), 
         da->GetFloatAtIndex(3) - da->GetFloatAtIndex(6));
    
    return DataNode(GetSqrtAsFloat(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z));
}

// fn_8031D664
DataNode DataSymbol(DataArray* da){
	Symbol s = da->ForceSymAtIndex(1);
	return DataNode(s);
}

// fn_8031D700
extern DataNode DataInt(DataArray *);

extern char lbl_808E4478[2];
// fn_8031D6A8
DataNode DataChar(DataArray *da)
{
	DataNode *dn = EvaluateNodeAtIndex(da, 1);
	lbl_808E4478[0] = dn->Int(nullptr);
	lbl_808E4478[1] = 0;
	return DataNode(lbl_808E4478);
}

// fn_8031D7C4
DataNode DataRound(DataArray *da)
{
	DataNode *dn = EvaluateNodeAtIndex(da, 1);
	return DataNode(Round(dn->LiteralFloat(nullptr)));
}

// fn_8031D810
DataNode DataFloor(DataArray *da)
{
	return DataNode(FloorThunk(da->GetFloatAtIndex(1)));
}

// fn_8031D850
DataNode DataCeil(DataArray *da)
{
	return DataNode(CeilThunk(da->GetFloatAtIndex(1)));
}

// fn_8031B86C
extern DataNode DataSet(DataArray *);

// fn_8031B970
DataNode DataIfElse(DataArray *da)
{
	DataNode *dn = da->GetNodeAtIndex(1);
	if (dn->NotNull()) {
		return DataNode(*EvaluateNodeAtIndex(da, 2));
	} else {
		return DataNode(*EvaluateNodeAtIndex(da, 3));
	}
}

// fn_8031B9F0
extern DataNode DataIf(DataArray *);
// fn_8031BA98
extern DataNode DataUnless(DataArray *);

bool DataNodeIsNull(DataNode *dn)
{
	return (!dn->NotNull());
}

// fn_8031BB68
DataNode DataEq(DataArray *da)
{
	DataNode *dn1 = EvaluateNodeAtIndex(da, 1);
	DataNode *dn2 = EvaluateNodeAtIndex(da, 2);
	return DataNode(dn1->operator==(*dn2));
}

// fn_8031BCC8
DataNode DataNe(DataArray *da)
{
	DataNode dn = DataEq(da);
	return DataNode(dn.GetIntVal() == 0);
}

// fn_8031BD1C
DataNode DataLe(DataArray *da)
{
	return DataNode(da->GetFloatAtIndex(1) <= da->GetFloatAtIndex(2));
}

// fn_8031BD8C
DataNode DataLt(DataArray *da)
{
	return DataNode(da->GetFloatAtIndex(1) < da->GetFloatAtIndex(2));
}

// fn_8031BDF8
DataNode DataGe(DataArray *da)
{
	return DataNode(da->GetFloatAtIndex(1) >= da->GetFloatAtIndex(2));
}

// fn_8031BE68
DataNode DataGt(DataArray *da)
{
	return DataNode(da->GetFloatAtIndex(1) > da->GetFloatAtIndex(2));
}

// fn_8031BED4
DataNode DataNot(DataArray *da)
{
	return DataNode(DataNodeIsNull(da->GetNodeAtIndex(1)));
}

// fn_8031BF18
DataNode DataAnd(DataArray *da)
{
	for (int i = 1; i < da->GetNodeCount(); i++) {
		if (DataNodeIsNull(da->GetNodeAtIndex(i))) {
			return DataNode(0);
		}
	}
	return DataNode(1);
}

// fn_8031BF9C
DataNode DataOr(DataArray *da)
{
	for (int i = 1; i < da->GetNodeCount(); i++) {
		DataNode *dn = da->GetNodeAtIndex(i);
		if (dn->NotNull())
			return DataNode(1);
	}
	return DataNode(0);
}

// fn_8031C020
DataNode DataXor(DataArray *da)
{
	return DataNode(
		da->GetNodeAtIndex(1)->NotNull() != da->GetNodeAtIndex(2)->NotNull());
}

// fn_8031C08C
DataNode DataBitAnd(DataArray *da)
{
	int res = da->GetIntAtIndex(1);
	for (int i = 2; i < da->GetNodeCount(); i++) {
		res &= da->GetIntAtIndex(i);
	}
	return DataNode(res);
}

// fn_8031C108
extern DataNode DataAndEqual(DataArray *);
// fn_8031C224
extern DataNode DataMaskEqual(DataArray *);

// fn_8031C45C
DataNode DataBitOr(DataArray *da)
{
	int res = da->GetIntAtIndex(1);
	for (int i = 2; i < da->GetNodeCount(); i++) {
		res |= da->GetIntAtIndex(i);
	}
	return DataNode(res);
}

// fn_8031C340
extern DataNode DataOrEqual(DataArray *);

// fn_8031C4D8
DataNode DataBitXor(DataArray *da)
{
	return DataNode(da->GetIntAtIndex(1) ^ da->GetIntAtIndex(2));
}

// fn_8031C534
DataNode DataBitNot(DataArray *da)
{
	return DataNode(~da->GetIntAtIndex(1));
}

// fn_8031C5B8
int GetLowestBit(int i)
{
	if (i == 0)
		return 0;
	int j = 1;
	while (!(j & i))
		j *= 2;
	return j;
}

// fn_8031C574
extern DataNode DataLowestBit(DataArray *);
DataNode DataLowestBit(DataArray *da)
{
	return DataNode(GetLowestBit(da->GetIntAtIndex(1)));
}

// fn_8031C5E4
DataNode DataCountBits(DataArray* da){
	return DataNode(CountBits(da->GetIntAtIndex(1)));
}

// fn_8031C628
extern DataNode DataWhile(DataArray *);
// fn_8031C904
extern DataNode DataDo(DataArray *);
// fn_8031D8EC
extern DataNode DataNew(DataArray *);
// fn_8031D890
extern DataNode DataDelete(DataArray *);
// fn_8031DD0C
extern DataNode DataObject(DataArray *);
// fn_8031DE08
extern DataNode DataExists(DataArray *);
// fn_8031DEB8
extern DataNode DataLocalize(DataArray *);
// fn_8031DF18
extern DataNode DataLocalizeSeparatedInt(DataArray *);
// fn_8031DF5C
extern DataNode DataLocalizeFloat(DataArray *);

// fn_8031DFC8
DataNode DataStartsWith(DataArray *da)
{
	int i;
	if (da->GetNodeCount() > 3)
		i = da->GetIntAtIndex(3);
	else
		i = strlen(da->GetStrAtIndex(2));
	return DataNode(!strncmp(da->GetStrAtIndex(1), da->GetStrAtIndex(2), i));
}

// fn_8031B764
extern DataNode DataPrint(DataArray *);
// fn_8031E06C
extern DataNode DataTime(DataArray *);

extern int RandomInt(int, int);
// fn_8031E170
DataNode DataRandomInt(DataArray *da)
{
	return DataNode(RandomInt(da->GetIntAtIndex(1), da->GetIntAtIndex(2)));
}

extern float RandomFloat();
extern float RandomFloat(float, float);
// fn_8031E1D4
DataNode DataRandomFloat(DataArray *da)
{
	if (da->GetNodeCount() > 1) {
		return DataNode(
			RandomFloat(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2)));
	} else
		return DataNode(RandomFloat());
}

// fn_8031E25C
DataNode DataRandomElem(DataArray *da)
{
	DataArray *a = da->GetArrayAtIndex(1);
	int b = a->GetNodeCount();
	int c_a = a->GetNodeCount();
	DataNode *dn = a->GetNodeAtIndex(RandomInt(0, c_a));
	return DataNode(*dn);
}

// fn_8031E2CC
DataNode DataRandom(DataArray *da)
{
	int i = da->GetNodeCount();
	int j = RandomInt(1, i);
	DataNode *dn = EvaluateNodeAtIndex(da, j);
	return DataNode(*dn);
}

extern void SeedRand(int);
// fn_8031E32C
DataNode DataRandomSeed(DataArray *da)
{
	SeedRand(da->GetIntAtIndex(1));
	return DataNode(0);
}

// fn_8031E370
DataNode DataNotify(DataArray *da)
{
	return DataNode(0);
}

// fn_8031E378
DataNode DataNotifyBeta(DataArray *da)
{
	return DataNode(0);
}

// fn_8031E380
DataNode DataFail(DataArray *da)
{
	return DataNode(0);
}

// fn_8031E388
DataNode DataNotifyOnce(DataArray *da)
{
	return DataNode(0);
}

// fn_8031E470
extern DataNode DataSwitch(DataArray *);
// fn_8031E390
extern DataNode DataCond(DataArray *);

// fn_8031E5FC
DataNode DataInsertElems(DataArray *da)
{
	da->GetArrayAtIndex(1)->InsertNodes(
		da->GetIntAtIndex(2),
		da->GetArrayAtIndex(3));
	return DataNode(0);
}

// fn_8031E674
DataNode DataInsertElem(DataArray *da)
{
	DataArray *a = da->GetArrayAtIndex(1);
	int i = da->GetIntAtIndex(2);
	DataNode *dn = EvaluateNodeAtIndex(da, 3);
	a->Insert(i, *dn);
	return DataNode(0);
}

// fn_8031E6F0
extern TextStream *TheDebug;
extern DataNode DataPrintArray(DataArray *);
DataNode DataPrintArray(DataArray *da)
{
	DataArray *a = da->GetArrayAtIndex(1);
	a->Print(*TheDebug, (DataType)0x10, false);
	return DataNode(0);
}

// fn_8031E744
extern DataNode DataSize(DataArray *);

// fn_8031E7D4
DataNode DataRemoveElem(DataArray *da)
{
	DataArray *a = da->GetArrayAtIndex(1);
	DataNode *dn = EvaluateNodeAtIndex(da, 2);
	a->Remove(*dn);
	return DataNode(0);
}

// fn_8031E83C
DataNode DataResize(DataArray *da)
{
	int i = da->GetIntAtIndex(2);
	DataArray *a = da->GetArrayAtIndex(1);
	a->Resize(i);
	return DataNode(0);
}

// fn_8031E8A0
extern DataNode DataNewArray(DataArray *);

// fn_8031E9A0
DataNode DataSetElem(DataArray *da)
{
	DataArray *a = da->GetArrayAtIndex(1);
	int i = da->GetIntAtIndex(2);
	DataNode *dn = EvaluateNodeAtIndex(da, 3);
	DataNode *dn2 = a->GetNodeAtIndex(i);
	dn2->operator=(*dn);
	return DataNode(*dn2);
}

// fn_8031EA64
DataNode DataEval(DataArray *da)
{
	DataNode *dn = EvaluateNodeAtIndex(da, 1);
	return DataNode(*dn->Evaluate());
}

// fn_8031EB54
float InverseLerp(float f1, float f2, float f3){
	if(f2 != f1) return (f3 - f1) / (f2 - f1);
	else return 1.0f;
}

// fn_8031EAA8
DataNode DataReverseInterp(DataArray* da){
	float ext = InverseLerp(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2), da->GetFloatAtIndex(3));
	return DataNode(Clamp(0.0f, 1.0f, ext));
}

// fn_8031EB78
DataNode DataInterp(DataArray* da){
	return DataNode(Interp(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2), da->GetFloatAtIndex(3)));
}

// fn_8031EBFC
extern DataNode DataInc(DataArray *);
// fn_8031ECF8
extern DataNode DataDec(DataArray *);
// fn_8031F1D0
extern DataNode DataRun(DataArray *);

// fn_8031F27C
extern DataNode OnReadFile(DataArray *);

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
DataNode DataFindElem(DataArray* da){
	DataArray* arr = da->GetArrayAtIndex(1);
	arr->IncRefCount();
	DataNode* dn = EvaluateNodeAtIndex(da, 2);
	for(int i = 0; i < arr->GetNodeCount(); i++){
		if(!(arr->GetNodeAtIndex(i)->operator==(*dn))) continue;
		if(da->GetNodeCount() > 3){
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
DataNode DataBasename(DataArray *da)
{
	char *base = FileGetBase((char *)da->GetStrAtIndex(1), '\0');
	return DataNode(base);
}

// fn_8031F808
DataNode DataDirname(DataArray *da)
{
	char* pFilepath = FileGetPath((char *)da->GetStrAtIndex(1), '\0');
	int i = String(pFilepath).find_last_of("/");
	return DataNode(&pFilepath[i == String::npos ? 0 : i + 1]);
}

// fn_8031F8A8
DataNode DataHasSubStr(DataArray *da)
{
	return DataNode((int)strstr(da->GetStrAtIndex(1), da->GetStrAtIndex(2)));
}

// fn_8031F90C
DataNode DataHasAnySubStr(DataArray *da)
{
	DataArray *arr = da->GetArrayAtIndex(2);
	for (int i = 0; i < arr->GetNodeCount(); i++) {
		if (strstr(da->GetStrAtIndex(1), arr->GetStrAtIndex(i))) {
			return DataNode(1);
		}
	}
	return DataNode(0);
}

// fn_8031F9B4
DataNode DataFindSubStr(DataArray *da)
{
	String str(da->GetStrAtIndex(1));
	return DataNode(str.find(da->GetStrAtIndex(2)));
}

// fn_8031FD80
DataNode DataStrlen(DataArray *da)
{
	int len = strlen(da->GetStrAtIndex(1));
	return DataNode(len);
}

extern unsigned short lbl_808E5860;
// fn_8031FDC4
DataNode DataStrElem(DataArray *da)
{
    unsigned short c = lbl_808E5860;
    *(char*)&c = da->GetStrAtIndex(1)[da->GetIntAtIndex(2)];
	return DataNode(Symbol((char*)&c));
}

extern "C" DataNode *fn_800E7878(DataArray *, int);

// fn_8031FED0
DataNode DataSearchReplace(DataArray *da)
{
	char *str;
	bool changed = SearchReplace(
		da->GetStrAtIndex(1),
		da->GetStrAtIndex(2),
		da->GetStrAtIndex(3),
		str);
	DataNode dn(str);
	DataNode *asdf = fn_800E7878(da, 4);
	return DataNode(changed);
}

// fn_8031FA30
DataNode DataSubStr(DataArray *da)
{
	String str(da->GetStrAtIndex(1));
	int i = da->GetIntAtIndex(2);
	int j = da->GetIntAtIndex(3);
	return DataNode(str.substr(i, j));
}

// fn_8031FAD0
extern DataNode DataStrCat(DataArray *);

// fn_8031FBAC
DataNode DataStringFlags(DataArray *da)
{
	int i = da->GetIntAtIndex(1);
	DataArray *a = da->GetArrayAtIndex(2);
	String s('\0');
	for (int j = 0; j < a->GetNodeCount(); j++) {
		Symbol sym((char *)a->GetStrAtIndex(j));
	}
	return DataNode(s);
}

// fn_8031FCC0
DataNode DataStrToLower(DataArray *da)
{
	String str(da->GetStrAtIndex(1));
	str.ToLower();
	return DataNode(str);
}

// fn_8031FD20
DataNode DataStrToUpper(DataArray *da)
{
	String str(da->GetStrAtIndex(1));
	str.ToUpper();
	return DataNode(str);
}

// fn_8031FEA8
bool StrICmpIsDifferent(const char *c, const char *d)
{
	return !stricmp(c, d);
}

// fn_8031FE44
DataNode DataStrIEq(DataArray *da)
{
	return DataNode(
		StrICmpIsDifferent(da->GetStrAtIndex(1), da->GetStrAtIndex(2)));
}

// fn_8031FF7C
DataNode DataPushBack(DataArray *da)
{
	DataArray *a = da->GetArrayAtIndex(1);
	int cnt = a->GetNodeCount();
	a->Resize(cnt + 1);
	*a->GetNodeAtIndex(cnt) = *EvaluateNodeAtIndex(da, 2);
	return DataNode(0);
}

// fn_80320004
DataNode DataSort(DataArray *da)
{
	DataArray *a = da->GetArrayAtIndex(1);
	a->SortNodes();
	return DataNode(0);
}

// fn_8031C6C4
extern DataNode DataVar(DataArray *);
// fn_8031B904
extern DataNode DataSetVar(DataArray *);

// fn_8031C710
DataNode DataPackColor(DataArray* da){
    return DataNode(
        ((int)(da->GetFloatAtIndex(3) * 255.0f) & 0xFF) << 0x10 | 
        ((int)(da->GetFloatAtIndex(2) * 255.0f) & 0xFF) << 8  |
        ((int)(da->GetFloatAtIndex(1) * 255.0f) & 0xFF)
    );
}

// fn_8031C7C4
extern DataNode DataUnpackColor(DataArray *);
// fn_803200E8
extern DataNode OnSetThis(DataArray *);
// fn_80320150
extern DataNode DataMacroElem(DataArray *);
// fn_8032024C
extern DataNode DataMergeDirs(DataArray *);

// fn_8031EA24
DataNode DataQuote(DataArray *da)
{
	return DataNode(*da->GetNodeAtIndex(1));
}

// fn_8032080C
extern DataNode DataQuasiquote(DataArray *);

// fn_8032084C
DataNode DataUnquote(DataArray *da)
{
	return DataNode(*EvaluateNodeAtIndex(da, 1));
}

// fn_8032088C
extern DataNode DataGetDateTime(DataArray *);
// fn_8032008C
extern DataNode DataWith(DataArray *);

// fn_80320048
DataNode DataGetType(DataArray *da)
{
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
DataNode DataDisableNotify(DataArray *da)
{
	return DataNode(0);
}

// fn_80320CD4
DataNode DataFilterNotify(DataArray *da)
{
	return DataNode(0);
}

// fn_80320CDC
void DataInitFuncs()
{
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
}