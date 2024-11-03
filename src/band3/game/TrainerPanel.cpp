#include "game/TrainerPanel.h"
#include "game/TrainerProgressMeter.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "utl/DataPointMgr.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

TrainerPanel* TheTrainerPanel;

TrainerPanel::TrainerPanel() : mProgressMeter(0), mCurrSection(-1), mShowProgressMeter(1) {
    mProgressMeter = new TrainerProgressMeter();
}

TrainerPanel::~TrainerPanel(){
    delete mProgressMeter;
}

void TrainerPanel::Enter(){
    UIPanel::Enter();
    InitSections();
    mCurrSection = -1;
    TheTrainerPanel = this;
    RndDir* progressMeter = DataDir()->Find<RndDir>("progress_meter", true);
    mProgressMeter->Init(progressMeter, mSections.size());
    UpdateProgressMeter();
    unk4c.clear();
    unk4c.resize(mSections.size());
}

void TrainerPanel::Exit(){
    UIPanel::Exit();
    TheTrainerPanel = nullptr;
}

void TrainerPanel::Draw(){
    UIPanel::Draw();
    if(mShowProgressMeter){
        TheUI->unk34->Select();
        mProgressMeter->Draw();
    }
    else {
        mProgressMeter->Hide();
    }
}

void TrainerPanel::StartSection(int sect){
    if(mCurrSection >= 0){
        TrainerChallenge* tc = mSections[mCurrSection].mChallenge;
        if(tc) tc->Exit();
    }
    mCurrSection = sect;
    Message setSectNameMsg("set_section_name", mSections[sect].mName, sect);
    Handle(setSectNameMsg, true);


    TrainerChallenge* tc = mSections[mCurrSection].mChallenge;
    if(mCurrSection >= 0 && tc){
        Message updateRestsMsg("update_restrictions", tc->GetRestrictionToken());
        Handle(updateRestsMsg, true);
        tc->Enter();
    }

    Handle(reset_score_msg, true);
    StartSectionImpl();
    SendDataPoint("trainers/section", start_section, sect);
}

void TrainerPanel::RestartSection(){
    StartSection(mCurrSection);
}