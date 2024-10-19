#include "meta_band/LessonMgr.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/Defines.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols.h"
#include <vector>

namespace {
    LessonMgr* TheLessonMgr;
}

DECOMP_FORCEACTIVE(LessonMgr, __FILE__, "mTrainerToCategoriesMap.empty()")

LessonMgr::LessonMgr(){
    MILO_ASSERT(mCategoryToLessonsMap.empty(), 0x1C);
    MILO_ASSERT(mLessonsMap.empty(), 0x1D);
    DataArray* pTrainerConfig = SystemConfig("trainer");
    MILO_ASSERT(pTrainerConfig, 0x20);
    DataArray* pTrainers = pTrainerConfig->FindArray("trainers", true);
    MILO_ASSERT(pTrainers, 0x23);
    for(int i = 1; i < pTrainers->Size(); i++){
        DataArray* pTrainer = pTrainers->Array(i);
        MILO_ASSERT(pTrainer, 0x29);
        Symbol sym = pTrainer->Sym(0);
        mTrainers.push_back(sym);

        std::vector<Symbol>* symvec = new std::vector<Symbol>();
        for(int j = 1; j < pTrainer->Size(); j++){
            DataArray* pCategory = pTrainer->Array(j);
            MILO_ASSERT(pCategory, 0x33);
            Symbol symcat = pCategory->Sym(0);
            symvec->push_back(symcat);

            std::vector<Symbol>* symvec2 = new std::vector<Symbol>();
            for(int k = 1; k < pCategory->Size(); k++){
                DataArray* pLesson = pCategory->Array(k);
                MILO_ASSERT(pLesson, 0x3E);
                Symbol sym0 = pLesson->Sym(0);
                Symbol sym1 = pLesson->Sym(1);
                TrackType ty = GetTrackTypeFromTrainer(sym);
                Lesson* lesson = GetLesson(sym0);
                if(!lesson){
                    mLessonsMap[sym0] = new Lesson(sym, symcat, sym0, sym1, ty);
                    symvec2->push_back(sym0);
                }
                else MILO_WARN("Lesson: %s already exists", sym0.Str());
            }
            mCategoryToLessonsMap[symcat] = symvec2;
        }
        mTrainerToCategoriesMap[sym] = symvec;
    }
    SetName("lesson_mgr", ObjectDir::Main());
}

LessonMgr::~LessonMgr(){
    for(std::map<Symbol, Lesson*>::iterator it = mLessonsMap.begin(); it != mLessonsMap.end(); ++it){
        RELEASE(it->second);
    }
    mLessonsMap.clear();
        
    for(std::map<Symbol, std::vector<Symbol>*>::iterator it = mTrainerToCategoriesMap.begin(); it != mTrainerToCategoriesMap.end(); ++it){
        RELEASE(it->second);
    }
    mTrainerToCategoriesMap.clear();

    for(std::map<Symbol, std::vector<Symbol>*>::iterator it = mCategoryToLessonsMap.begin(); it != mCategoryToLessonsMap.end(); ++it){
        RELEASE(it->second);
    }
    mCategoryToLessonsMap.clear();
}

void LessonMgr::Init(){ TheLessonMgr = new LessonMgr(); }
LessonMgr* LessonMgr::GetLessonMgr(){ return TheLessonMgr; }

Lesson* LessonMgr::GetLesson(Symbol s) const {
    std::map<Symbol, Lesson*>::const_iterator it = mLessonsMap.find(s);
    if(it != mLessonsMap.end()) return it->second;
    else return nullptr;
}

std::vector<Symbol>* LessonMgr::GetCategoriesFromTrainer(Symbol s) const {
    std::map<Symbol, std::vector<Symbol>*>::const_iterator it = mTrainerToCategoriesMap.find(s);
    if(it != mTrainerToCategoriesMap.end()) return it->second;
    else return nullptr;
}

std::vector<Symbol>* LessonMgr::GetLessonsFromCategory(Symbol s) const {
    std::map<Symbol, std::vector<Symbol>*>::const_iterator it = mCategoryToLessonsMap.find(s);
    if(it != mCategoryToLessonsMap.end()) return it->second;
    else return nullptr;
}

int LessonMgr::GetTotalCountFromCategory(Symbol s){ return GetLessonsFromCategory(s)->size(); }

int LessonMgr::GetTotalCountFromTrainer(Symbol s){
    int count = 0;
    std::vector<Symbol>* cats = GetCategoriesFromTrainer(s);
    for(int i = 0; i < cats->size(); i++){
        count += GetTotalCountFromCategory(cats->at(i));
    }
    return count;
}

int LessonMgr::GetCompletedCountFromCategory(BandProfile* pProfile, Symbol s){
    MILO_ASSERT(pProfile, 0xCB);
    int count = 0;
    std::vector<Symbol>* lessons = GetLessonsFromCategory(s);
    for(int i = 0; i < lessons->size(); i++){
        Symbol lesson = lessons->at(i);
        if(pProfile->IsLessonComplete(lesson, 1.0f)) count++;
    }
    return count;
}

int LessonMgr::GetCompletedCountFromTrainer(BandProfile* pProfile, Symbol s){
    MILO_ASSERT(pProfile, 0xDE);
    int count = 0;
    std::vector<Symbol>* cats = GetCategoriesFromTrainer(s);
    for(int i = 0; i < cats->size(); i++){
        count += GetCompletedCountFromCategory(pProfile, cats->at(i));
    }
    return count;
}

TrackType LessonMgr::GetTrackTypeFromTrainer(Symbol s){
    TrackType ty;
    if(s == trainer_drums) ty = kTrackDrum;
    else if(s == trainer_pro_drums) ty = kTrackDrum;
    else if(s == trainer_vocals) ty = kTrackVocals;
    else if(s == trainer_real_guitar) ty = kTrackRealGuitar;
    else if(s == trainer_pro_keyboard) ty = kTrackRealKeys;
    else {
        ty = kTrackNone;
        MILO_ASSERT(0, 0x109);
    }
    return ty;
}

Lesson::Lesson(Symbol s1, Symbol s2, Symbol s3, Symbol s4, TrackType ty) : mTrainer(s1), mCategory(s2), mName(s3), mSong(s4), mTrackType(ty) {

}

Lesson::~Lesson(){

}

Difficulty Lesson::GetDifficulty() const {
    String str(mCategory.Str());
    Symbol diff;
    std::vector<String> splits;
    if(str.split("_", splits) > 0){
        diff = splits.back().c_str();
    }
    Difficulty ret;
    if(diff == easy) ret = kDifficultyEasy;
    else if(diff == medium) ret = kDifficultyMedium;
    else if(diff == hard) ret = kDifficultyHard;
    else if(diff == expert) ret = kDifficultyExpert;
    else {
        ret = kDifficultyEasy;
        MILO_ASSERT(0, 0x13E);
    }
    return ret;
}