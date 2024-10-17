#include "meta_band/TrainerProvider.h"
#include "BandProfile.h"
#include "TrainerProvider.h"
#include "meta_band/LessonMgr.h"
#include "meta_band/ProfileMgr.h"
#include "os/Debug.h"
#include "ui/UIListLabel.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

TrainerProvider::TrainerProvider(){
    LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0x15);
    mTrainers = pLessonMgr->mTrainers;
}

TrainerProvider::~TrainerProvider(){

}

void TrainerProvider::Text(int i1, int i2, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(slot, 0x20);
    MILO_ASSERT(label, 0x21);
    if(slot->Matches("trainer")){
        label->SetTextToken(DataSymbol(i2));
    }
    else if(slot->Matches("progress")){
        Symbol data = DataSymbol(i2);
        LessonMgr* pLessonMgr = LessonMgr::GetLessonMgr();
        MILO_ASSERT(pLessonMgr, 0x2D);
        BandProfile* profile = TheProfileMgr.GetPrimaryProfile();
        if(profile){
            int count_completed = pLessonMgr->GetCompletedCountFromTrainer(profile, data);
            int count = pLessonMgr->GetTotalCountFromTrainer(data);
            label->SetTokenFmt(trainer_progress, count_completed, count);
        }
    }
    else label->SetTextToken(gNullStr);
}

Symbol TrainerProvider::DataSymbol(int data) const {
    MILO_ASSERT(( 0) <= (data) && (data) < ( NumData()), 0x41);
    return mTrainers[data];
}