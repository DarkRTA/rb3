#include "meta_band/LessonProvider.h"
#include "BandProfile.h"
#include "bandobj/CheckboxDisplay.h"
#include "meta_band/LessonMgr.h"
#include "meta_band/ProfileMgr.h"
#include "os/Debug.h"
#include "ui/UIListCustom.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

LessonProvider::LessonProvider() : mCategories(0), mLessons(0) {

}

LessonProvider::~LessonProvider(){

}

void LessonProvider::InitData(RndDir* dir){
    mCategoryMat = dir->Find<RndMat>("category.mat", false);
    mLessonMat = dir->Find<RndMat>("lesson.mat", false);
}

bool LessonProvider::IsActive(int i) const {
    return NumData() == 0 ? false : !GetLessonEntry(i).unk4;
}

void LessonProvider::Text(int, int idx, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(slot, 0x34);
    MILO_ASSERT(label, 0x35);
    const LessonEntry& entry = GetLessonEntry(idx);
    if(entry.unk4){
        if(slot->Matches("category")){
            label->SetTextToken(entry.unk0);
        }
        else if(slot->Matches("progress")){
            Symbol key = entry.unk0;
            LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
            MILO_ASSERT(pLessonMgr, 0x44);
            BandProfile* profile = TheProfileMgr.GetPrimaryProfile();
            if(profile){
                int count_completed = pLessonMgr->GetCompletedCountFromCategory(profile, key);
                int count = pLessonMgr->GetTotalCountFromCategory(key);
                label->SetTokenFmt(trainer_progress, count_completed, count);
            }
        }
        else label->SetTextToken(gNullStr);
    }
    else if(slot->Matches("lesson")){
        label->SetTextToken(entry.unk0);
    }
    else label->SetTextToken(gNullStr);
}

RndMat* LessonProvider::Mat(int, int idx, UIListMesh* slot) const {
    MILO_ASSERT(slot, 100);
    const LessonEntry& entry = GetLessonEntry(idx);
    if(slot->Matches("bg")){
        if(entry.unk4) return mCategoryMat;
        else return mLessonMat;
    }
    else return nullptr;
}

void LessonProvider::Custom(int, int idx, UIListCustom* slot, Hmx::Object* obj) const {
    MILO_ASSERT(slot, 0x79);
    const LessonEntry& entry = GetLessonEntry(idx);
    if(slot->Matches("checkbox")){
        CheckboxDisplay* pCheckboxDisplay = dynamic_cast<CheckboxDisplay*>(obj);
        MILO_ASSERT(pCheckboxDisplay, 0x80);
        if(entry.unk4) pCheckboxDisplay->SetShowing(false);
        else {
            pCheckboxDisplay->SetShowing(true);
            BandProfile* profile = TheProfileMgr.GetPrimaryProfile();
            if(profile){
                if(profile->IsLessonComplete(entry.unk0, 1.0f)) pCheckboxDisplay->SetChecked(true);
                else pCheckboxDisplay->SetChecked(false);
            }
        }
    }
}

Symbol LessonProvider::DataSymbol(int idx) const {
    return GetLessonEntry(idx).unk0;
}

int LessonProvider::NumData() const { return mLessonEntries.size(); }

void LessonProvider::Update(Symbol s){
    mLessonEntries.clear();
    LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0xB1);
    mCategories = pLessonMgr->GetCategoriesFromTrainer(s);
    MILO_ASSERT(mCategories, 0xB5);
    for(std::vector<Symbol>::iterator it = mCategories->begin(); it != mCategories->end(); ++it){
        Symbol cur = *it;
        mLessonEntries.push_back(LessonEntry(cur, true));
        mLessons = pLessonMgr->GetLessonsFromCategory(cur);
        MILO_ASSERT(mLessons, 0xC1);
        for(std::vector<Symbol>::iterator lit = mLessons->begin(); lit != mLessons->end(); ++lit){
            mLessonEntries.push_back(LessonEntry(*lit, false));
        }
    }
}

const LessonProvider::LessonEntry& LessonProvider::GetLessonEntry(int data) const {
    MILO_ASSERT_RANGE(data, 0, NumData(), 0xD0);
    return mLessonEntries[data];
}
