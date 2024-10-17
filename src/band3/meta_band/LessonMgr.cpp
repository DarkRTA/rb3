#include "meta_band/LessonMgr.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/System.h"
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

}

void LessonMgr::Init(){ TheLessonMgr = new LessonMgr(); }
LessonMgr* LessonMgr::GetLessonMgr(){ return TheLessonMgr; }