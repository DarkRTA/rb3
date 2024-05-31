#include "TourQuestGameRules.h"
#include "os/Debug.h"
#include "tour/TourGameRules.h"
#include "utl/Symbols.h"

TourQuestGameRules::TourQuestGameRules() : mModifier() {}
TourQuestGameRules::~TourQuestGameRules() {}

void TourQuestGameRules::Init(const DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 23);
    TourGameRules::Init(i_pConfig);
    mModifier.Init(i_pConfig->FindArray(modifiers, false));
}