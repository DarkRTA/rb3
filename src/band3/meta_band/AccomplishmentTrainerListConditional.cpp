#include "meta_band/AccomplishmentTrainerListConditional.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentTrainerConditional.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

AccomplishmentTrainerListConditional::AccomplishmentTrainerListConditional(DataArray* arr, int i) : AccomplishmentTrainerConditional(arr, i) {
    Configure(arr);
}

AccomplishmentTrainerListConditional::~AccomplishmentTrainerListConditional(){

}

void AccomplishmentTrainerListConditional::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x1B);
    DataArray* pEntryArray = i_pConfig->FindArray(lessons, true);
    MILO_ASSERT(pEntryArray->Size() > 1, 0x22);
    for(int i = 1; i < pEntryArray->Size(); i++){
        Symbol sym = pEntryArray->Node(i).Sym();
        mLessons.push_back(sym);
    }
}

AccomplishmentType AccomplishmentTrainerListConditional::GetType() const { return kAccomplishmentTypeTrainerListConditional; }

bool AccomplishmentTrainerListConditional::IsFulfilled(BandProfile* profile) const {
    for(std::vector<Symbol>::const_iterator it = mLessons.begin(); it != mLessons.end(); ++it){
        if(!CheckConditionsForLesson(profile, *it)) return false;
    }
    return true;
}

int AccomplishmentTrainerListConditional::GetNumCompletedLessons(BandProfile* profile) const {
    int num = 0;
    for(std::vector<Symbol>::const_iterator it = mLessons.begin(); it != mLessons.end(); ++it){
        if(CheckConditionsForLesson(profile, *it)) num++;
    }
    return num;
}

bool AccomplishmentTrainerListConditional::InqIncrementalSymbols(BandProfile* profile, std::vector<Symbol>& syms) const {
    syms = mLessons;
    return true;
}

int AccomplishmentTrainerListConditional::GetTotalNumLessons() const { return mLessons.size(); }