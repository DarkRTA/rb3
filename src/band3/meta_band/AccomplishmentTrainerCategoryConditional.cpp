#include "AccomplishmentTrainerCategoryConditional.h"
#include "meta_band/LessonMgr.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

AccomplishmentTrainerCategoryConditional::AccomplishmentTrainerCategoryConditional(DataArray* i_pConfig, int i) : AccomplishmentTrainerConditional(i_pConfig, i), mCategory(""), mNumLessons(0) {
    Configure(i_pConfig);
}

AccomplishmentTrainerCategoryConditional::~AccomplishmentTrainerCategoryConditional() {

}

void AccomplishmentTrainerCategoryConditional::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1E);
    i_pConfig->FindData(lesson_category, mCategory, true);
    i_pConfig->FindData(num_lessons, mNumLessons, true);
}

AccomplishmentType AccomplishmentTrainerCategoryConditional::GetType() const {
    return kAccomplishmentTypeTrainerCategoryConditional;
}

bool AccomplishmentTrainerCategoryConditional::IsFulfilled(BandProfile* profile) const {
    return mNumLessons <= GetNumCompletedLessons(profile);
}

int AccomplishmentTrainerCategoryConditional::GetNumCompletedLessons(BandProfile* profile) const {
    std::vector<Symbol> lessons;
    InqCompletedLessons(profile, lessons);
    int ret = lessons.size();
    if(ret >= mNumLessons) ret = mNumLessons;
    return ret;
}

bool AccomplishmentTrainerCategoryConditional::InqIncrementalSymbols(BandProfile* i_pProfile, std::vector<Symbol>& o_rSymbols) const {
    MILO_ASSERT(i_pProfile, 0x48);
    MILO_ASSERT(o_rSymbols.empty(), 0x49);
    LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0x4C);
    std::vector<Symbol>* lessons = pLessonMgr->GetLessonsFromCategory(mCategory);
    if(!lessons){
        MILO_WARN("No lessons found for category %s", mCategory.Str());
        return false;
    }
    else {
        for(std::vector<Symbol>::iterator it = lessons->begin(); it != lessons->end(); ++it){
            Symbol key = *it;
            if(CheckConditionsForLesson(i_pProfile, key)){
                o_rSymbols.push_back(key);
            }
            if(o_rSymbols.size() >= mNumLessons) break;
        }
        if(o_rSymbols.size() < mNumLessons){
            int numsyms = o_rSymbols.size();
            int numlessons = mNumLessons;
            int diff = numlessons - numsyms;
            for(int i = 0; i < diff; i++){
                o_rSymbols.push_back(goal_filtersong_unknown);
            }
        }
        return true;
    }
}

Symbol AccomplishmentTrainerCategoryConditional::GetFirstUnfinishedAccomplishmentEntry(BandProfile* i_pProfile) const {
    MILO_ASSERT(i_pProfile, 0x77);
    Symbol symFirst = gNullStr;
    LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0x7C);
    std::vector<Symbol>* lessons = pLessonMgr->GetLessonsFromCategory(mCategory);
    if(!lessons){
        MILO_WARN("No lessons found for category %s", mCategory.Str());
        return gNullStr;
    }
    else {
        for(std::vector<Symbol>::iterator it = lessons->begin(); it != lessons->end(); ++it){
            Symbol key = *it;
            if(!CheckConditionsForLesson(i_pProfile, key)){
                symFirst = key;
                break;
            }
        }
        MILO_ASSERT(symFirst != gNullStr, 0x91);
        return symFirst;
    }
}

int AccomplishmentTrainerCategoryConditional::GetTotalNumLessons() const { return mNumLessons; }

bool AccomplishmentTrainerCategoryConditional::InqCompletedLessons(BandProfile* i_pProfile, std::vector<Symbol>& o_rLessons) const {
    MILO_ASSERT(i_pProfile, 0x9E);
    MILO_ASSERT(o_rLessons.empty(), 0x9F);
    LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0xA2);
    std::vector<Symbol>* lessons = pLessonMgr->GetLessonsFromCategory(mCategory);
    if(!lessons){
        MILO_WARN("No lessons found for category %s", mCategory.Str());
        return false;
    }
    else {
        for(std::vector<Symbol>::iterator it = lessons->begin(); it != lessons->end(); ++it){
            Symbol key = *it;
            if(CheckConditionsForLesson(i_pProfile, key)){
                o_rLessons.push_back(key);
            }
        }
        return true;
    }
}
