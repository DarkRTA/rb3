#include "TourReward.h"
#include "decomp.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "utl/Symbol.h"

TourReward::TourReward() : mRewards(NULL) {}

TourReward::~TourReward() {}

void TourReward::Init(const DataArray* i_pConfig) { mRewards = const_cast<DataArray*>(i_pConfig); }

void TourReward::ApplyRewardEntry(TourProgress* tp, DataArray* da) const {
    static class Symbol sym_band = "band";
    static class Symbol sym_perf = "perf";
    Symbol s = da->Sym(0);
    if (s == sym_band) {
        DataArray* pEntryArray = da->Array(1);
        MILO_ASSERT(pEntryArray, 42);
        ApplyRewardEntry(tp, tp->GetTourProperties(), pEntryArray);
    } else if (s == sym_perf) {
        DataArray* pEntryArray = da->Array(1);
        MILO_ASSERT(pEntryArray, 49);
        ApplyRewardEntry(tp, tp->GetPerformanceProperties(), pEntryArray);
    } else {
        ApplyRewardEntry(tp, tp->GetTourProperties(), da);
    }
}
#ifdef MILO_DEBUG
#pragma push
#pragma pool_data off
#endif

void TourReward::ApplyRewardEntry(TourProgress* tp, TourPropertyCollection& tpc, DataArray* da) const {
    static class Symbol sym_add = "+";
    static class Symbol sym_subtract = "-";
    static class Symbol sym_multiply = "*";
    static class Symbol sym_divide = "/";
    Symbol s = da->Sym(0);
    if (s == sym_add) {
        ApplyAddReward(tp, tpc, da);
    } else if (s == sym_subtract) {
        ApplySubtractReward(tp, tpc, da);
    } else if (s == sym_multiply) {
        ApplyMultiplyReward(tp, tpc, da);
    } else if (s == sym_divide) {
        ApplyDivideReward(tp, tpc, da);
    } else {
        MILO_WARN("Unknown reward entry (%s).", s.Str());
    }
}
#ifdef MILO_DEBUG
#pragma pop
#endif

void TourReward::Apply(TourProgress* tp) const {
    if (mRewards) {
        for (int i = 1; i < mRewards->Size(); i++) 
            ApplyRewardEntry(tp, mRewards->Array(i));
        tp->HandleTourRewardApplied();
    }
}

void TourReward::ApplyRewardValue(TourProgress*, TourPropertyCollection& pc, Symbol s, float f) const {
    pc.GetPropertyValue(s);
    pc.SetPropertyValue(s, f);
}

void TourReward::ApplyAddReward(TourProgress* tp, TourPropertyCollection& pc, DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 129);
    Symbol s = i_pArray->Sym(1);
#ifdef MILO_DEBUG
    ValidatePropertyModification(s);
#endif
    float f = i_pArray->Float(2) + pc.GetPropertyValue(s);
    ApplyRewardValue(tp, pc, s, f);
}

void TourReward::ApplySubtractReward(TourProgress* tp, TourPropertyCollection& pc, DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 149);
    Symbol s = i_pArray->Sym(1);
#ifdef MILO_DEBUG
    ValidatePropertyModification(s);
#endif
    float f = pc.GetPropertyValue(s) - i_pArray->Float(2);
    ApplyRewardValue(tp, pc, s, f);
}

void TourReward::ApplyMultiplyReward(TourProgress* tp, TourPropertyCollection& pc, DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 168);
    Symbol s = i_pArray->Sym(1);
#ifdef MILO_DEBUG
    ValidatePropertyModification(s);
#endif
    float f = i_pArray->Float(2) * pc.GetPropertyValue(s);
    ApplyRewardValue(tp, pc, s, f);
}

void TourReward::ApplyDivideReward(TourProgress* tp, TourPropertyCollection& pc, DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 187);
    Symbol s = i_pArray->Sym(1);
#ifdef MILO_DEBUG
    ValidatePropertyModification(s);
#endif
    float f = pc.GetPropertyValue(s) / i_pArray->Float(2);
    ApplyRewardValue(tp, pc, s, f);
}

#ifdef MILO_DEBUG
DECOMP_FORCEACTIVE(TourReward, "pProperty", "false\0", "o_rEntries.empty()")
#endif

void TourReward::ValidatePropertyModification(Symbol s) const {
    TourProperty* t = TheTour->GetTourProperty(s);
    if (t && t->IsAutomatic()) MILO_WARN("Trying to modify an automatic property with a reward! Property = %s\n", s.Str());
}
