#include "tour/TourCondition.h"
#include "obj/Data.h"
#include "os/Debug.h"

TourCondition::TourCondition() : mConds(0) {

}

TourCondition::~TourCondition(){

}

void TourCondition::Init(const DataArray* arr){
    mConds = arr;
}

bool TourCondition::IsMet(const TourProgress& tp) const {
    if(mConds) return IsAndConditionMet(tp, mConds);
    else return true;
}

#pragma push
#pragma pool_data off
bool TourCondition::IsConditionMet(const TourProgress& tp, const DataArray* arr) const {
    static Symbol sym_and("&&");
    static Symbol sym_or("||");
    static Symbol sym_not("!");
    static Symbol sym_band("band");
    static Symbol sym_perf("perf");
    Symbol sym = arr->Sym(0);
    if(sym == sym_and) return IsAndConditionMet(tp, arr);
    else if(sym == sym_or) return IsOrConditionMet(tp, arr);
    else if(sym == sym_not) return IsNotConditionMet(tp, arr);
    else if(sym == sym_band){
        DataArray* pEntryArray = arr->Array(1);
        MILO_ASSERT(pEntryArray, 0x49);
        return IsComparisonConditionMet(tp.GetTourProperties(), pEntryArray);
    }
    else if(sym == sym_perf){
        DataArray* pEntryArray = arr->Array(1);
        MILO_ASSERT(pEntryArray, 0x50);
        return IsComparisonConditionMet(tp.GetPerformanceProperties(), pEntryArray);
    }
    else return IsComparisonConditionMet(tp.GetTourProperties(), arr);
}

bool TourCondition::IsComparisonConditionMet(const TourPropertyCollection& coll, const DataArray* arr) const {
    static Symbol sym_greater(">");
    static Symbol sym_less("<");
    static Symbol sym_greater_equal(">=");
    static Symbol sym_less_equal("<=");
    static Symbol sym_equal("==");
    static Symbol sym_not_equal("!=");
    Symbol sym = arr->Sym(0);
    if(sym == sym_greater) return IsGreaterConditionMet(coll, arr);
    else if(sym == sym_less) return IsLessConditionMet(coll, arr);
    else if(sym == sym_greater_equal) return IsGreaterEqualConditionMet(coll, arr);
    else if(sym == sym_less_equal) return IsLessEqualConditionMet(coll, arr);
    else if(sym == sym_equal) return IsEqualConditionMet(coll, arr);
    else if(sym == sym_not_equal) return IsNotEqualConditionMet(coll, arr);
    else {
        MILO_WARN("Unknown condition (%s), treating as true.", sym.Str());
        return true;
    }
}
#pragma pop

bool TourCondition::IsAndConditionMet(const TourProgress& tp, const DataArray* arr) const {
    for(int i = 1; i < arr->Size(); i++){
        if(!IsConditionMet(tp, arr->Array(i))) return false;
    }
    return true;
}

bool TourCondition::IsOrConditionMet(const TourProgress& tp, const DataArray* arr) const {
    for(int i = 1; i < arr->Size(); i++){
        if(IsConditionMet(tp, arr->Array(i))) return true;
    }
    return false;
}

bool TourCondition::IsNotConditionMet(const TourProgress& tp, const DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 2, 0xAF);
    return !IsConditionMet(tp, i_pArray->Array(1));
}

bool TourCondition::IsGreaterConditionMet(const TourPropertyCollection& tp, const DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 0xB7);
    Symbol key = i_pArray->Sym(1);
    float val = i_pArray->Float(2);
    return tp.GetPropertyValue(key) > val;
}

bool TourCondition::IsLessConditionMet(const TourPropertyCollection& tp, const DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 0xC3);
    Symbol key = i_pArray->Sym(1);
    float val = i_pArray->Float(2);
    return tp.GetPropertyValue(key) < val;
}

bool TourCondition::IsGreaterEqualConditionMet(const TourPropertyCollection& tp, const DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 0xCF);
    Symbol key = i_pArray->Sym(1);
    float val = i_pArray->Float(2);
    return tp.GetPropertyValue(key) >= val;
}

bool TourCondition::IsLessEqualConditionMet(const TourPropertyCollection& tp, const DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 0xDB);
    Symbol key = i_pArray->Sym(1);
    float val = i_pArray->Float(2);
    return tp.GetPropertyValue(key) <= val;
}

bool TourCondition::IsEqualConditionMet(const TourPropertyCollection& tp, const DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 0xE7);
    Symbol key = i_pArray->Sym(1);
    return tp.GetPropertyValue(key) == i_pArray->Float(2);
}

bool TourCondition::IsNotEqualConditionMet(const TourPropertyCollection& tp, const DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 0xF3);
    Symbol key = i_pArray->Sym(1);
    return tp.GetPropertyValue(key) != i_pArray->Float(2);
}