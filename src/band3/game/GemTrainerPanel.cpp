#include "game/GemTrainerPanel.h"
#include "game/Metronome.h"
#include "game/TrainerGemTab.h"

GemTrainerPanel::GemTrainerPanel() : unk5c(0), unk70(0), unk74(0), unk78(0), unk7c(0), unk80(0), unk84(0), unka8(0), unka9(0), unkac(0), unkb0(0), unkb8(0), unkbc(-1.0f), unkc0(-1.0f),
    unkc8(0), unkc9(0), unkcc(-1), unkd0(0) {
    unkb4 = new TrainerGemTab();
    unkb8 = new Metronome();
}

GemTrainerPanel::~GemTrainerPanel(){
    delete unkb4;
    delete unkb8;
}

void GemTrainerPanel::Enter(){
    
}