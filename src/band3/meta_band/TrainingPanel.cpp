#include "meta_band/TrainingPanel.h"
#include "LessonProvider.h"
#include "TrainingPanel.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/TrainerProvider.h"
#include "meta_band/TrainingMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/JoypadMsgs.h"
#include "ui/UIPanel.h"
#include "utl/Messages3.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

TrainingPanel::TrainingState TrainingPanel::sBackStates[] = { kTrainingState_Invalid, kTrainingState_Invalid, kTrainingState_MainMenu,
    kTrainingState_MainMenu, kTrainingState_MainMenu, kTrainingState_MainMenu };

TrainingPanel::TrainingPanel() : mTrainingState(kTrainingState_Invalid), mTrainerProvider(0), mLessonProvider(0) {

}

TrainingPanel::~TrainingPanel(){

}

void TrainingPanel::Load(){
    UIPanel::Load();
    TrainingMgr* pTrainingMgr = TrainingMgr::GetTrainingMgr();
    MILO_ASSERT(pTrainingMgr, 0x2E);
    MILO_ASSERT(!mTrainerProvider, 0x30);
    mTrainerProvider = new TrainerProvider();
    MILO_ASSERT(!mLessonProvider, 0x33);
    mLessonProvider = new LessonProvider();
}

void TrainingPanel::Enter(){
    UIPanel::Enter();
    TrainingMgr* pTrainingMgr = TrainingMgr::GetTrainingMgr();
    MILO_ASSERT(pTrainingMgr, 0x3C);
}

void TrainingPanel::Exit(){
    UIPanel::Exit();
    SetTrainingState(kTrainingState_Invalid);
}

void TrainingPanel::Unload(){
    UIPanel::Unload();
    RELEASE(mTrainerProvider);
    RELEASE(mLessonProvider);
}

bool TrainingPanel::IsCorrectController(Symbol s, LocalBandUser* u) const {
    ControllerType ty = u->GetControllerType();
    if((s == trainer_drums || s == trainer_pro_drums) && ty == kControllerDrum) return true;
    else if(s == trainer_real_guitar && ty == kControllerRealGuitar) return true;
    else if(s == trainer_pro_keyboard && ty == kControllerKeys) return true;
    else return false;
}

void TrainingPanel::GotoTrainer(Symbol s){
    TrainingState state = GetStateFromTrainer(s);
    if(state != kTrainingState_Invalid){
        UpdateLessonsProvider(s);
        SetTrainingState(state);
    }
}

void TrainingPanel::UpdateLessonsProvider(Symbol s){
    mLessonProvider->Update(s);
    RefreshLessonsList();
}

void TrainingPanel::SetTrainingState(TrainingPanel::TrainingState state){
    mTrainingState = state;
    static Message msg("update_state", state);
    msg[0] = mTrainingState;
    Handle(msg, true);
}

TrainingPanel::TrainingState TrainingPanel::GetStateFromTrainer(Symbol s){
    if(s == trainer_drums) return kTrainingState_DrumLessons;
    else if(s == trainer_pro_drums) return kTrainingState_ProDrumLessons;
    else if(s == trainer_real_guitar) return kTrainingState_ProGuitarLessons;
    else if(s == trainer_pro_keyboard) return kTrainingState_ProKeyboardLessons;
    else return kTrainingState_Invalid;
}

void TrainingPanel::RefreshLessonsList(){
    Handle(refresh_lessons_list_msg, true);
}

DataNode TrainingPanel::OnMsg(const ButtonDownMsg& msg){
    JoypadAction action = msg.GetAction();
    if(action == kAction_Cancel) return LeaveState();
    else if(action == kAction_ViewModify) TheProfileMgr.SetPrimaryProfileByUser(msg.GetUser());
    return DataNode(kDataUnhandled, 0);
}

DataNode TrainingPanel::LeaveState(){
    if(mTrainingState == kTrainingState_MainMenu) return DataNode(kDataUnhandled, 0);
    else {
        SetTrainingState(sBackStates[mTrainingState]);
        return 1;
    }
}

BEGIN_HANDLERS(TrainingPanel)
    HANDLE_EXPR(is_correct_controller, IsCorrectController(_msg->Sym(2), _msg->Obj<LocalBandUser>(3)))
    HANDLE_ACTION(goto_trainer, GotoTrainer(_msg->Sym(2)))
    HANDLE_ACTION(set_state, SetTrainingState((TrainingState)_msg->Int(2)))
    HANDLE_EXPR(trainer_provider, mTrainerProvider)
    HANDLE_EXPR(lesson_provider, mLessonProvider)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_CHECK(0xC6)
END_HANDLERS