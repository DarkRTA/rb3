#include "TourReward.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "tour/Tour.h"

TourReward::TourReward() : mRewards(NULL) {}

TourReward::~TourReward() {}

void TourReward::Init(const DataArray* i_pConfig) { mRewards = const_cast<DataArray*>(i_pConfig); }

void TourReward::ApplyRewardEntry(TourProgress*, DataArray*) const {

}

void TourReward::ApplyRewardEntry(TourProgress*, TourPropertyCollection&, DataArray*) const {

}

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
    ValidatePropertyModification(s);
    float f = i_pArray->Float(2) + pc.GetPropertyValue(s);
    ApplyRewardValue(tp, pc, s, f);
}

void TourReward::ApplySubtractReward(TourProgress* tp, TourPropertyCollection& pc, DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 149);
    Symbol s = i_pArray->Sym(1);
    ValidatePropertyModification(s);
    float f = pc.GetPropertyValue(s) - i_pArray->Float(2);
    ApplyRewardValue(tp, pc, s, f);
}

void TourReward::ApplyMultiplyReward(TourProgress* tp, TourPropertyCollection& pc, DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 168);
    Symbol s = i_pArray->Sym(1);
    ValidatePropertyModification(s);
    float f = i_pArray->Float(2) * pc.GetPropertyValue(s);
    ApplyRewardValue(tp, pc, s, f);
}

void TourReward::ApplyDivideReward(TourProgress* tp, TourPropertyCollection& pc, DataArray* i_pArray) const {
    MILO_ASSERT(i_pArray->Size() == 3, 187);
    Symbol s = i_pArray->Sym(1);
    ValidatePropertyModification(s);
    float f = pc.GetPropertyValue(s) / i_pArray->Float(2);
    ApplyRewardValue(tp, pc, s, f);
}

void TourReward::ValidatePropertyModification(Symbol s) const {
    TourProperty* t = TheTour->GetTourProperty(s);
    if (t && t->IsAutomatic()) MILO_WARN("Trying to modify an automatic property with a reward! Property = %s\n", s.Str());
}
